// SPDX-License-Identifier: GPL-2.0
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <ynl.h>
#include <libmnl/libmnl.h> //dnf install libmnl-devel
#include <linux/genetlink.h>
#include <json-c/json.h>  // dnf install json-c json-c-devel
#include <json-c/json_object.h>

#include "dpll-user.h"

#define BUF_SIZE 512
#define SOCKET_PATH_MAX_LEN 108 // maximum length of socket path in struct sockaddr_un

enum return_code {
	OK = 0,
	ERROR_SRV_SOCKET = 1,
	UDS_PATH_TOO_LONG = 2,
	FAIL_CLEARING_UDS_FILE = 3,
	FAIL_BIND_SERVER_SOCK = 4,
	FAIL_LISTEN_UDS = 5,
	FAIL_CREATE_YNL_SOCKET = 6,
	FAIL_RECEIVE_YNL_DATA = 7,
	UDS_PATH_FAIL = 8
};

static int ntf_data_cb(const struct nlmsghdr *nlh, void *data)
{
	const struct nlattr *attr;
	json_object *obj = (json_object*)data;
	mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
		switch (mnl_attr_get_type(attr)){
			case DPLL_A_ID:
				json_object_object_add(obj, "id", json_object_new_int(mnl_attr_get_u32(attr)));
				break;
			case DPLL_A_MODULE_NAME:
				json_object_object_add(obj, "module-name", json_object_new_string(mnl_attr_get_str(attr)));
				break;
			case DPLL_A_CLOCK_ID:
				json_object_object_add(obj, "clock-id", json_object_new_uint64(mnl_attr_get_u64(attr)));
				break;
			case DPLL_A_MODE:
				json_object_object_add(obj, "mode", json_object_new_string(dpll_mode_str(mnl_attr_get_u8(attr))));
				break;
			case DPLL_A_LOCK_STATUS:
				json_object_object_add(obj, "lock-status", json_object_new_string(dpll_lock_status_str(mnl_attr_get_u8(attr))));
				break;
			case DPLL_A_TYPE:
				json_object_object_add(obj, "type", json_object_new_string(dpll_type_str(mnl_attr_get_u8(attr))));
				break;
		}
	}
	return MNL_CB_OK;
}

int ntf_main(const char* mcast_group, bool stdout_print, char* socket_path)
{
	struct ynl_sock *ys = NULL;
	json_object *data = NULL;
	int recv = 0;
	int rc = 0;
	struct sockaddr_un addr;
	int cfd = 0, sfd = 0; //client, server UDS file descriptors
	
	bool to_socket = (bool)strcmp(socket_path, "");
	if (to_socket){
		sfd = socket(AF_UNIX, (SOCK_SEQPACKET | SOCK_CLOEXEC), 0);
		if (sfd == -1) {
			return ERROR_SRV_SOCKET;
		}
		/* check address isn't longer than the buffer (108 characters)*/
		if (strlen(socket_path) > sizeof(addr.sun_path) - 1) {
			rc = UDS_PATH_TOO_LONG;
			goto exit;
		}
		// Ensure no file exists on address path
		if (remove(socket_path) == -1 && errno != ENOENT) {
			rc = FAIL_CLEARING_UDS_FILE;
			goto exit;
		}
		memset(&addr, 0, sizeof(struct sockaddr_un));
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
		if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
			rc = FAIL_BIND_SERVER_SOCK;
			goto exit;
		}
		if (listen(sfd, 1) == -1) {
			rc = FAIL_LISTEN_UDS;
			goto exit;
		}
		/* This will block until a client connects: */
		cfd = accept(sfd, NULL, NULL);
	}

	ys = ynl_sock_create(&ynl_dpll_family, NULL);
	if (!ys){
		rc = FAIL_CREATE_YNL_SOCKET;
		goto exit;
	}
	ynl_subscribe(ys, mcast_group);
	recv = mnl_socket_recvfrom(ys->sock, ys->rx_buf, MNL_SOCKET_BUFFER_SIZE);
	while (recv > 0) {
		data = json_object_new_object();
		recv = mnl_cb_run(ys->rx_buf, recv, 0, 0, ntf_data_cb, (void*)data);
		if (recv <= 0){
			rc = FAIL_RECEIVE_YNL_DATA;
			goto exit;
		}
		if (stdout_print)
			json_object_to_fd(fileno(stdout), data, 0);
		if (to_socket){
			if (access(socket_path, F_OK) == 0) {
				json_object_to_fd(cfd, data, 0);
			} else {
				rc = UDS_PATH_FAIL;
				goto exit;
			}
			
		}
		json_object_put(data);
		recv = mnl_socket_recvfrom(ys->sock, ys->rx_buf, MNL_SOCKET_BUFFER_SIZE);
	}
exit:
	if(sfd)
		close(sfd);
	if(cfd)
		close(cfd);
	if (ys)
		ynl_sock_destroy(ys);
	if (data)
		json_object_put(data);
	return 	rc;
}


int main(int argc, char **argv)
{
	bool stdout_print = false;
	char socket_path[SOCKET_PATH_MAX_LEN] = "";
	int opt;
 
	while ((opt = getopt(argc, argv, "ou:")) != -1) {
		switch (opt) {
		case 'o':
			stdout_print = true;
		break;
		case 'u':
			strcpy(socket_path, optarg);
			break;
		default:
			fprintf(stderr, "Usage: %s [-o]|[-u <socket path>]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (!strcmp(socket_path, "") && !stdout_print){
		printf("either socket path or stdout flag must be specified\n");
		exit(EXIT_FAILURE);
	}
	return ntf_main(DPLL_MCGRP_MONITOR, stdout_print, socket_path);
}

// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ynl.h>
#include <libmnl/libmnl.h> //dnf install libmnl-devel
#include <linux/genetlink.h>
#include <json-c/json.h>  // dnf install json-c json-c-devel
#include <json-c/json_object.h>

#include "dpll-user.h"

#define BUF_SIZE 512
#define SV_SOCK_PATH "/tmp/us_xfr"

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

int ntf_main(const char* mcast_group)
{
	struct ynl_sock *ys;
	json_object *data;
	int ret = 0;
	struct sockaddr_un addr;
  	
	int sfd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if (sfd == -1) {
		return -1;
	}
	/* check address isn't longer than the buffer (108 characters)*/
	if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1) {
		return -2;
	}
	// Ensure no file exists on address path
	if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
		return -3;
	}
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
		return -4;
	}
	if (listen(sfd, 1) == -1) {
		return -5;
	}
	printf("Waiting for connections\n");
	/* This will block until a client connects: */
	int cfd = accept(sfd, NULL, NULL);
	printf("Accepted socket fd = %d\n", cfd);

	ys = ynl_sock_create(&ynl_dpll_family, NULL);
	if (!ys){
		fprintf(stderr,"dpll-monitor failed to create socket\n");
		return -1;
	}
	ynl_subscribe(ys, mcast_group);
	ret = mnl_socket_recvfrom(ys->sock, ys->rx_buf, MNL_SOCKET_BUFFER_SIZE);
	while (ret > 0) {
		data = json_object_new_object();
		ret = mnl_cb_run(ys->rx_buf, ret, 0, 0, ntf_data_cb, (void*)data);
		if (ret <= 0){
			break;
		}
		json_object_to_fd(fileno(stdout), data, 0);
		json_object_to_fd(cfd, data, 0);
		json_object_put(data);
		ret = mnl_socket_recvfrom(ys->sock, ys->rx_buf, MNL_SOCKET_BUFFER_SIZE);
	}
	ynl_sock_destroy(ys);
	if (ret == -1) {
		perror("error");
		exit(EXIT_FAILURE);
	}
	return 	0;
}


int main(int argc, char **argv)
{
	ntf_main(DPLL_MCGRP_MONITOR);
	return 0;
}

// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ynl.h>
#include <libmnl/libmnl.h>
#include <linux/genetlink.h>

#include "dpll-user.h"

#define DPLL_ID 0

typedef struct{
	int mcast_id;
	char* mcast_name;
}dpll_mcast;

static int parse_mc_grps_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	/* skip unsupported attribute in user-space */
	if (mnl_attr_type_valid(attr, CTRL_ATTR_MCAST_GRP_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case CTRL_ATTR_MCAST_GRP_ID:
		if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case CTRL_ATTR_MCAST_GRP_NAME:
		if (mnl_attr_validate(attr, MNL_TYPE_STRING) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

static void parse_genl_mc_grps(struct nlattr *nested, void *data)
{
	struct nlattr *pos;

	mnl_attr_for_each_nested(pos, nested) {
		struct nlattr *tb[CTRL_ATTR_MCAST_GRP_MAX+1] = {};

		mnl_attr_parse_nested(pos, parse_mc_grps_cb, tb);
		if (tb[CTRL_ATTR_MCAST_GRP_NAME]) {
			char* required = ((dpll_mcast*)data)->mcast_name;
			const char* found = mnl_attr_get_str(tb[CTRL_ATTR_MCAST_GRP_NAME]);
			if(!strcmp(required, found)){
				((dpll_mcast*)data)->mcast_id = mnl_attr_get_u32(tb[CTRL_ATTR_MCAST_GRP_ID]);
			}
		}
	}
}

static int data_attr_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	if (mnl_attr_type_valid(attr, CTRL_ATTR_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case CTRL_ATTR_MCAST_GROUPS:
		if (mnl_attr_validate(attr, MNL_TYPE_NESTED) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	default:
		break;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

static int mcast_id_cb(const struct nlmsghdr *nlh, void *data)
{
	struct nlattr *tb[CTRL_ATTR_MAX+1] = {};
	struct genlmsghdr *genl = mnl_nlmsg_get_payload(nlh);

	mnl_attr_parse(nlh, sizeof(*genl), data_attr_cb, tb);
	if (tb[CTRL_ATTR_MCAST_GROUPS]) {
		parse_genl_mc_grps(tb[CTRL_ATTR_MCAST_GROUPS], data);
	}
	return MNL_CB_OK;
}

int get_mcast_id(char *family)
{
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct genlmsghdr *genl;
	int ret;
	unsigned int seq, portid;
	char* mcast_name = "monitor";
	dpll_mcast data;
	data.mcast_name = mcast_name;
	

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type	= GENL_ID_CTRL;
	nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	nlh->nlmsg_seq = seq = time(NULL);

	genl = mnl_nlmsg_put_extra_header(nlh, sizeof(struct genlmsghdr));
	genl->cmd = CTRL_CMD_GETFAMILY;
	genl->version = 1;

	mnl_attr_put_u32(nlh, CTRL_ATTR_FAMILY_ID, GENL_ID_CTRL);

	mnl_attr_put_strz(nlh, CTRL_ATTR_FAMILY_NAME, family);
	nl = mnl_socket_open(NETLINK_GENERIC);

	if (nl == NULL) {
		perror("mnl_socket_open");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0) {
		perror("mnl_socket_bind");
		exit(EXIT_FAILURE);
	}
	portid = mnl_socket_get_portid(nl);

	if (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) {
		perror("mnl_socket_sendto");
		exit(EXIT_FAILURE);
	}

	ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	
	while (ret > 0) {
		ret = mnl_cb_run(buf, ret, seq, portid, mcast_id_cb, &data);
		if (ret <= 0)
			break;
		ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	}
	printf("dpll monitor id is %d\n", data.mcast_id);
	if (ret == -1) {
		perror("error");
		exit(EXIT_FAILURE);
	}
	mnl_socket_close(nl);

	return 0;
}


static int ntf_data_cb(const struct nlmsghdr *nlh, void *data)
{
	const struct nlattr *attr;

	mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
		switch (mnl_attr_get_type(attr)){
			case DPLL_A_ID:
				printf("dpll ID: %d\n", mnl_attr_get_u32(attr));
				break;
			case DPLL_A_MODULE_NAME:
				printf("module name: %s\n", mnl_attr_get_str(attr));
				break;
			case DPLL_A_CLOCK_ID:
				printf("clock ID: %lx", mnl_attr_get_u64(attr));
				break;
			case DPLL_A_MODE:
				printf("dpll mode: %s\n", dpll_mode_str(mnl_attr_get_u8(attr)));
				break;
			case DPLL_A_LOCK_STATUS:
				printf("dpll lock status: %s\n", dpll_lock_status_str(mnl_attr_get_u8(attr)));
				break;
			case DPLL_A_TYPE:
				printf("dpll type %s\n", dpll_type_str(mnl_attr_get_u8(attr)));
				break;
		}

	}

	
	return MNL_CB_OK;
}

int ntf_main(int group)
{
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	int ret;

	nl = mnl_socket_open(NETLINK_GENERIC);
	if (nl == NULL) {
		perror("mnl_socket_open");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0) {
		perror("mnl_socket_bind");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_setsockopt(nl, NETLINK_ADD_MEMBERSHIP, &group,
				  sizeof(int)) < 0) {
		perror("mnl_socket_setsockopt");
		exit(EXIT_FAILURE);
	}

	ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	while (ret > 0) {
		ret = mnl_cb_run(buf, ret, 0, 0, ntf_data_cb, NULL);
		if (ret <= 0)
			break;
		ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	}
	if (ret == -1) {
		perror("error");
		exit(EXIT_FAILURE);
	}

	mnl_socket_close(nl);

	return 0;
}


int main(int argc, char **argv)
{
	struct ynl_sock *ys;
	struct dpll_device_get_rsp *dev;
	struct dpll_device_get_req *req;
//	struct ynl_ntf_base_type *ntf;
	int rc = 0;

	ys = ynl_sock_create(&ynl_dpll_family, NULL);
	if (!ys){
		fprintf(stderr,"failed to create socket\n");
		return 1;
	}

	req = dpll_device_get_req_alloc();
	if (!req){
		fprintf(stderr, "failed to allocate request\n");
		rc = 2;
		goto sock_close;
	}
	
	dpll_device_get_req_set_id(req, DPLL_ID);

	dev = dpll_device_get(ys, req);
	
	if (!dev){
		fprintf(stderr, "failed to get device\n");
		rc = 3;
		goto err_close;
	}

	printf("Module name: %s\n", dev->module_name);
	printf("Lock status: %s\n", dpll_lock_status_str(dev->lock_status));
	printf("DPLL type: %s\n", dpll_type_str(dev->type));
	printf("Clock ID: %llx\n", dev->clock_id);
	dpll_device_get_rsp_free(dev);

	get_mcast_id("dpll");
	ntf_main(4);
	
err_close:
	dpll_device_get_req_free(req);
sock_close:
	ynl_sock_destroy(ys);
	return rc;
}

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

int ntf_main(const char* mcast_group)
{
	struct ynl_sock *ys;
	int ret;

	ys = ynl_sock_create(&ynl_dpll_family, NULL);
	if (!ys){
		fprintf(stderr,"dpll-monitor: failed to create socket\n");
		return -1;
	}

	ynl_subscribe(ys, mcast_group);

	ret = mnl_socket_recvfrom(ys->sock, ys->rx_buf, MNL_SOCKET_BUFFER_SIZE);
	while (ret > 0) {
		ret = mnl_cb_run(ys->rx_buf, ret, 0, 0, ntf_data_cb, NULL);
		if (ret <= 0){
			break;
		}
		ret = mnl_socket_recvfrom(ys->sock, ys->rx_buf, MNL_SOCKET_BUFFER_SIZE);
	}
	if (ret == -1) {
		perror("error");
		exit(EXIT_FAILURE);
	}
	ynl_sock_destroy(ys);
	return 	0;
}


int main(int argc, char **argv)
{
	ntf_main("monitor");
	return 0;
}

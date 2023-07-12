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
	
	ntf_main(4);
	return 0;
}

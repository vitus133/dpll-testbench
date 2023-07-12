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


int get_mcast_id(char* mcast_group)
{
	struct ynl_sock *ys;
	int mcast_id = -1;

	ys = ynl_sock_create(&ynl_dpll_family, NULL);
	if (!ys){
		fprintf(stderr,"dpll-monitor: failed to create socket\n");
		return -1;
	}
	for (unsigned int i = 0; i< ys->n_mcast_groups; ++i) {
		if (!strcmp((ys->mcast_groups + i)->name, mcast_group))
			mcast_id = (ys->mcast_groups + i)->id;
	}
	ynl_sock_destroy(ys);
	return 	mcast_id;
;
}


int main(int argc, char **argv)
{
	int mcast_id = get_mcast_id("monitor");
	printf("multicast ID is %d\n", mcast_id);
	return 0;
}

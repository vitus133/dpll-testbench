// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <ynl.h>
#include <libmnl/libmnl.h>
#include <linux/genetlink.h>

#include "dpll-user.h"


int main(int argc, char **argv)
{
	struct ynl_sock *ys;
	struct dpll_device_get_list *list;
	struct dpll_device_get_list *next;

	int rc = 0;

	ys = ynl_sock_create(&ynl_dpll_family, NULL);
	if (!ys){
		fprintf(stderr,"failed to create socket\n");
		return 1;
	}

	list = dpll_device_get_dump(ys);
	
	if (!list){
		fprintf(stderr, "failed to get dlist\n");
		rc = 3;
		goto err_close;
	}
	next = list;
	while(next != (struct dpll_device_get_list*)YNL_LIST_END){
		printf("Module name: %s\n", next->obj.module_name);
		printf("Lock status: %s\n", dpll_lock_status_str(next->obj.lock_status));
		printf("DPLL type: %s\n", dpll_type_str(next->obj.type));
		printf("Clock ID: %llx\n", next->obj.clock_id);
		next = next->next;	
	}
	dpll_device_get_list_free(list);

err_close:
	ynl_sock_destroy(ys);
	return rc;
}

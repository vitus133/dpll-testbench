// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <string.h>

#include <ynl.h>

#include "dpll-user.h"

#define DPLL_ID 0

int main(int argc, char **argv)
{
	struct ynl_sock *ys;
	struct dpll_device_get_rsp *dev;
	struct dpll_device_get_req *req;
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

	// Free resources
	dpll_device_get_rsp_free(dev);
err_close:
	dpll_device_get_req_free(req);
sock_close:
	ynl_sock_destroy(ys);
	return rc;
}

// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <ynl.h>
#include <libmnl/libmnl.h>
#include <linux/genetlink.h>
#include <json-c/json.h>  // dnf install json-c json-c-devel
#include <json-c/json_object.h>  // dnf install json-c json-c-devel
#include "dpll-user.h"


int main(int argc, char **argv)
{
	struct ynl_sock *ys;
	struct dpll_device_get_list *list;
	struct dpll_device_get_list *next;
	json_object *root;

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
	root = json_object_new_array();
	next = list;
	while(next != (struct dpll_device_get_list*)YNL_LIST_END){
		json_object *child = json_object_new_object();
		json_object_object_add(child, "module-name", json_object_new_string(next->obj.module_name));
		json_object_object_add(child, "lock-status", json_object_new_string(dpll_lock_status_str(next->obj.lock_status)));
		json_object_object_add(child, "id", json_object_new_int(next->obj.id));
		json_object_object_add(child, "type", json_object_new_string(dpll_type_str(next->obj.type)));
		json_object_object_add(child, "clock-id", json_object_new_uint64(next->obj.clock_id));
		next = next->next;
		json_object_array_add(root, child);	
	}
	json_object_to_fd(fileno(stdout), root, 0); //JSON_C_TO_STRING_PRETTY
	json_object_put(root);
	dpll_device_get_list_free(list);

err_close:
	ynl_sock_destroy(ys);
	return rc;
}

// SPDX-License-Identifier: GPL
/*
 * Generic netlink for DPLL testbench
 */

#include <linux/module.h>
#include <linux/dpll.h>
#include <net/genetlink.h>
#include "dpll-testbench.h"

typedef struct  {
	struct dpll_device *dpll;
	int dpll_idx;
	
}test_dpll;
#define NUM_DPLL_DEVICES 1
test_dpll d[NUM_DPLL_DEVICES];

static const struct dpll_device_ops test_dpll_ops = {
	.lock_status_get = test_dpll_lock_status_get,
	.mode_get = test_dpll_mode_get,
	.mode_supported = test_dpll_mode_supported,
};


static const enum dpll_lock_status
test_dpll_status[__DPLL_LOCK_STATUS_MAX] = {
	[TEST_CGU_STATE_INVALID] = 0,
	[TEST_CGU_STATE_FREERUN] = DPLL_LOCK_STATUS_UNLOCKED,
	[TEST_CGU_STATE_LOCKED] = DPLL_LOCK_STATUS_LOCKED,
	[TEST_CGU_STATE_LOCKED_HO_ACQ] = DPLL_LOCK_STATUS_LOCKED_HO_ACQ,
	[TEST_CGU_STATE_HOLDOVER] = DPLL_LOCK_STATUS_HOLDOVER,
};

static int test_dpll_mode_get(const struct dpll_device *dpll, void *priv,
			     enum dpll_mode *mode,
			     struct netlink_ext_ack *extack)
{
	*mode = DPLL_MODE_AUTOMATIC;

	return 0;
}

static bool test_dpll_mode_supported(const struct dpll_device *dpll, void *priv,
				    enum dpll_mode mode,
				    struct netlink_ext_ack *extack)
{
	if (mode == DPLL_MODE_AUTOMATIC)
		return true;

	return false;
}

static int test_dpll_lock_status_get(const struct dpll_device *dpll, void *priv,
				    enum dpll_lock_status *status,
				    struct netlink_ext_ack *extack)
{

	*status = test_dpll_status[TEST_CGU_STATE_FREERUN];

	return 0;
}

static int init_dpll_testbench(void);
static int __init init_dpll_testbench()
{
	int ret = 0;

	pr_info("starting dpll test bench\n");
	for (int i=0; i<NUM_DPLL_DEVICES; ++i){
		u64 clock_id = i;
		d[i].dpll_idx = i;
		d[i].dpll = dpll_device_get(clock_id, d[i].dpll_idx, THIS_MODULE);
		if (d[i].dpll == NULL) {
			pr_err("dpll_device_get returned error");
			ret = 1;
			break;
		}
		pr_info("dpll %llx has index %d", (u64)d[i].dpll, i);
		ret = dpll_device_register(d[i].dpll, i==0?DPLL_TYPE_PPS:DPLL_TYPE_EEC, &test_dpll_ops, &d[i]);
		if (ret) {
			dpll_device_put(d->dpll);
			return ret;
		}

	}
	return ret;
}
static void exit_dpll_testbench(void);
static void __exit exit_dpll_testbench(void)
{
	for (int i=0; i<NUM_DPLL_DEVICES; ++i){
		dpll_device_unregister(d[i].dpll, &test_dpll_ops, &d[i]);
		dpll_device_put(d[i].dpll);
	}
	pr_info("stopped dpll test bench\n");
}

module_init(init_dpll_testbench);
module_exit(exit_dpll_testbench);

MODULE_AUTHOR("Vitaly Grinberg");
MODULE_LICENSE("GPL");



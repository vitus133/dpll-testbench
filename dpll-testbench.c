// SPDX-License-Identifier: GPL
/*
 * Generic netlink for DPLL testbench
 */

#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/dpll.h>
#include <net/genetlink.h>
#include "dpll-testbench.h"


struct dpll_device *dpll;
struct kthread_worker* kworker;
struct kthread_delayed_work work;
enum dpll_lock_status current_status;
enum dpll_lock_status previous_status;


static const struct dpll_device_ops test_dpll_ops = {
	.lock_status_get = test_dpll_lock_status_get,
	.mode_get = test_dpll_mode_get,
	.mode_supported = test_dpll_mode_supported,
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
	return true;
}

static int test_dpll_lock_status_get(const struct dpll_device *dpll, void *priv,
				    enum dpll_lock_status *status,
				    struct netlink_ext_ack *extack)
{
	*status = current_status;
	return 0;
}

static void advance_dpll_state(void){
	current_status += 1;
	if (current_status >= __DPLL_LOCK_STATUS_MAX){
		current_status = DPLL_LOCK_STATUS_UNLOCKED;
	}
}

static void test_dpll_periodic_work(struct kthread_work *w)
{
	static int counter = 0;

	counter += 1;
	if (counter >= 10){
		counter = 0;
		advance_dpll_state();
	}
	if (current_status != previous_status){
		dpll_device_change_ntf(dpll);
		previous_status = current_status;
	}
	kthread_queue_delayed_work(kworker, &work,  msecs_to_jiffies(500));
}

static int test_dpll_init_worker(void)
{
	kthread_init_delayed_work(&work, test_dpll_periodic_work);
	kworker = kthread_create_worker(0, "dpll-testbench");
	if (IS_ERR(kworker))
		return PTR_ERR(kworker);	
	kthread_queue_delayed_work(kworker, &work, 0);

	return 0;
}


static int __init init_dpll_testbench()
{
	int ret = 0;
	u64 clock_id = 5799633565433967664;
	current_status = DPLL_LOCK_STATUS_UNLOCKED;
	previous_status = current_status;

	pr_info("starting dpll test bench\n");
	
	dpll = dpll_device_get(clock_id, 0, THIS_MODULE);
	if (dpll == NULL) {
		pr_err("dpll_device_get returned error");
		return 1;
	}
	pr_info("dpll %llx", (u64)dpll);
	ret = dpll_device_register(dpll, DPLL_TYPE_PPS, &test_dpll_ops, dpll);
	if (ret) {
		dpll_device_put(dpll);
		return ret;
	}

	
	test_dpll_init_worker();
	return ret;
}

static void __exit exit_dpll_testbench(void)
{
	
	dpll_device_unregister(dpll, &test_dpll_ops, dpll);
	dpll_device_put(dpll);
	
	pr_info("stopped dpll test bench\n");
}

module_init(init_dpll_testbench);
module_exit(exit_dpll_testbench);

MODULE_AUTHOR("Vitaly Grinberg");
MODULE_LICENSE("GPL");



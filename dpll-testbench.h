#ifndef DPLL_TESTBENCH_H
#define DPLL_TESTBENCH_H

static int init_dpll_testbench(void);

static void exit_dpll_testbench(void);

static int test_dpll_lock_status_get(const struct dpll_device *dpll, void *priv,
				    enum dpll_lock_status *status,
				    struct netlink_ext_ack *extack);
static int test_dpll_mode_get(const struct dpll_device *dpll, void *priv,
			     enum dpll_mode *mode,
			     struct netlink_ext_ack *extack);
static bool test_dpll_mode_supported(const struct dpll_device *dpll, void *priv,
				    enum dpll_mode mode,
				    struct netlink_ext_ack *extack);


#endif
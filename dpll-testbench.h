#ifndef DPLL_TESTBENCH_H
#define DPLL_TESTBENCH_H

enum test_cgu_state {
	TEST_CGU_STATE_UNKNOWN = -1,
	TEST_CGU_STATE_INVALID,		/* state is not valid */
	TEST_CGU_STATE_FREERUN,		/* clock is free-running */
	TEST_CGU_STATE_LOCKED,		/* clock is locked to the reference,
					 * but the holdover memory is not valid
					 */
	TEST_CGU_STATE_LOCKED_HO_ACQ,	/* clock is locked to the reference
					 * and holdover memory is valid
					 */
	TEST_CGU_STATE_HOLDOVER,		/* clock is in holdover mode */
	TEST_CGU_STATE_MAX
};

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
// SPDX-License-Identifier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause)
/* Do not edit directly, auto-generated from: */
/*	kernel-root */
/* YNL-GEN user source */

#include <stdlib.h>
#include <string.h>
#include "dpll-user.h"
#include "ynl.h"
#include <linux/dpll.h>

#include <libmnl/libmnl.h>
#include <linux/genetlink.h>

/* Enums */
static const char * const dpll_op_strmap[] = {
	[DPLL_CMD_DEVICE_ID_GET] = "device-id-get",
	[DPLL_CMD_DEVICE_GET] = "device-get",
	[DPLL_CMD_DEVICE_SET] = "device-set",
	[DPLL_CMD_DEVICE_CREATE_NTF] = "device-create-ntf",
	[DPLL_CMD_DEVICE_DELETE_NTF] = "device-delete-ntf",
	[DPLL_CMD_DEVICE_CHANGE_NTF] = "device-change-ntf",
	[DPLL_CMD_PIN_ID_GET] = "pin-id-get",
	[DPLL_CMD_PIN_GET] = "pin-get",
	[DPLL_CMD_PIN_SET] = "pin-set",
	[DPLL_CMD_PIN_CREATE_NTF] = "pin-create-ntf",
	[DPLL_CMD_PIN_DELETE_NTF] = "pin-delete-ntf",
	[DPLL_CMD_PIN_CHANGE_NTF] = "pin-change-ntf",
};

const char *dpll_op_str(int op)
{
	if (op < 0 || op >= (int)MNL_ARRAY_SIZE(dpll_op_strmap))
		return NULL;
	return dpll_op_strmap[op];
}

static const char * const dpll_mode_strmap[] = {
	[1] = "manual",
	[2] = "automatic",
	[3] = "holdover",
	[4] = "freerun",
};

const char *dpll_mode_str(enum dpll_mode value)
{
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_mode_strmap))
		return NULL;
	return dpll_mode_strmap[value];
}

static const char * const dpll_lock_status_strmap[] = {
	[1] = "unlocked",
	[2] = "locked",
	[3] = "locked-ho-acq",
	[4] = "holdover",
};

const char *dpll_lock_status_str(enum dpll_lock_status value)
{
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_lock_status_strmap))
		return NULL;
	return dpll_lock_status_strmap[value];
}

static const char * const dpll_type_strmap[] = {
	[1] = "pps",
	[2] = "eec",
};

const char *dpll_type_str(enum dpll_type value)
{
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_type_strmap))
		return NULL;
	return dpll_type_strmap[value];
}

static const char * const dpll_pin_type_strmap[] = {
	[1] = "mux",
	[2] = "ext",
	[3] = "synce-eth-port",
	[4] = "int-oscillator",
	[5] = "gnss",
};

const char *dpll_pin_type_str(enum dpll_pin_type value)
{
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_pin_type_strmap))
		return NULL;
	return dpll_pin_type_strmap[value];
}

static const char * const dpll_pin_direction_strmap[] = {
	[1] = "input",
	[2] = "output",
};

const char *dpll_pin_direction_str(enum dpll_pin_direction value)
{
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_pin_direction_strmap))
		return NULL;
	return dpll_pin_direction_strmap[value];
}

static const char * const dpll_pin_state_strmap[] = {
	[1] = "connected",
	[2] = "disconnected",
	[3] = "selectable",
};

const char *dpll_pin_state_str(enum dpll_pin_state value)
{
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_pin_state_strmap))
		return NULL;
	return dpll_pin_state_strmap[value];
}

static const char * const dpll_pin_caps_strmap[] = {
	[0] = "direction-can-change",
	[1] = "priority-can-change",
	[2] = "state-can-change",
};

const char *dpll_pin_caps_str(enum dpll_pin_caps value)
{
	value = ffs(value) - 1;
	if (value < 0 || value >= (int)MNL_ARRAY_SIZE(dpll_pin_caps_strmap))
		return NULL;
	return dpll_pin_caps_strmap[value];
}

/* Policies */
struct ynl_policy_attr dpll_pin_frequency_range_policy[DPLL_A_MAX + 1] = {
	[DPLL_A_PIN_FREQUENCY_MIN] = { .name = "pin-frequency-min", .type = YNL_PT_U64, },
	[DPLL_A_PIN_FREQUENCY_MAX] = { .name = "pin-frequency-max", .type = YNL_PT_U64, },
};

struct ynl_policy_nest dpll_pin_frequency_range_nest = {
	.max_attr = DPLL_A_MAX,
	.table = dpll_pin_frequency_range_policy,
};

struct ynl_policy_attr dpll_pin_parent_policy[DPLL_A_MAX + 1] = {
	[DPLL_A_ID] = { .name = "id", .type = YNL_PT_U32, },
	[DPLL_A_PIN_DIRECTION] = { .name = "pin-direction", .type = YNL_PT_U8, },
	[DPLL_A_PIN_PRIO] = { .name = "pin-prio", .type = YNL_PT_U32, },
	[DPLL_A_PIN_STATE] = { .name = "pin-state", .type = YNL_PT_U8, },
	[DPLL_A_PIN_ID] = { .name = "pin-id", .type = YNL_PT_U32, },
};

struct ynl_policy_nest dpll_pin_parent_nest = {
	.max_attr = DPLL_A_MAX,
	.table = dpll_pin_parent_policy,
};

struct ynl_policy_attr dpll_policy[DPLL_A_MAX + 1] = {
	[DPLL_A_ID] = { .name = "id", .type = YNL_PT_U32, },
	[DPLL_A_MODULE_NAME] = { .name = "module-name", .type = YNL_PT_NUL_STR, },
	[DPLL_A_CLOCK_ID] = { .name = "clock-id", .type = YNL_PT_U64, },
	[DPLL_A_MODE] = { .name = "mode", .type = YNL_PT_U8, },
	[DPLL_A_MODE_SUPPORTED] = { .name = "mode-supported", .type = YNL_PT_U8, },
	[DPLL_A_LOCK_STATUS] = { .name = "lock-status", .type = YNL_PT_U8, },
	[DPLL_A_TEMP] = { .name = "temp", .type = YNL_PT_U32, },
	[DPLL_A_TYPE] = { .name = "type", .type = YNL_PT_U8, },
	[DPLL_A_PIN_ID] = { .name = "pin-id", .type = YNL_PT_U32, },
	[DPLL_A_PIN_BOARD_LABEL] = { .name = "pin-board-label", .type = YNL_PT_NUL_STR, },
	[DPLL_A_PIN_PANEL_LABEL] = { .name = "pin-panel-label", .type = YNL_PT_NUL_STR, },
	[DPLL_A_PIN_PACKAGE_LABEL] = { .name = "pin-package-label", .type = YNL_PT_NUL_STR, },
	[DPLL_A_PIN_TYPE] = { .name = "pin-type", .type = YNL_PT_U8, },
	[DPLL_A_PIN_DIRECTION] = { .name = "pin-direction", .type = YNL_PT_U8, },
	[DPLL_A_PIN_FREQUENCY] = { .name = "pin-frequency", .type = YNL_PT_U64, },
	[DPLL_A_PIN_FREQUENCY_SUPPORTED] = { .name = "pin-frequency-supported", .type = YNL_PT_NEST, .nest = &dpll_pin_frequency_range_nest, },
	[DPLL_A_PIN_FREQUENCY_MIN] = { .name = "pin-frequency-min", .type = YNL_PT_U64, },
	[DPLL_A_PIN_FREQUENCY_MAX] = { .name = "pin-frequency-max", .type = YNL_PT_U64, },
	[DPLL_A_PIN_PRIO] = { .name = "pin-prio", .type = YNL_PT_U32, },
	[DPLL_A_PIN_STATE] = { .name = "pin-state", .type = YNL_PT_U8, },
	[DPLL_A_PIN_DPLL_CAPS] = { .name = "pin-dpll-caps", .type = YNL_PT_U32, },
	[DPLL_A_PIN_PARENT] = { .name = "pin-parent", .type = YNL_PT_NEST, .nest = &dpll_pin_parent_nest, },
};

struct ynl_policy_nest dpll_nest = {
	.max_attr = DPLL_A_MAX,
	.table = dpll_policy,
};

/* Common nested types */
void dpll_pin_frequency_range_free(struct dpll_pin_frequency_range *obj)
{
}

int dpll_pin_frequency_range_parse(struct ynl_parse_arg *yarg,
				   const struct nlattr *nested)
{
	struct dpll_pin_frequency_range *dst = yarg->data;
	const struct nlattr *attr;

	mnl_attr_for_each_nested(attr, nested) {
		unsigned int type = mnl_attr_get_type(attr);

		if (type == DPLL_A_PIN_FREQUENCY_MIN) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_frequency_min = 1;
			dst->pin_frequency_min = mnl_attr_get_u64(attr);
		} else if (type == DPLL_A_PIN_FREQUENCY_MAX) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_frequency_max = 1;
			dst->pin_frequency_max = mnl_attr_get_u64(attr);
		}
	}

	return 0;
}

void dpll_pin_parent_free(struct dpll_pin_parent *obj)
{
}

int dpll_pin_parent_put(struct nlmsghdr *nlh, unsigned int attr_type,
			struct dpll_pin_parent *obj)
{
	struct nlattr *nest;

	nest = mnl_attr_nest_start(nlh, attr_type);
	if (obj->_present.id)
		mnl_attr_put_u32(nlh, DPLL_A_ID, obj->id);
	if (obj->_present.pin_direction)
		mnl_attr_put_u8(nlh, DPLL_A_PIN_DIRECTION, obj->pin_direction);
	if (obj->_present.pin_prio)
		mnl_attr_put_u32(nlh, DPLL_A_PIN_PRIO, obj->pin_prio);
	if (obj->_present.pin_state)
		mnl_attr_put_u8(nlh, DPLL_A_PIN_STATE, obj->pin_state);
	if (obj->_present.pin_id)
		mnl_attr_put_u32(nlh, DPLL_A_PIN_ID, obj->pin_id);
	mnl_attr_nest_end(nlh, nest);

	return 0;
}

int dpll_pin_parent_parse(struct ynl_parse_arg *yarg,
			  const struct nlattr *nested)
{
	struct dpll_pin_parent *dst = yarg->data;
	const struct nlattr *attr;

	mnl_attr_for_each_nested(attr, nested) {
		unsigned int type = mnl_attr_get_type(attr);

		if (type == DPLL_A_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.id = 1;
			dst->id = mnl_attr_get_u32(attr);
		} else if (type == DPLL_A_PIN_DIRECTION) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_direction = 1;
			dst->pin_direction = mnl_attr_get_u8(attr);
		} else if (type == DPLL_A_PIN_PRIO) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_prio = 1;
			dst->pin_prio = mnl_attr_get_u32(attr);
		} else if (type == DPLL_A_PIN_STATE) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_state = 1;
			dst->pin_state = mnl_attr_get_u8(attr);
		} else if (type == DPLL_A_PIN_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_id = 1;
			dst->pin_id = mnl_attr_get_u32(attr);
		}
	}

	return 0;
}

/* ============== DPLL_CMD_DEVICE_ID_GET ============== */
/* DPLL_CMD_DEVICE_ID_GET - do */
void dpll_device_id_get_req_free(struct dpll_device_id_get_req *req)
{
	free(req->module_name);
	free(req);
}

void dpll_device_id_get_rsp_free(struct dpll_device_id_get_rsp *rsp)
{
	free(rsp);
}

int dpll_device_id_get_rsp_parse(const struct nlmsghdr *nlh, void *data)
{
	struct dpll_device_id_get_rsp *dst;
	struct ynl_parse_arg *yarg = data;
	const struct nlattr *attr;

	dst = yarg->data;

	mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
		unsigned int type = mnl_attr_get_type(attr);

		if (type == DPLL_A_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.id = 1;
			dst->id = mnl_attr_get_u32(attr);
		}
	}

	return MNL_CB_OK;
}

struct dpll_device_id_get_rsp *
dpll_device_id_get(struct ynl_sock *ys, struct dpll_device_id_get_req *req)
{
	struct ynl_req_state yrs = { .yarg = { .ys = ys, }, };
	struct dpll_device_id_get_rsp *rsp;
	struct nlmsghdr *nlh;
	int err;

	nlh = ynl_gemsg_start_req(ys, ys->family_id, DPLL_CMD_DEVICE_ID_GET, 1);
	ys->req_policy = &dpll_nest;
	yrs.yarg.rsp_policy = &dpll_nest;

	if (req->_present.module_name_len)
		mnl_attr_put_strz(nlh, DPLL_A_MODULE_NAME, req->module_name);
	if (req->_present.clock_id)
		mnl_attr_put_u64(nlh, DPLL_A_CLOCK_ID, req->clock_id);
	if (req->_present.type)
		mnl_attr_put_u8(nlh, DPLL_A_TYPE, req->type);

	rsp = calloc(1, sizeof(*rsp));
	yrs.yarg.data = rsp;
	yrs.cb = dpll_device_id_get_rsp_parse;
	yrs.rsp_cmd = DPLL_CMD_DEVICE_ID_GET;

	err = ynl_exec(ys, nlh, &yrs);
	if (err < 0)
		goto err_free;

	return rsp;

err_free:
	dpll_device_id_get_rsp_free(rsp);
	return NULL;
}

/* ============== DPLL_CMD_DEVICE_GET ============== */
/* DPLL_CMD_DEVICE_GET - do */
void dpll_device_get_req_free(struct dpll_device_get_req *req)
{
	free(req->module_name);
	free(req);
}

void dpll_device_get_rsp_free(struct dpll_device_get_rsp *rsp)
{
	free(rsp->module_name);
	free(rsp->mode_supported);
	free(rsp);
}

int dpll_device_get_rsp_parse(const struct nlmsghdr *nlh, void *data)
{
	struct ynl_parse_arg *yarg = data;
	unsigned int n_mode_supported = 0;
	struct dpll_device_get_rsp *dst;
	const struct nlattr *attr;
	int i;

	dst = yarg->data;

	if (dst->mode_supported)
		return ynl_error_parse(yarg, "attribute already present (dpll.mode-supported)");

	mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
		unsigned int type = mnl_attr_get_type(attr);

		if (type == DPLL_A_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.id = 1;
			dst->id = mnl_attr_get_u32(attr);
		} else if (type == DPLL_A_MODULE_NAME) {
			unsigned int len;

			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;

			len = strnlen(mnl_attr_get_str(attr), mnl_attr_get_payload_len(attr));
			dst->_present.module_name_len = len;
			dst->module_name = malloc(len + 1);
			memcpy(dst->module_name, mnl_attr_get_str(attr), len);
			dst->module_name[len] = 0;
		} else if (type == DPLL_A_MODE) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.mode = 1;
			dst->mode = mnl_attr_get_u8(attr);
		} else if (type == DPLL_A_MODE_SUPPORTED) {
			n_mode_supported++;
		} else if (type == DPLL_A_LOCK_STATUS) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.lock_status = 1;
			dst->lock_status = mnl_attr_get_u8(attr);
		} else if (type == DPLL_A_TEMP) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.temp = 1;
			dst->temp = mnl_attr_get_u32(attr);
		} else if (type == DPLL_A_CLOCK_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.clock_id = 1;
			dst->clock_id = mnl_attr_get_u64(attr);
		} else if (type == DPLL_A_TYPE) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.type = 1;
			dst->type = mnl_attr_get_u8(attr);
		}
	}

	if (n_mode_supported) {
		dst->mode_supported = calloc(n_mode_supported, sizeof(*dst->mode_supported));
		dst->n_mode_supported = n_mode_supported;
		i = 0;
		mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
			if (mnl_attr_get_type(attr) == DPLL_A_MODE_SUPPORTED) {
				dst->mode_supported[i] = mnl_attr_get_u8(attr);
				i++;
			}
		}
	}

	return MNL_CB_OK;
}

struct dpll_device_get_rsp *
dpll_device_get(struct ynl_sock *ys, struct dpll_device_get_req *req)
{
	struct ynl_req_state yrs = { .yarg = { .ys = ys, }, };
	struct dpll_device_get_rsp *rsp;
	struct nlmsghdr *nlh;
	int err;

	nlh = ynl_gemsg_start_req(ys, ys->family_id, DPLL_CMD_DEVICE_GET, 1);
	ys->req_policy = &dpll_nest;
	yrs.yarg.rsp_policy = &dpll_nest;

	if (req->_present.id)
		mnl_attr_put_u32(nlh, DPLL_A_ID, req->id);
	if (req->_present.module_name_len)
		mnl_attr_put_strz(nlh, DPLL_A_MODULE_NAME, req->module_name);

	rsp = calloc(1, sizeof(*rsp));
	yrs.yarg.data = rsp;
	yrs.cb = dpll_device_get_rsp_parse;
	yrs.rsp_cmd = DPLL_CMD_DEVICE_GET;

	err = ynl_exec(ys, nlh, &yrs);
	if (err < 0)
		goto err_free;

	return rsp;

err_free:
	dpll_device_get_rsp_free(rsp);
	return NULL;
}

/* DPLL_CMD_DEVICE_GET - dump */
void dpll_device_get_list_free(struct dpll_device_get_list *rsp)
{
	struct dpll_device_get_list *next = rsp;

	while ((void *)next != YNL_LIST_END) {
		rsp = next;
		next = rsp->next;

		free(rsp->obj.module_name);
		free(rsp->obj.mode_supported);
		free(rsp);
	}
}

struct dpll_device_get_list *dpll_device_get_dump(struct ynl_sock *ys)
{
	struct ynl_dump_state yds = {};
	struct nlmsghdr *nlh;
	int err;

	yds.ys = ys;
	yds.alloc_sz = sizeof(struct dpll_device_get_list);
	yds.cb = dpll_device_get_rsp_parse;
	yds.rsp_cmd = DPLL_CMD_DEVICE_GET;
	yds.rsp_policy = &dpll_nest;

	nlh = ynl_gemsg_start_dump(ys, ys->family_id, DPLL_CMD_DEVICE_GET, 1);

	err = ynl_exec_dump(ys, nlh, &yds);
	if (err < 0)
		goto free_list;

	return yds.first;

free_list:
	dpll_device_get_list_free(yds.first);
	return NULL;
}

/* DPLL_CMD_DEVICE_GET - notify */
void dpll_device_get_ntf_free(struct dpll_device_get_ntf *rsp)
{
	free(rsp->obj.module_name);
	free(rsp->obj.mode_supported);
	free(rsp);
}

/* ============== DPLL_CMD_DEVICE_SET ============== */
/* DPLL_CMD_DEVICE_SET - do */
void dpll_device_set_req_free(struct dpll_device_set_req *req)
{
	free(req);
}

int dpll_device_set(struct ynl_sock *ys, struct dpll_device_set_req *req)
{
	struct nlmsghdr *nlh;
	int err;

	nlh = ynl_gemsg_start_req(ys, ys->family_id, DPLL_CMD_DEVICE_SET, 1);
	ys->req_policy = &dpll_nest;

	if (req->_present.id)
		mnl_attr_put_u32(nlh, DPLL_A_ID, req->id);
	if (req->_present.mode)
		mnl_attr_put_u8(nlh, DPLL_A_MODE, req->mode);

	err = ynl_exec(ys, nlh, NULL);
	if (err < 0)
		return -1;

	return 0;
}

/* ============== DPLL_CMD_PIN_ID_GET ============== */
/* DPLL_CMD_PIN_ID_GET - do */
void dpll_pin_id_get_req_free(struct dpll_pin_id_get_req *req)
{
	free(req->module_name);
	free(req->pin_board_label);
	free(req->pin_panel_label);
	free(req->pin_package_label);
	free(req);
}

void dpll_pin_id_get_rsp_free(struct dpll_pin_id_get_rsp *rsp)
{
	free(rsp);
}

int dpll_pin_id_get_rsp_parse(const struct nlmsghdr *nlh, void *data)
{
	struct ynl_parse_arg *yarg = data;
	struct dpll_pin_id_get_rsp *dst;
	const struct nlattr *attr;

	dst = yarg->data;

	mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
		unsigned int type = mnl_attr_get_type(attr);

		if (type == DPLL_A_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.id = 1;
			dst->id = mnl_attr_get_u32(attr);
		}
	}

	return MNL_CB_OK;
}

struct dpll_pin_id_get_rsp *
dpll_pin_id_get(struct ynl_sock *ys, struct dpll_pin_id_get_req *req)
{
	struct ynl_req_state yrs = { .yarg = { .ys = ys, }, };
	struct dpll_pin_id_get_rsp *rsp;
	struct nlmsghdr *nlh;
	int err;

	nlh = ynl_gemsg_start_req(ys, ys->family_id, DPLL_CMD_PIN_ID_GET, 1);
	ys->req_policy = &dpll_nest;
	yrs.yarg.rsp_policy = &dpll_nest;

	if (req->_present.module_name_len)
		mnl_attr_put_strz(nlh, DPLL_A_MODULE_NAME, req->module_name);
	if (req->_present.clock_id)
		mnl_attr_put_u64(nlh, DPLL_A_CLOCK_ID, req->clock_id);
	if (req->_present.pin_board_label_len)
		mnl_attr_put_strz(nlh, DPLL_A_PIN_BOARD_LABEL, req->pin_board_label);
	if (req->_present.pin_panel_label_len)
		mnl_attr_put_strz(nlh, DPLL_A_PIN_PANEL_LABEL, req->pin_panel_label);
	if (req->_present.pin_package_label_len)
		mnl_attr_put_strz(nlh, DPLL_A_PIN_PACKAGE_LABEL, req->pin_package_label);
	if (req->_present.pin_type)
		mnl_attr_put_u8(nlh, DPLL_A_PIN_TYPE, req->pin_type);

	rsp = calloc(1, sizeof(*rsp));
	yrs.yarg.data = rsp;
	yrs.cb = dpll_pin_id_get_rsp_parse;
	yrs.rsp_cmd = DPLL_CMD_PIN_ID_GET;

	err = ynl_exec(ys, nlh, &yrs);
	if (err < 0)
		goto err_free;

	return rsp;

err_free:
	dpll_pin_id_get_rsp_free(rsp);
	return NULL;
}

/* ============== DPLL_CMD_PIN_GET ============== */
/* DPLL_CMD_PIN_GET - do */
void dpll_pin_get_req_free(struct dpll_pin_get_req *req)
{
	free(req);
}

void dpll_pin_get_rsp_free(struct dpll_pin_get_rsp *rsp)
{
	unsigned int i;

	free(rsp->pin_board_label);
	free(rsp->pin_panel_label);
	free(rsp->pin_package_label);
	for (i = 0; i < rsp->n_pin_frequency_supported; i++)
		dpll_pin_frequency_range_free(&rsp->pin_frequency_supported[i]);
	free(rsp->pin_frequency_supported);
	for (i = 0; i < rsp->n_pin_parent; i++)
		dpll_pin_parent_free(&rsp->pin_parent[i]);
	free(rsp->pin_parent);
	free(rsp);
}

int dpll_pin_get_rsp_parse(const struct nlmsghdr *nlh, void *data)
{
	unsigned int n_pin_frequency_supported = 0;
	struct ynl_parse_arg *yarg = data;
	unsigned int n_pin_parent = 0;
	struct dpll_pin_get_rsp *dst;
	const struct nlattr *attr;
	struct ynl_parse_arg parg;
	int i;

	dst = yarg->data;
	parg.ys = yarg->ys;

	if (dst->pin_frequency_supported)
		return ynl_error_parse(yarg, "attribute already present (dpll.pin-frequency-supported)");
	if (dst->pin_parent)
		return ynl_error_parse(yarg, "attribute already present (dpll.pin-parent)");

	mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
		unsigned int type = mnl_attr_get_type(attr);

		if (type == DPLL_A_PIN_ID) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_id = 1;
			dst->pin_id = mnl_attr_get_u32(attr);
		} else if (type == DPLL_A_PIN_BOARD_LABEL) {
			unsigned int len;

			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;

			len = strnlen(mnl_attr_get_str(attr), mnl_attr_get_payload_len(attr));
			dst->_present.pin_board_label_len = len;
			dst->pin_board_label = malloc(len + 1);
			memcpy(dst->pin_board_label, mnl_attr_get_str(attr), len);
			dst->pin_board_label[len] = 0;
		} else if (type == DPLL_A_PIN_PANEL_LABEL) {
			unsigned int len;

			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;

			len = strnlen(mnl_attr_get_str(attr), mnl_attr_get_payload_len(attr));
			dst->_present.pin_panel_label_len = len;
			dst->pin_panel_label = malloc(len + 1);
			memcpy(dst->pin_panel_label, mnl_attr_get_str(attr), len);
			dst->pin_panel_label[len] = 0;
		} else if (type == DPLL_A_PIN_PACKAGE_LABEL) {
			unsigned int len;

			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;

			len = strnlen(mnl_attr_get_str(attr), mnl_attr_get_payload_len(attr));
			dst->_present.pin_package_label_len = len;
			dst->pin_package_label = malloc(len + 1);
			memcpy(dst->pin_package_label, mnl_attr_get_str(attr), len);
			dst->pin_package_label[len] = 0;
		} else if (type == DPLL_A_PIN_TYPE) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_type = 1;
			dst->pin_type = mnl_attr_get_u8(attr);
		} else if (type == DPLL_A_PIN_FREQUENCY) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_frequency = 1;
			dst->pin_frequency = mnl_attr_get_u64(attr);
		} else if (type == DPLL_A_PIN_FREQUENCY_SUPPORTED) {
			n_pin_frequency_supported++;
		} else if (type == DPLL_A_PIN_PARENT) {
			n_pin_parent++;
		} else if (type == DPLL_A_PIN_DPLL_CAPS) {
			if (ynl_attr_validate(yarg, attr))
				return MNL_CB_ERROR;
			dst->_present.pin_dpll_caps = 1;
			dst->pin_dpll_caps = mnl_attr_get_u32(attr);
		}
	}

	if (n_pin_frequency_supported) {
		dst->pin_frequency_supported = calloc(n_pin_frequency_supported, sizeof(*dst->pin_frequency_supported));
		dst->n_pin_frequency_supported = n_pin_frequency_supported;
		i = 0;
		parg.rsp_policy = &dpll_pin_frequency_range_nest;
		mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
			if (mnl_attr_get_type(attr) == DPLL_A_PIN_FREQUENCY_SUPPORTED) {
				parg.data = &dst->pin_frequency_supported[i];
				if (dpll_pin_frequency_range_parse(&parg, attr))
					return MNL_CB_ERROR;
				i++;
			}
		}
	}
	if (n_pin_parent) {
		dst->pin_parent = calloc(n_pin_parent, sizeof(*dst->pin_parent));
		dst->n_pin_parent = n_pin_parent;
		i = 0;
		parg.rsp_policy = &dpll_pin_parent_nest;
		mnl_attr_for_each(attr, nlh, sizeof(struct genlmsghdr)) {
			if (mnl_attr_get_type(attr) == DPLL_A_PIN_PARENT) {
				parg.data = &dst->pin_parent[i];
				if (dpll_pin_parent_parse(&parg, attr))
					return MNL_CB_ERROR;
				i++;
			}
		}
	}

	return MNL_CB_OK;
}

struct dpll_pin_get_rsp *
dpll_pin_get(struct ynl_sock *ys, struct dpll_pin_get_req *req)
{
	struct ynl_req_state yrs = { .yarg = { .ys = ys, }, };
	struct dpll_pin_get_rsp *rsp;
	struct nlmsghdr *nlh;
	int err;

	nlh = ynl_gemsg_start_req(ys, ys->family_id, DPLL_CMD_PIN_GET, 1);
	ys->req_policy = &dpll_nest;
	yrs.yarg.rsp_policy = &dpll_nest;

	if (req->_present.id)
		mnl_attr_put_u32(nlh, DPLL_A_ID, req->id);
	if (req->_present.pin_id)
		mnl_attr_put_u32(nlh, DPLL_A_PIN_ID, req->pin_id);

	rsp = calloc(1, sizeof(*rsp));
	yrs.yarg.data = rsp;
	yrs.cb = dpll_pin_get_rsp_parse;
	yrs.rsp_cmd = DPLL_CMD_PIN_GET;

	err = ynl_exec(ys, nlh, &yrs);
	if (err < 0)
		goto err_free;

	return rsp;

err_free:
	dpll_pin_get_rsp_free(rsp);
	return NULL;
}

/* DPLL_CMD_PIN_GET - dump */
void dpll_pin_get_list_free(struct dpll_pin_get_list *rsp)
{
	struct dpll_pin_get_list *next = rsp;

	while ((void *)next != YNL_LIST_END) {
		unsigned int i;

		rsp = next;
		next = rsp->next;

		free(rsp->obj.pin_board_label);
		free(rsp->obj.pin_panel_label);
		free(rsp->obj.pin_package_label);
		for (i = 0; i < rsp->obj.n_pin_frequency_supported; i++)
			dpll_pin_frequency_range_free(&rsp->obj.pin_frequency_supported[i]);
		free(rsp->obj.pin_frequency_supported);
		for (i = 0; i < rsp->obj.n_pin_parent; i++)
			dpll_pin_parent_free(&rsp->obj.pin_parent[i]);
		free(rsp->obj.pin_parent);
		free(rsp);
	}
}

struct dpll_pin_get_list *
dpll_pin_get_dump(struct ynl_sock *ys, struct dpll_pin_get_req_dump *req)
{
	struct ynl_dump_state yds = {};
	struct nlmsghdr *nlh;
	int err;

	yds.ys = ys;
	yds.alloc_sz = sizeof(struct dpll_pin_get_list);
	yds.cb = dpll_pin_get_rsp_parse;
	yds.rsp_cmd = DPLL_CMD_PIN_GET;
	yds.rsp_policy = &dpll_nest;

	nlh = ynl_gemsg_start_dump(ys, ys->family_id, DPLL_CMD_PIN_GET, 1);
	ys->req_policy = &dpll_nest;

	if (req->_present.id)
		mnl_attr_put_u32(nlh, DPLL_A_ID, req->id);

	err = ynl_exec_dump(ys, nlh, &yds);
	if (err < 0)
		goto free_list;

	return yds.first;

free_list:
	dpll_pin_get_list_free(yds.first);
	return NULL;
}

/* DPLL_CMD_PIN_GET - notify */
void dpll_pin_get_ntf_free(struct dpll_pin_get_ntf *rsp)
{
	unsigned int i;

	free(rsp->obj.pin_board_label);
	free(rsp->obj.pin_panel_label);
	free(rsp->obj.pin_package_label);
	for (i = 0; i < rsp->obj.n_pin_frequency_supported; i++)
		dpll_pin_frequency_range_free(&rsp->obj.pin_frequency_supported[i]);
	free(rsp->obj.pin_frequency_supported);
	for (i = 0; i < rsp->obj.n_pin_parent; i++)
		dpll_pin_parent_free(&rsp->obj.pin_parent[i]);
	free(rsp->obj.pin_parent);
	free(rsp);
}

/* ============== DPLL_CMD_PIN_SET ============== */
/* DPLL_CMD_PIN_SET - do */
void dpll_pin_set_req_free(struct dpll_pin_set_req *req)
{
	unsigned int i;

	for (i = 0; i < req->n_pin_parent; i++)
		dpll_pin_parent_free(&req->pin_parent[i]);
	free(req->pin_parent);
	free(req);
}

int dpll_pin_set(struct ynl_sock *ys, struct dpll_pin_set_req *req)
{
	struct nlmsghdr *nlh;
	int err;

	nlh = ynl_gemsg_start_req(ys, ys->family_id, DPLL_CMD_PIN_SET, 1);
	ys->req_policy = &dpll_nest;

	if (req->_present.id)
		mnl_attr_put_u32(nlh, DPLL_A_ID, req->id);
	if (req->_present.pin_id)
		mnl_attr_put_u32(nlh, DPLL_A_PIN_ID, req->pin_id);
	if (req->_present.pin_frequency)
		mnl_attr_put_u64(nlh, DPLL_A_PIN_FREQUENCY, req->pin_frequency);
	if (req->_present.pin_direction)
		mnl_attr_put_u8(nlh, DPLL_A_PIN_DIRECTION, req->pin_direction);
	if (req->_present.pin_prio)
		mnl_attr_put_u32(nlh, DPLL_A_PIN_PRIO, req->pin_prio);
	if (req->_present.pin_state)
		mnl_attr_put_u8(nlh, DPLL_A_PIN_STATE, req->pin_state);
	for (unsigned int i = 0; i < req->n_pin_parent; i++)
		dpll_pin_parent_put(nlh, DPLL_A_PIN_PARENT, &req->pin_parent[i]);

	err = ynl_exec(ys, nlh, NULL);
	if (err < 0)
		return -1;

	return 0;
}

static const struct ynl_ntf_info dpll_ntf_info[] =  {
	[DPLL_CMD_DEVICE_CREATE_NTF] =  {
		.alloc_sz	= sizeof(struct dpll_device_get_ntf),
		.cb		= dpll_device_get_rsp_parse,
		.policy		= &dpll_nest,
		.free		= (void *)dpll_device_get_ntf_free,
	},
	[DPLL_CMD_DEVICE_DELETE_NTF] =  {
		.alloc_sz	= sizeof(struct dpll_device_get_ntf),
		.cb		= dpll_device_get_rsp_parse,
		.policy		= &dpll_nest,
		.free		= (void *)dpll_device_get_ntf_free,
	},
	[DPLL_CMD_DEVICE_CHANGE_NTF] =  {
		.alloc_sz	= sizeof(struct dpll_device_get_ntf),
		.cb		= dpll_device_get_rsp_parse,
		.policy		= &dpll_nest,
		.free		= (void *)dpll_device_get_ntf_free,
	},
	[DPLL_CMD_PIN_CREATE_NTF] =  {
		.alloc_sz	= sizeof(struct dpll_pin_get_ntf),
		.cb		= dpll_pin_get_rsp_parse,
		.policy		= &dpll_nest,
		.free		= (void *)dpll_pin_get_ntf_free,
	},
	[DPLL_CMD_PIN_DELETE_NTF] =  {
		.alloc_sz	= sizeof(struct dpll_pin_get_ntf),
		.cb		= dpll_pin_get_rsp_parse,
		.policy		= &dpll_nest,
		.free		= (void *)dpll_pin_get_ntf_free,
	},
	[DPLL_CMD_PIN_CHANGE_NTF] =  {
		.alloc_sz	= sizeof(struct dpll_pin_get_ntf),
		.cb		= dpll_pin_get_rsp_parse,
		.policy		= &dpll_nest,
		.free		= (void *)dpll_pin_get_ntf_free,
	},
};

const struct ynl_family ynl_dpll_family =  {
	.name		= "dpll",
	.ntf_info	= dpll_ntf_info,
	.ntf_info_size	= MNL_ARRAY_SIZE(dpll_ntf_info),
};

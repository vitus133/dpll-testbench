/* SPDX-License-Identifier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/* Do not edit directly, auto-generated from: */
/*	kernel-root */
/* YNL-GEN user header */

#ifndef _LINUX_DPLL_GEN_H
#define _LINUX_DPLL_GEN_H

#include <stdlib.h>
#include <string.h>
#include <linux/types.h>
#include <linux/dpll.h>

struct ynl_sock;

extern const struct ynl_family ynl_dpll_family;

/* Enums */
const char *dpll_op_str(int op);
const char *dpll_mode_str(enum dpll_mode value);
const char *dpll_lock_status_str(enum dpll_lock_status value);
const char *dpll_type_str(enum dpll_type value);
const char *dpll_pin_type_str(enum dpll_pin_type value);
const char *dpll_pin_direction_str(enum dpll_pin_direction value);
const char *dpll_pin_state_str(enum dpll_pin_state value);
const char *dpll_pin_caps_str(enum dpll_pin_caps value);

/* Common nested types */
struct dpll_pin_frequency_range {
	struct {
		__u32 pin_frequency_min:1;
		__u32 pin_frequency_max:1;
	} _present;

	__u64 pin_frequency_min;
	__u64 pin_frequency_max;
};

struct dpll_pin_parent {
	struct {
		__u32 id:1;
		__u32 pin_direction:1;
		__u32 pin_prio:1;
		__u32 pin_state:1;
		__u32 pin_id:1;
	} _present;

	__u32 id;
	enum dpll_pin_direction pin_direction;
	__u32 pin_prio;
	enum dpll_pin_state pin_state;
	__u32 pin_id;
};

/* ============== DPLL_CMD_DEVICE_ID_GET ============== */
/* DPLL_CMD_DEVICE_ID_GET - do */
struct dpll_device_id_get_req {
	struct {
		__u32 module_name_len;
		__u32 clock_id:1;
		__u32 type:1;
	} _present;

	char *module_name;
	__u64 clock_id;
	enum dpll_type type;
};

static inline struct dpll_device_id_get_req *dpll_device_id_get_req_alloc(void)
{
	return calloc(1, sizeof(struct dpll_device_id_get_req));
}
void dpll_device_id_get_req_free(struct dpll_device_id_get_req *req);

static inline void
dpll_device_id_get_req_set_module_name(struct dpll_device_id_get_req *req,
				       const char *module_name)
{
	free(req->module_name);
	req->_present.module_name_len = strlen(module_name);
	req->module_name = malloc(req->_present.module_name_len + 1);
	memcpy(req->module_name, module_name, req->_present.module_name_len);
	req->module_name[req->_present.module_name_len] = 0;
}
static inline void
dpll_device_id_get_req_set_clock_id(struct dpll_device_id_get_req *req,
				    __u64 clock_id)
{
	req->_present.clock_id = 1;
	req->clock_id = clock_id;
}
static inline void
dpll_device_id_get_req_set_type(struct dpll_device_id_get_req *req,
				enum dpll_type type)
{
	req->_present.type = 1;
	req->type = type;
}

struct dpll_device_id_get_rsp {
	struct {
		__u32 id:1;
	} _present;

	__u32 id;
};

void dpll_device_id_get_rsp_free(struct dpll_device_id_get_rsp *rsp);

/*
 * Get id of dpll device that matches given attributes

 */
struct dpll_device_id_get_rsp *
dpll_device_id_get(struct ynl_sock *ys, struct dpll_device_id_get_req *req);

/* ============== DPLL_CMD_DEVICE_GET ============== */
/* DPLL_CMD_DEVICE_GET - do */
struct dpll_device_get_req {
	struct {
		__u32 id:1;
		__u32 module_name_len;
	} _present;

	__u32 id;
	char *module_name;
};

static inline struct dpll_device_get_req *dpll_device_get_req_alloc(void)
{
	return calloc(1, sizeof(struct dpll_device_get_req));
}
void dpll_device_get_req_free(struct dpll_device_get_req *req);

static inline void
dpll_device_get_req_set_id(struct dpll_device_get_req *req, __u32 id)
{
	req->_present.id = 1;
	req->id = id;
}
static inline void
dpll_device_get_req_set_module_name(struct dpll_device_get_req *req,
				    const char *module_name)
{
	free(req->module_name);
	req->_present.module_name_len = strlen(module_name);
	req->module_name = malloc(req->_present.module_name_len + 1);
	memcpy(req->module_name, module_name, req->_present.module_name_len);
	req->module_name[req->_present.module_name_len] = 0;
}

struct dpll_device_get_rsp {
	struct {
		__u32 id:1;
		__u32 module_name_len;
		__u32 mode:1;
		__u32 lock_status:1;
		__u32 temp:1;
		__u32 clock_id:1;
		__u32 type:1;
	} _present;

	__u32 id;
	char *module_name;
	enum dpll_mode mode;
	unsigned int n_mode_supported;
	__u8 *mode_supported;
	enum dpll_lock_status lock_status;
	__s32 temp;
	__u64 clock_id;
	enum dpll_type type;
};

void dpll_device_get_rsp_free(struct dpll_device_get_rsp *rsp);

/*
 * Get list of DPLL devices (dump) or attributes of a single dpll device

 */
struct dpll_device_get_rsp *
dpll_device_get(struct ynl_sock *ys, struct dpll_device_get_req *req);

/* DPLL_CMD_DEVICE_GET - dump */
struct dpll_device_get_list {
	struct dpll_device_get_list *next;
	struct dpll_device_get_rsp obj __attribute__ ((aligned (8)));
};

void dpll_device_get_list_free(struct dpll_device_get_list *rsp);

struct dpll_device_get_list *dpll_device_get_dump(struct ynl_sock *ys);

/* DPLL_CMD_DEVICE_GET - notify */
struct dpll_device_get_ntf {
	__u16 family;
	__u8 cmd;
	struct ynl_ntf_base_type *next;
	void (*free)(struct dpll_device_get_ntf *ntf);
	struct dpll_device_get_rsp obj __attribute__ ((aligned (8)));
};

void dpll_device_get_ntf_free(struct dpll_device_get_ntf *rsp);

/* ============== DPLL_CMD_DEVICE_SET ============== */
/* DPLL_CMD_DEVICE_SET - do */
struct dpll_device_set_req {
	struct {
		__u32 id:1;
		__u32 mode:1;
	} _present;

	__u32 id;
	enum dpll_mode mode;
};

static inline struct dpll_device_set_req *dpll_device_set_req_alloc(void)
{
	return calloc(1, sizeof(struct dpll_device_set_req));
}
void dpll_device_set_req_free(struct dpll_device_set_req *req);

static inline void
dpll_device_set_req_set_id(struct dpll_device_set_req *req, __u32 id)
{
	req->_present.id = 1;
	req->id = id;
}
static inline void
dpll_device_set_req_set_mode(struct dpll_device_set_req *req,
			     enum dpll_mode mode)
{
	req->_present.mode = 1;
	req->mode = mode;
}

/*
 * Set attributes for a DPLL device
 */
int dpll_device_set(struct ynl_sock *ys, struct dpll_device_set_req *req);

/* ============== DPLL_CMD_PIN_ID_GET ============== */
/* DPLL_CMD_PIN_ID_GET - do */
struct dpll_pin_id_get_req {
	struct {
		__u32 module_name_len;
		__u32 clock_id:1;
		__u32 pin_board_label_len;
		__u32 pin_panel_label_len;
		__u32 pin_package_label_len;
		__u32 pin_type:1;
	} _present;

	char *module_name;
	__u64 clock_id;
	char *pin_board_label;
	char *pin_panel_label;
	char *pin_package_label;
	enum dpll_pin_type pin_type;
};

static inline struct dpll_pin_id_get_req *dpll_pin_id_get_req_alloc(void)
{
	return calloc(1, sizeof(struct dpll_pin_id_get_req));
}
void dpll_pin_id_get_req_free(struct dpll_pin_id_get_req *req);

static inline void
dpll_pin_id_get_req_set_module_name(struct dpll_pin_id_get_req *req,
				    const char *module_name)
{
	free(req->module_name);
	req->_present.module_name_len = strlen(module_name);
	req->module_name = malloc(req->_present.module_name_len + 1);
	memcpy(req->module_name, module_name, req->_present.module_name_len);
	req->module_name[req->_present.module_name_len] = 0;
}
static inline void
dpll_pin_id_get_req_set_clock_id(struct dpll_pin_id_get_req *req,
				 __u64 clock_id)
{
	req->_present.clock_id = 1;
	req->clock_id = clock_id;
}
static inline void
dpll_pin_id_get_req_set_pin_board_label(struct dpll_pin_id_get_req *req,
					const char *pin_board_label)
{
	free(req->pin_board_label);
	req->_present.pin_board_label_len = strlen(pin_board_label);
	req->pin_board_label = malloc(req->_present.pin_board_label_len + 1);
	memcpy(req->pin_board_label, pin_board_label, req->_present.pin_board_label_len);
	req->pin_board_label[req->_present.pin_board_label_len] = 0;
}
static inline void
dpll_pin_id_get_req_set_pin_panel_label(struct dpll_pin_id_get_req *req,
					const char *pin_panel_label)
{
	free(req->pin_panel_label);
	req->_present.pin_panel_label_len = strlen(pin_panel_label);
	req->pin_panel_label = malloc(req->_present.pin_panel_label_len + 1);
	memcpy(req->pin_panel_label, pin_panel_label, req->_present.pin_panel_label_len);
	req->pin_panel_label[req->_present.pin_panel_label_len] = 0;
}
static inline void
dpll_pin_id_get_req_set_pin_package_label(struct dpll_pin_id_get_req *req,
					  const char *pin_package_label)
{
	free(req->pin_package_label);
	req->_present.pin_package_label_len = strlen(pin_package_label);
	req->pin_package_label = malloc(req->_present.pin_package_label_len + 1);
	memcpy(req->pin_package_label, pin_package_label, req->_present.pin_package_label_len);
	req->pin_package_label[req->_present.pin_package_label_len] = 0;
}
static inline void
dpll_pin_id_get_req_set_pin_type(struct dpll_pin_id_get_req *req,
				 enum dpll_pin_type pin_type)
{
	req->_present.pin_type = 1;
	req->pin_type = pin_type;
}

struct dpll_pin_id_get_rsp {
	struct {
		__u32 id:1;
	} _present;

	__u32 id;
};

void dpll_pin_id_get_rsp_free(struct dpll_pin_id_get_rsp *rsp);

/*
 * Get id of a pin that matches given attributes

 */
struct dpll_pin_id_get_rsp *
dpll_pin_id_get(struct ynl_sock *ys, struct dpll_pin_id_get_req *req);

/* ============== DPLL_CMD_PIN_GET ============== */
/* DPLL_CMD_PIN_GET - do */
struct dpll_pin_get_req {
	struct {
		__u32 id:1;
		__u32 pin_id:1;
	} _present;

	__u32 id;
	__u32 pin_id;
};

static inline struct dpll_pin_get_req *dpll_pin_get_req_alloc(void)
{
	return calloc(1, sizeof(struct dpll_pin_get_req));
}
void dpll_pin_get_req_free(struct dpll_pin_get_req *req);

static inline void
dpll_pin_get_req_set_id(struct dpll_pin_get_req *req, __u32 id)
{
	req->_present.id = 1;
	req->id = id;
}
static inline void
dpll_pin_get_req_set_pin_id(struct dpll_pin_get_req *req, __u32 pin_id)
{
	req->_present.pin_id = 1;
	req->pin_id = pin_id;
}

struct dpll_pin_get_rsp {
	struct {
		__u32 pin_id:1;
		__u32 pin_board_label_len;
		__u32 pin_panel_label_len;
		__u32 pin_package_label_len;
		__u32 pin_type:1;
		__u32 pin_frequency:1;
		__u32 pin_dpll_caps:1;
	} _present;

	__u32 pin_id;
	char *pin_board_label;
	char *pin_panel_label;
	char *pin_package_label;
	enum dpll_pin_type pin_type;
	__u64 pin_frequency;
	unsigned int n_pin_frequency_supported;
	struct dpll_pin_frequency_range *pin_frequency_supported;
	unsigned int n_pin_parent;
	struct dpll_pin_parent *pin_parent;
	__u32 pin_dpll_caps;
};

void dpll_pin_get_rsp_free(struct dpll_pin_get_rsp *rsp);

/*
 * Get list of pins and its attributes.
- dump request without any attributes given - list all the pins in the
  system
- dump request with target dpll - list all the pins registered with
  a given dpll device
- do request with target dpll and target pin - single pin attributes

 */
struct dpll_pin_get_rsp *
dpll_pin_get(struct ynl_sock *ys, struct dpll_pin_get_req *req);

/* DPLL_CMD_PIN_GET - dump */
struct dpll_pin_get_req_dump {
	struct {
		__u32 id:1;
	} _present;

	__u32 id;
};

static inline struct dpll_pin_get_req_dump *dpll_pin_get_req_dump_alloc(void)
{
	return calloc(1, sizeof(struct dpll_pin_get_req_dump));
}
void dpll_pin_get_req_dump_free(struct dpll_pin_get_req_dump *req);

static inline void
dpll_pin_get_req_dump_set_id(struct dpll_pin_get_req_dump *req, __u32 id)
{
	req->_present.id = 1;
	req->id = id;
}

struct dpll_pin_get_list {
	struct dpll_pin_get_list *next;
	struct dpll_pin_get_rsp obj __attribute__ ((aligned (8)));
};

void dpll_pin_get_list_free(struct dpll_pin_get_list *rsp);

struct dpll_pin_get_list *
dpll_pin_get_dump(struct ynl_sock *ys, struct dpll_pin_get_req_dump *req);

/* DPLL_CMD_PIN_GET - notify */
struct dpll_pin_get_ntf {
	__u16 family;
	__u8 cmd;
	struct ynl_ntf_base_type *next;
	void (*free)(struct dpll_pin_get_ntf *ntf);
	struct dpll_pin_get_rsp obj __attribute__ ((aligned (8)));
};

void dpll_pin_get_ntf_free(struct dpll_pin_get_ntf *rsp);

/* ============== DPLL_CMD_PIN_SET ============== */
/* DPLL_CMD_PIN_SET - do */
struct dpll_pin_set_req {
	struct {
		__u32 id:1;
		__u32 pin_id:1;
		__u32 pin_frequency:1;
		__u32 pin_direction:1;
		__u32 pin_prio:1;
		__u32 pin_state:1;
	} _present;

	__u32 id;
	__u32 pin_id;
	__u64 pin_frequency;
	enum dpll_pin_direction pin_direction;
	__u32 pin_prio;
	enum dpll_pin_state pin_state;
	unsigned int n_pin_parent;
	struct dpll_pin_parent *pin_parent;
};

static inline struct dpll_pin_set_req *dpll_pin_set_req_alloc(void)
{
	return calloc(1, sizeof(struct dpll_pin_set_req));
}
void dpll_pin_set_req_free(struct dpll_pin_set_req *req);

static inline void
dpll_pin_set_req_set_id(struct dpll_pin_set_req *req, __u32 id)
{
	req->_present.id = 1;
	req->id = id;
}
static inline void
dpll_pin_set_req_set_pin_id(struct dpll_pin_set_req *req, __u32 pin_id)
{
	req->_present.pin_id = 1;
	req->pin_id = pin_id;
}
static inline void
dpll_pin_set_req_set_pin_frequency(struct dpll_pin_set_req *req,
				   __u64 pin_frequency)
{
	req->_present.pin_frequency = 1;
	req->pin_frequency = pin_frequency;
}
static inline void
dpll_pin_set_req_set_pin_direction(struct dpll_pin_set_req *req,
				   enum dpll_pin_direction pin_direction)
{
	req->_present.pin_direction = 1;
	req->pin_direction = pin_direction;
}
static inline void
dpll_pin_set_req_set_pin_prio(struct dpll_pin_set_req *req, __u32 pin_prio)
{
	req->_present.pin_prio = 1;
	req->pin_prio = pin_prio;
}
static inline void
dpll_pin_set_req_set_pin_state(struct dpll_pin_set_req *req,
			       enum dpll_pin_state pin_state)
{
	req->_present.pin_state = 1;
	req->pin_state = pin_state;
}
static inline void
__dpll_pin_set_req_set_pin_parent(struct dpll_pin_set_req *req,
				  struct dpll_pin_parent *pin_parent,
				  unsigned int n_pin_parent)
{
	free(req->pin_parent);
	req->pin_parent = pin_parent;
	req->n_pin_parent = n_pin_parent;
}

/*
 * Set attributes of a target pin
 */
int dpll_pin_set(struct ynl_sock *ys, struct dpll_pin_set_req *req);

#endif /* _LINUX_DPLL_GEN_H */

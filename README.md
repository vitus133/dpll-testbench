# DPLL testbench

This repository contains a usage example for Linux DPLL API and 
generic Netlink CLI. 
Intel Ice driver for E810 cards relies on Linux DPLL driver for 
DPLL device queries, configuration and notifications through generic netlink.

The testbench contains kernel module built around Linux DPLL API, and a copy
of user space Python CLI for interacting with the module through generic netlink.

## Prerequisites
libmnl and libmnl-devel

Install with

```bash
sudo dnf install libmnl libmnl-devel
```

## Build and run

### Kernel

First you need to build and run a kernel version containing DPLL driver. 
Check if yours has `drivers/dpll` directory. If not, read further.
I used linux-5.14.0-325.dpll_v3.el9 - a kernel specially created for E-810
Intel NIC integration. I first compiled and installed the kernel on a RHEL-9 VM.
The build configuration used can be found at [kernel-config/.config](kernel-config/.config)
Here is the seeries of commands:

```bash
make
sudo make modules_install
sudo make install

```
After the build and installation are done, reboot into the new kernel.

### Kernel module
In order to build the `dpll-testbench` kernel module, run `make` in this directory.
If everything builds ok, you will have `dpll-testbench.ko` file.
Load it using
```bash
sudo insmod dpll-testbench.ko
```
( to remove use `rmmod`)

### User space program

Currently using Python CLI copied from the latest upstream Linux kernels.
To make a smoke test, create environment and run a basic "get" or "dump" for 
DPLL devices.

1. Change to the `userspace` directory and create the environment

```bash
python -m venv env
source env/bin/activate
pip install -r requirements.txt
```

2. Run tests (run as root)

```bash
(env) [vitaly@rhel9 userspace]# sudo env/bin/python cli.py --spec dpll.yaml --dump device-get
[{'clock-id': 5799633565433967664,
  'id': 0,
  'lock-status': 'holdover',
  'mode': 'automatic',
  'module-name': 'dpll_testbench',
  'type': 'pps'}]

(env) [vitaly@rhel9 userspace]# sudo env/bin/python cli.py --spec dpll.yaml --do device-get --json '{"id":0}'
{'clock-id': 5799633565433967664,
 'id': 0,
 'lock-status': 'locked',
 'mode': 'automatic',
 'module-name': 'dpll_testbench',
 'type': 'pps'}

```

#### Monitoring for device status change

```bash
vitaly@rhel9 userspace]$ sudo env/bin/python cli.py --spec dpll.yaml --subscribe monitor
waiting on socket
received notification:
{'name': 'device-change-ntf', 'msg': {'id': 0, 'module-name': 'dpll_testbench', 'clock-id': 5799633565433967664, 'lock-status': 'unlocked', 'mode': 'automatic', 'type': 'pps'}}
waiting on socket
received notification:
{'name': 'device-change-ntf', 'msg': {'id': 0, 'module-name': 'dpll_testbench', 'clock-id': 5799633565433967664, 'lock-status': 'locked', 'mode': 'automatic', 'type': 'pps'}}
waiting on socket
received notification:
{'name': 'device-change-ntf', 'msg': {'id': 0, 'module-name': 'dpll_testbench', 'clock-id': 5799633565433967664, 'lock-status': 'locked-ho-acq', 'mode': 'automatic', 'type': 'pps'}}
waiting on socket

```

### User-space program based on kernel tools

(Kernel tools directory)[kernel-root/tools/net/ynl], in addition to python cli we used above, contains C code generation utilities. When pointed to a generic netlink ddefinitions file (dpll.yaml in our case), userspace header and source files are generated and built into an archive file.

Here is how it's done (cut from [code generation makefile](kernel-root/tools/net/ynl/generated/Makefile)).

[Documentation/netlink/specs/dpll.yaml](kernel-root/Documentation/netlink/specs/dpll.yaml) is used as input to [ynl-gen-c.py](kernel-root/tools/net/ynl/ynl-gen-c.py):

```bash
%-user.h: ../../../../Documentation/netlink/specs/%.yaml $(TOOL)
	@echo -e "\tGEN $@"
	@$(TOOL) --mode user --header --spec $< $(YNL_GEN_ARG_$*) > $@

%-user.c: ../../../../Documentation/netlink/specs/%.yaml $(TOOL)
	@echo -e "\tGEN $@"
	@$(TOOL) --mode user --source --spec $< $(YNL_GEN_ARG_$*) > $@
```

Resulting user space [source](kernel-root/tools/net/ynl/generated/dpll-user.c) and [header](kernel-root/tools/net/ynl/generated/dpll-user.h) are built into an object and `protos.a` archive:

```bash

protos.a: $(OBJS)
	@echo -e "\tAR $@"
	@ar rcs $@ $(OBJS)


%-user.o: %-user.c %-user.h
	@echo -e "\tCC $@"
	@$(COMPILE.c) $(CFLAGS_$*) -o $@ $<

```

The header and `protos.a` can be used to build a [user space program](kernel-root/tools/net/ynl/samples/dpll.c) for accessing our DPLL testbench through kernel dpll driver:

```c
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

```
Making it:

```bash
(env) [vitaly@rhel9 samples]$ make
gcc -std=gnu11 -O2 -W -Wall -Wextra -Wno-unused-parameter -Wshadow -I../lib/ -I../generated/ -idirafter ../../../../include/uapi/    dpll.c ../lib/ynl.a ../generated/protos.a  -lmnl ../lib/ynl.a ../generated/protos.a -o dpll
```

Running it:
```bash
(env) [vitaly@rhel9 samples]$ sudo ./dpll 
Module name: dpll_testbench
Lock status: locked-ho-acq
DPLL type: pps
Clock ID: 507c6fffff1fb430

```

#### Caveats
So far I haven't succeeded in building a notification channel parser using the dpll driver. It's so much easier with Python. I did succeed in receiving multicast notifications using direct calls to the `libnl` functions.

## Future plans (subject to project priorities)

1. Implement userspace program in Go, for incorporating in https://github.com/openshift/linuxptp-daemon

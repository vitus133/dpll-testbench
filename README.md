# DPLL testbench

This repository contains a usage example for Linux DPLL API and 
generic Netlink CLI. 
Intel Ice driver for E810 cards relies on Linux DPLL driver for 
DPLL device queries, configuration and notifications through generic netlink.

The testbench contains kernel module built around Linux DPLL API, and a copy
of user space Python CLI for interacting with the module through generic netlink.

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
(env) [root@rhel9 ynl]# python cli.py --spec dpll.yaml --dump device-get
[{'clock-id': 0,
  'id': 1,
  'lock-status': 'unlocked',
  'mode': 'automatic',
  'module-name': 'dpll_testbench',
  'type': 'pps'}]

(env) [root@rhel9 ynl]# python cli.py --spec dpll.yaml --do device-get --json '{"id":1}'
{'clock-id': 0,
 'id': 1,
 'lock-status': 'unlocked',
 'mode': 'automatic',
 'module-name': 'dpll_testbench',
 'type': 'pps'}

```
## Future plans

1. Implement device state change notification
2. Implement userspace program in Go, for incorporating in https://github.com/openshift/linuxptp-daemon
 
KERNELDIR := /lib/modules/$(shell uname -r)/build
CONFIG_MODULE_SIG=n


obj-m += dpll-testbench.o

all:
	$(MAKE) -C $(KERNELDIR) V=0  M=`pwd` modules
clean:
	#$(MAKE) -C $(KERNELDIR)  M=`pwd` clean
	@rm -f *.ko *.o modules.order Module.symvers *.mod.? *~
	@rm -rf .tmp_versions .cache.mk *.ur-safe *.mod


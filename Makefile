MY_TARGET := chr_test.ko
obj-m := chr_test.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
MODULE_DIR := /lib/modules/$(shell uname -r)/kernel/chr_test
PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
install :
	mkdir -p $ $(MODULE_DIR)
	cp -f $(MY_TARGET) $(DODULE_DIR)
clean :
	$(MAKE) -C $(KERNEL_DIR_ SUBDIRS=$(PWD) clean

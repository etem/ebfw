# Module name
LKM		:= ebfw

# Build
MODULEDIR	:= /lib/modules/$(shell uname -r)
BUILDDIR	:= $(MODULEDIR)/build
KERNELDIR 	:= $(MODULEDIR)/kernel

# Source files
SRCS_S 		:= src

# Header files
SRCS_H		:= $(PWD)/$(SRCS_S)/headers

# Module
obj-m 		:= $(LKM).o

# Core
$(LKM)-y 	+= src/main.o

# Net
$(LKM)-y 	+= src/net.o

# Character device
$(LKM)-y 	+= src/cdev.o

ccflags-y	:= -I$(SRCS_H)

# Recipes
all:
	$(MAKE) -C $(BUILDDIR) M=$(PWD) modules

load:
	insmod ebfw.ko

clean:
	$(MAKE) -C $(BUILDDIR) M=$(PWD) clean
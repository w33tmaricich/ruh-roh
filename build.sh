#!/bin/sh

KERNEL_BUILD=/usr/lib/modules/$(uname -r)/build

make -C $KERNEL_BUILD M=$(pwd) modules

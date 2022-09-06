LINUX_VER=$(shell uname -r)

obj-m := my-module.o

build:
	make -C /lib/modules/$(LINUX_VER)/build M=$(PWD) modules
	gcc main.c -o main

clean: 
	make -C /lib/modules/$(LINUX_VER)/build M=$(PWD) clean
	rm main
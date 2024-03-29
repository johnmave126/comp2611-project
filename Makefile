GCC=mipsel-linux-gnu-gcc
CFLAGS=-I. -Os -msym32 -mno-split-addresses -G 32 -mips32 \
	-mgp32 -fno-delayed-branch -mno-gpopt -mno-abicalls \
	-fno-merge-constants -fno-strict-aliasing \
	-fno-zero-initialized-in-bss -Wall -Wno-main -Wpointer-arith \
	-Wformat -Wno-parentheses

project.s: project.c project.h
	$(GCC) -S $(CFLAGS) project.c

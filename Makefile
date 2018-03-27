all: build

.PHONY: clean

image: build build/myos.img
	mkdir -p build/myos
	mount build/myos.img build/myos
	cp $(FILES) build/myos/
	sync build/myos/*
	umount build/myos
	rm -rf build/myos

build/myos.img: bin/empty.img build/bootloader/stage1.o $(KRNLDR) $(KERNEL) $(APPS)
	mkdir -p $(@D)
	rm -f $@
	cp -f bin/empty.img $@
	dd if=build/bootloader/stage1.o of=$@ conv=notrunc

# Bootloader
KRNLDR = build/bootloader/KRNLDR.SYS
$(KRNLDR): build/bootloader/stage2.o
	cp $< $@
build/bootloader/%.o: src/bootloader/%.s
	mkdir -p $(@D)
	nasm -f bin -o $@ -Isrc/bootloader/ $<

CCFLAGS = -I$(STDLIB_INCLUDE_DIR) -fno-builtin -nostdlib -nostartfiles -m32 -masm=intel -fPIE

# My Standard Library
STDLIB_OBJS = build/stdlib/stdio.o build/stdlib/floppy.o
STDLIB_INCLUDE_DIR = src/stdlib/include
build/stdlib/%.o: src/stdlib/%.c
	mkdir -p $(@D)
	gcc -c $(CCFLAGS) -o $@ -nostdlib $<

# Kernel
KERNEL = build/kernel/KERNEL.SYS

KERNEL_SOURCES := $(shell find src/kernel -name '*.s' -or -name '*.c')
# KERNEL_SOURCES := src/kernel/main.c
KERNEL_OBJECTS := $(subst src/kernel, build/kernel, $(patsubst %.c, %.o, $(KERNEL_SOURCES)))

build/kernel/KERNEL.SYS: $(KERNEL_OBJECTS) $(STDLIB_OBJS)
	gcc -o $@ $(CCFLAGS) $^

build/kernel/%.o: src/kernel/%.c
	mkdir -p $(@D)
	gcc -c $(CCFLAGS) -o $@ $<

# Apps
APPS = build/apps/app1.exe build/apps/app2.exe build/apps/app3.exe build/apps/app4.exe
build/apps/app1.exe: src/apps/app1.c $(STDLIB_OBJS)
	mkdir -p build/apps
	gcc -o $@ $(CCFLAGS) $^

build/apps/app2.exe: src/apps/app2.c $(STDLIB_OBJS)
	mkdir -p build/apps
	gcc -o $@ $(CCFLAGS) $^

build/apps/app3.exe: src/apps/app3.c $(STDLIB_OBJS)
	mkdir -p build/apps
	gcc -o $@ $(CCFLAGS) $^

build/apps/app4.exe: src/apps/app4.c $(STDLIB_OBJS)
	mkdir -p build/apps
	gcc -o $@ $(CCFLAGS) $^

FILES = $(KRNLDR) $(KERNEL) $(APPS)

build: build/bootloader/stage1.o $(FILES)

clean:
	rm -rf build/*

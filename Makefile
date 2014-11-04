SRC=main.c
FLAGS=
OBJ=$(SRC:.asm=)
OUT=qemu
CC=bcc

$(OUT):	disk.img 
	qemu-system-i386 -hda disk.img
	
debug :
	xterm -e qemu-system-i386 -monitor stdio -hda disk.img -s -S & xterm -fn 6x10 -geometry 92x73+0+0 -e 
	gdb -x debugargs

disk.img:boot kernel 
	dd if=/dev/zero of=disk.img bs=512 count=100 
	dd conv=notrunc seek=0 if=boot_/boot of=disk.img 
	dd conv=notrunc seek=1 if=kernel_/kernel.img of=disk.img
	@echo "\033[32;1m[>>] [KERNEL ] Created bootable disk image "\""disk.img"\""\033[0m"
	
boot: boot_/boot.asm
	nasm boot_/boot.asm
	
kernel: 
	bcc -W -V -I -ansi -c kernel_/main.c
	bcc -W -V -I -ansi -c kernel_/kernel.c
	bcc -W -V -I -ansi -c kernel_/syscall_handler.c
	as86 -o kernel_/util_asm.o kernel_/util_asm.s
	as86 -o kernel_/init_syscall.o kernel_/init_syscall.s
	ld86 -M -m -d -s -o kernel_/kernel.img kernel_/main.o kernel_/kernel.o kernel_/syscall_handler.o kernel_/util_asm.o kernel_/init_syscall.o

%.o: %.c
	$(CC) $(FLAGS) -c $(SRC)   

clean:
	rm -f *.c *.o
	rm -f kernel_/kernel boot_/boot disk.img 
	rm -f kernel_/*.o kernel_/kernel.img
build  : boot kernel
rebuild: clean boot kernel

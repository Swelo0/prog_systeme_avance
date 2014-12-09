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

# n°1 on lit 16425 secteurs de 512 bytes de 0 et on écrit dans disk
# n°2 on lit boot que l'on écris dans disk au secteur 0
# n°3 on lit kernel que l'on écris dans disk au secteur 1
# on va commencer notre SFS au secteur 5
disk.img:boot kernel 
	dd if=/dev/zero of=disk.img bs=512 count=6000 
	dd conv=notrunc seek=0 if=boot_/boot of=disk.img 
	dd conv=notrunc seek=1 if=kernel_/kernel.img of=disk.img
	dd conv=notrunc seek=5 if=tools_/test.txt of=disk.img
	@echo "\033[32;1m[>>] [SYSTEME ] Creation de l'image disque bootable "\""disk.img"\""\033[0m"
	
boot: boot_/boot.asm
	nasm boot_/boot.asm

#as86 : Compilation du code C en code objet
#ld86 : Edition des liens (génération de l'image)
#Toujours mettre main au début
kernel: 
	bcc -W -V -I -ansi -c kernel_/main.c
	bcc -W -V -I -ansi -c kernel_/kernel.c
	bcc -W -V -I -ansi -c kernel_/syscall_handler.c
	bcc -W -V -I -ansi -c kernel_/disk.c
	bcc -W -V -I -ansi -c kernel_/syscall.c
	as86 -o kernel_/util_asm.o kernel_/util_asm.s
	as86 -o kernel_/disk_asm.o kernel_/disk_asm.s
	as86 -o kernel_/init_syscall.o kernel_/init_syscall.s
	ld86 -M -m -d -s -o kernel_/kernel.img kernel_/main.o kernel_/kernel.o kernel_/syscall_handler.o kernel_/util_asm.o kernel_/init_syscall.o kernel_/disk.o kernel_/disk_asm.o kernel_/syscall.o

%.o: %.c
	$(CC) $(FLAGS) -c $(SRC)   

clean:
	rm -f *.c *.o
	rm -f kernel_/kernel boot_/boot disk.img 
	rm -f kernel_/*.o kernel_/kernel.img
build  : 
	boot kernel
	
rebuild: 
	clean boot kernel

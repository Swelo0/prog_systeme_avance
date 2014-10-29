SRC=main.c
FLAGS=
OBJ=$(SRC:.asm=)
OUT=qemu
CC=bcc

$(OUT):	disk.img 
	qemu -hda disk.img

disk.img:boot kernel 
	dd if=/dev/zero of=disk.img bs=512 count=100 
	dd conv=notrunc seek=0 if=boot of=disk.img 
	dd conv=notrunc seek=1 if=kernel.o of=disk.img 
	
link: boot util_asm main kernel
	ld86 -M -m -d -s -o kernel.img main.o kernel.o util_asm.o
boot: boot.asm
	nasm boot.asm
util_asm: util_asm.s
	as86 util_asm.s -o util_asm.o
kernel: kernel.c
	bcc -W -V -I -ansi -c kernel.c
main: main.c
	bcc -W -V -I -ansi -c main.c


%.o: %.c
	$(CC) $(FLAGS) -c $(SRC)   

clean:
	rm -f *.c *.o
	rm -f main kernel util_asm boot link disk.img
build  : boot kernel main util_asm
rebuild: clean boot kernel main util_asm

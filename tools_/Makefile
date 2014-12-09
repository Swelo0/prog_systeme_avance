# Makefile du dossier tools_/

all : build

build: fs.o creationSFS.o
	gcc fs.o creationSFS.o -o sfs

creationSFS.o : creationSFS.c
	gcc -c -Wall creationSFS.c

fs.o : fs.c fs.h
	gcc -c -Wall fs.c

clean :
	rm *.o *.out sfs

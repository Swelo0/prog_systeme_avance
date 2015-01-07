// kernel.c
//#include "syscall.c"
#define filename_size 32

typedef signed int int16;

int times2(int n);
int interrupt(int number, int ax, int bx, int cx, int dx, int di);

typedef struct stat_t {
	char  name[filename_size];
	int nbBlocks;
	int16 size;
} stat_t;

stat_t stat;

void kernel() {
	char str[256], sect[512], filename[filename_size];
	stat.name[0] = '\0';
	stat.size = 0;
	
	init_syscalls();
	
	interrupt(0x80, 1, "Veuillez saisir un nom de fichier afin de savoir sa taille:\r\n", 0, 0); // print_string
	interrupt(0x80, 2, filename, 0, 0); // read_string
	interrupt(0x80, 1, "\r\nVous avez ecrit: ", 0, 0); // print_string
	interrupt(0x80, 1, filename, 0, 0); // print_string
	interrupt(0x80, 1, "\r\n", 0, 0); // print_string	
	
	interrupt(0x80, 5, filename, &stat, 0); // get_stat() du fichier filename
	
	while(1);
}

#include "fs.h"

extern void print_string(char *str);
extern void read_sector(int sector, uchar *buf);
extern void print_char(char c);

int debutStruct = 0x1cb7;

char sect[512];
int i;

int get_stat(char *filename, struct stat_st *stat) {
	read_sector(14,sect);
	print_string("\r\n");
	
	for(i=183;i<194;i++)
		print_char(sect[i]);
}

int read_file(char *filename, unsigned char *buf) {
	
}

int remove_file(char *filename) {
	
}

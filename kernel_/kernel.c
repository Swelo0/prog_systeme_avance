// kernel.c
int times2(int n);
int interrupt(int number, int ax, int bx, int cx, int dx, int di);

void print_char(char c);
void print_string(char *str);
char read_char();
void read_string(char *buf);

void read_sector(int sector, uchar *buf);
void write_sector(int sector, uchar *buf);


void kernel() {
	pipo(); 
	init_syscalls();
	while(1);
}

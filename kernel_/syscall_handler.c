//syscall_handler.c
extern void print_string(char *str);
extern void read_string(char *buf);
extern void print_char(char c);
extern char read_char();
extern void read_sector(int sector, uchar *buf);
extern void write_sector(int sector, uchar *buf);

typedef unsigned int uint_;

void syscall_handler(uint_ syscall_nb, uint_ arg1, uint_ arg2, uint_ arg3, uint_ arg4){
	//case en fonction des id appel reçus
	switch (syscall_nb){
		case 1:
			print_string(arg1);
			break;
		case 2:
			read_string(arg1);
			break;
		case 3:
			read_sector(arg1,arg2);
			break;
		case 4:
			write_sector(arg1,arg2);
			break;
			
	}
}

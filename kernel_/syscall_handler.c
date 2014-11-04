//syscall_handler.c
extern void print_string(char *str);
extern void read_string(char *buf);
extern void read_sector(int sector, uchar *buf);
extern void write_sector(int sector, uchar *buf);

typedef unsigned int uint;

void syscall_handler(uint syscall_nb, uint arg1, uint arg2, uint arg3, uint arg4){
	
	//case en fonction des id appel reçus
	
}

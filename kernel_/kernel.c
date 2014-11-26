// kernel.c
int times2(int n);
int interrupt(int number, int ax, int bx, int cx, int dx, int di);

void print_char(char c);
void print_string(char *str);
char read_char();
void read_string(char *buf);

typedef unsigned char uchar;
typedef unsigned int uint;

void kernel() {
	char str[256], sect[512];
	init_syscalls();
	interrupt(0x80, 1, "Veuillez ecrire qqch qui sera ensuite affiche: ", 0, 0); // print_string
	interrupt(0x80, 2, str, 0, 0); // read_string
	interrupt(0x80, 1, "Vous avez ecrit: ", 0, 0); // print_string
	interrupt(0x80, 1, str, 0, 0); // print_string
	interrupt(0x80, 1, "\r\n", 0, 0); // print_string
	
	interrupt(0x80, 3, 5, sect, 0); // read sector
	interrupt(0x80, 1, "\n", 0, 0); // print_string
	interrupt(0x80, 1, "Voici ce qui a ete lu dans le secteur numero 5: ", 0, 0); // print_string
	interrupt(0x80, 1, "\r\n", 0, 0); // print_string
	interrupt(0x80, 1, sect, 0, 0); // print_string
	interrupt(0x80, 1, "\r\n", 0, 0); // print_string
	
	interrupt(0x80, 1, "Veuillez ecrire qqch qui sera ensuite ecrit dans le sixieme secteur du disque: ", 0, 0); // print_string
	interrupt(0x80, 2, sect, 0, 0); // read_string
	interrupt(0x80, 4, 5, sect, 0); // write_sector
	interrupt(0x80, 1, "\r\n", 0, 0); // print_string
	interrupt(0x80, 1, sect, 0, 0); // print_string
	interrupt(0x80, 1, "Le secteur 6 a bien ete modifie. Pour contrôler, c'est l'adresse 0xA00", 0, 0); // print_string, 0, 0); // print_string
	while(1);
}

void print_char(char c){
	char al = c;
	char ah = 0xE;
	int ax = ah*256+al;
	interrupt(0x10,ax,0,0,0);
}

char read_char(){
	int ax,al;
	ax = interrupt(0x16,0,0,0,0);
	al = ax & 0xff;
	return al;
}

void print_string(char *str){
	int i = 0;
	do{
		print_char(str[i]);
		i++;
	}while(str[i] != '\0');
}

void read_string(char* buf){
	int i = 0;
	do{
		buf[i] = read_char();
	}while(buf[i++] != 0xD);
	buf[i]='\0';
}

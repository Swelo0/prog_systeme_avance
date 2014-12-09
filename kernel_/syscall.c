#include "syscall.h"

void print_char(char c){
	char al = c;
	char ah = 0xE;
	int ax = ah*256+al;
	interrupt(0x10,ax,0,0,0);
}

//Renvoie une frappe clavier
char read_char(){
	int ax,al;
	ax = interrupt(0x16,0,0,0,0); //ax = scan code et char ASCII
	al = ax & 0xff; //Char ASCII
	return al;
}

//Affiche une chaine de caractère à l'écran.
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
		print_char(buf[i]); // A enlever
	}while(buf[i++] != 0xD);
	buf[i]='\0';
}

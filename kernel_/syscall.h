#ifndef H_SYSCALL_
#define H_SYSCALL_

	typedef unsigned char uchar;
	typedef unsigned int uint;

	void print_char(char c);
	void print_string(char *str);
	char read_char();
	void read_string(char *buf);
	void read_sector(int sector, uchar *buf);
	void write_sector(int sector, uchar *buf);

	typedef struct packet{
		uchar size;
		uchar reserved;
		uint sect_count;
		uint addr_offset;
		uint addr_segment;
		uint first_sect; // 0 = premier secteur.
	} packet;

#endif

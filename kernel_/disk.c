void read_sector(int sector, uchar buf*);
void write_sector(int sector, uchar *buf);

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct packet{
	uchar size;
	uchar reserved;
	uint sect_count;
	uint buf_offset;
	uint buf_segment;
	uint first_sect[4];
} packet;
	
void read_sector(int sector, uchar* buf){
	packet p;
	p.size = 0x10;
	p.reserved = 0;
	p.sect_count = 1;
	p.buf_offset = buf;
	//p.buf_segment -> assembleur;
	p.first_sect[0] = sector;
	p.first_sect[1] = 0;
	p.first_sect[2] = 0;
	p.first_sect[3] = 0;
	read_sector_raw(0x80, &p);
}

void write_sector(int sector, uchar* buf){
	packet p;
	p.size = 0x10;
	p.reserved = 0;
	p.sect_count = 1;
	p.buf_offset = buf;
	//p.buf_segment -> assembleur;
	p.first_sect[0] = sector;
	p.first_sect[1] = 0;
	p.first_sect[2] = 0;
	p.first_sect[3] = 0;
	write_sector_raw(0x80, &p);
}

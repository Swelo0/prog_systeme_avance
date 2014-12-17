#ifndef H_FS_KERNEL_
#define H_FS_KERNEL_
#define filename_size    32
#define first_fe_sect    14
#define file_entries_num 16

typedef signed int int16;
typedef struct stat_t {
	char   name[filename_size]; 
	int    nbBlocks;
	int16  size;
} stat_t;

char sectBuf[512];

extern void print_string(char *str)             ;
extern void read_sector (int sector, uchar *buf);
extern void print_char  (char c)                ;

int str_comp(char *str1, char *str2, int size1, int size2);
int get_stat   (char *filename, stat_t *stat)      		  ;
int read_file  (char *filename, unsigned char *buf)		  ;
int remove_file(char *filename)                    		  ;
int iterator(char *filename, int* position, int* sector, int* sectorPos, struct stat_t *stat);

#endif

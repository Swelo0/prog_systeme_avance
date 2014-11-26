#ifndef H_FS_
#define H_FS_

typedef short int16;

typedef char block[1024];

// attribute(packed) pour empêcher le compilateur de faire du panning
typedef struct filesystem { // __attribute__(__packed__) {

	struct superblock {
		char    signature[8]	 ; 
		int16 	sectors_per_block;
		int16 	bitmap_size	 ;
		int16 	file_entry_size  ;
		int16 	file_entry_blocks;
		int16 	file_content_size;
	} sb          		;

	block bitmap            ;
	block file_entry[16]    ;
	block file_content[8191];
		
} filesystem;

filesystem sfscreate();
void sfsadd(char file[]);
void sfslist();
void sfsdel();

#endif

#ifndef H_FS_
#define H_FS_

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define block_size		1024

typedef int16_t int16;
typedef int64_t int64;
typedef char    block[1024];

// attribute(packed) pour empêcher le compilateur de faire du panning
typedef struct filesystem { //__attribute__(__packed__) {

	struct superblock {
		char    signature[8]	 ; 
		int16 	sectors_per_block;
		int16 	bitmap_size	 ;
		int16 	file_entry_size  ;
		int16 	file_entry_blocks;
		int16 	file_content_size;
	} sb ;

	int64 bitmap ;
	struct file_entries {
		// Chaque entry prend 256 bytes
		char  name[32];
		int16 size;
		// 256 - (32 + 2) = 222 bytes pour les index des blocs
		int16 blocs[222];
	} fe[16];
	// La mémoire est de 64Ko max ==> 53 pour le file_content
	block file_content[53]  ;
		
} filesystem;

filesystem sfscreate();
void sfslist(filesystem fs);
void sfsadd (filesystem *fs, char file[]);
void sfsdel (filesystem *fs, char file[]);


#endif

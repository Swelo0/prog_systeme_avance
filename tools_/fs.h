#ifndef H_FS_
#define H_FS_

#include <stdio.h>
#include <string.h>
//#include <stdint.h>

#define block_size	 1024
#define signature_size   8
#define filename_size	 32
#define file_entry_sz    256	// Chaque entry prend 256 bytes
#define max_blocks	 222	// 256 - (32 + 2) = 222 bytes pour les index des blocs
#define file_entries_num 16
#define file_contents	 53	// La mémoire est de 64Ko max ==> 53 pour le file_content

typedef short   int16; //short est tjr à 16bits
typedef long    int64;
typedef char    block[1024]; // block = char[1024]. La syntax peut
							 // perturbé.

// attribute(packed) pour empêcher le compilateur de faire du panning
typedef struct filesystem {
	struct superblock {

		char  signature[signature_size]; 
		int16 sectors_per_block	       ;
		int16 bitmap_size	       ;
		int16 file_entry_size  	       ;
		int16 file_entry_blocks	       ;
		int16 file_content_size	       ;

	} sb ;

	block bitmap ;

	struct file_entries {

		char  name[filename_size];
		int16 size;
		int16 blocs[max_blocks];

	} fe[file_entries_num];

	block file_content[max_blocks]  ;
		
} filesystem __attribute__((packed));

filesystem sfscreate();
void sfslist(filesystem *fs);
void sfsadd (filesystem *fs, char file[]);
void sfsdel (filesystem *fs, char file[]);

#endif

// fs.c

typedef short 	   int16;
typedef char[1024] block;

typedef struct superblock {
	char[8] signature		 ; 
	int16 	sectors_per_block;
	int16 	bitmap_size		 ;
	int16 	file_entry_size  ;
	int16 	file_entry_blocks;
	int16 	file_content_size;
} superblock;

// 32bytes+112*(2bytes) = 256 bytes
typedef struct fileEntries {
	char[32]   name;
	int16[112] index;
} fileEntries;

typedef struct filesystem {
	//superblock   sb          ;
	struct superblock {
		char[8] signature		 ; 
		int16 	sectors_per_block;
		int16 	bitmap_size		 ;
		int16 	file_entry_size  ;
		int16 	file_entry_blocks;
		int16 	file_content_size;
	} 			 sb          ;
	block	     bitmap      ;
	fileEntries[16*4]  file_entry  ; // 16 blocks
	block[8191]  file_content;	     //	
} filesystem;

filesystem sfscreate() {
		filesystem sf;
		
		sf.sb.signature 		 = "SFSv0100";
		sf.sb.sectors_per_block  = 2         ;
		sf.sb.bitmap_size        = 1         ;
		sf.sb.file_entry_size    = 256       ;
		sf.sb.file_entry_blocks  = 16        ;
		sf.sb.file_content_size  = 8192      ;
		
		//Init du bitmap à 0;
		sf.bitmap = 0;
		//Init du file entries à 0;
		int i;
		for (i=0; i<16; i++)
			sf.file_entry[i] = 0;
		
		return sf;
}

void sfsadd() {
	// Code was here
}

void sfslist() {
	// Code was here
}

void sfsdel() {
	// Code was here
}

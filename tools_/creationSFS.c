#include "fs.h"
#include <stdio.h>

// Création: crée un filesystemName.img
filesystem sfscreate(char *filesystemName) {

		filesystem sf;
		
		// Superblock
		strcpy(sf.sb.signature,    "SFSv0100")     ;
		sf.sb.sectors_per_block  = 2               ;
		sf.sb.bitmap_size        = 1               ;
		sf.sb.file_entry_size    = file_entry_sz   ;
		sf.sb.file_entry_blocks  = file_entries_num;
		sf.sb.file_content_size  = file_contents   ;
		
		// Init du bitmap à 0;
		memset(sf.bitmap,'\0',block_size);

		// Init du file entries à 0;
		int i,j;
		for (i = 0; i < file_entries_num; i++) {
			sf.fe[i].name[0] = '\0';
			sf.fe[i].size    =  0 ;
			for (j = 0; j < max_blocks; j++)
				sf.fe[i].blocs[j] = 0;
		}

		return sf;
}

filesystem sfsAddToImg(){
	
}

int main() {

	filesystem fs = sfscreate("fs.img");
	//write(&fs);
	//sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",(int64)fs.bitmap[0]);
	//sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",(int64)fs.bitmap[0]);
	
	//sfsdel(&fs, "test.txt");
	
	//sfslist(&fs);
	
	printf("binarymap : %d \n",(int64)fs.bitmap[0]);

	return 0;
}

	///////////////////
	/*
	int numEntry = 0;
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1);
	
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1)	;
	*/

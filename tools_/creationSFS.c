#include "fs.h"
#include <stdio.h>

filesystem sf;

// Création: crée un filesystemName.img
int sfscreate(char *filesystemName) {
		FILE * file= fopen(filesystemName, "wb");
		
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
		
		//Ecriture de la structure initiale dans fs.img
		if (file != NULL) {
			fwrite(&sf, sizeof(filesystem), 1, file);
			fclose(file);
		}
		return 0;
}

int sfsAddToImg(char *filesystemName, char *filename){
	FILE * file= fopen(filesystemName, "wb");
	
	sfsadd(&sf, filename);
	
	//Ecriture de la structure initiale dans fs.img
	if (file != NULL) {
		fwrite(&sf, sizeof(filesystem), 1, file);
		fclose(file);
	}
	
	return 0;
}

int main() {
	sfscreate("fs.img");
	sfsAddToImg("fs.img", "test.txt");
	sfsAddToImg("fs.img", "bonjour.txt");
	sfsAddToImg("fs.img", "message.txt");

	return 0;
}

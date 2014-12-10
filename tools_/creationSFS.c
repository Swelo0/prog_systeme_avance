#include "fs.h"
#include <stdio.h>

filesystem sf;

// Création: crée un filesystemName.img
int sfscreate() {
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
		return 0;
}

int sfsAddToImg(char *filename){
	
	sfsadd(&sf, filename);
	
	return 0;
}

int main() {
	FILE * file= fopen("fs.img", "wb");
	int i;
	char* tempChar;
	sfscreate();
	sfsAddToImg("test.txt");
	sfsAddToImg("bonjour.txt");
	sfsAddToImg("message.txt");
	
	//Ecriture de la structure initiale dans fs.img
	if (file != NULL) {
		fwrite(&sf.sb, sizeof(struct superblock), 1, file);
		fclose(file);
		
		tempChar = malloc(1024 - sizeof(struct superblock));
		
		for(i = 0; i < (1024 - sizeof(struct superblock)); i++){
			tempChar[i] = '\0';
		}
		
		file = fopen("fs.img", "a");
		fwrite(tempChar, 1024 - sizeof(struct superblock), 1, file);
		fclose(file);
				
		file= fopen("fs.img", "a");
		fwrite(&sf.bitmap, block_size, 1, file);
		fclose(file);
		
		file= fopen("fs.img", "a");
		fwrite(&sf.fe, sizeof(struct file_entries)*file_entries_num, 1, file);
		fclose(file);
		
		file= fopen("fs.img", "a");
		fwrite(&sf.fe, sizeof(struct file_entries)*file_entries_num, 1, file);
		fclose(file);
		
		file= fopen("fs.img", "a");
		fwrite(&sf.file_content, sizeof(block)*max_blocks, 1, file);
		fclose(file);
	}

	return 0;
}

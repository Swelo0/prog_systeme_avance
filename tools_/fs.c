#include "fs.h"

// Création
filesystem sfscreate() {

		filesystem sf;
		
		// Superblock
		strcpy(sf.sb.signature,    "SFSv0100");
		sf.sb.sectors_per_block  = 2          ;
		sf.sb.bitmap_size        = 1          ;
		sf.sb.file_entry_size    = 256        ;
		sf.sb.file_entry_blocks  = 16         ;
		sf.sb.file_content_size  = 53         ;
		
		// Init du bitmap à 0;
		int i,j;
		for (i = 0; i < 1024; i++)
			sf.bitmap[i] = 0;

		// Init du file entries à 0;
		for (i = 0; i < 16; i++) {
			sf.fe.entry[i].name[0] = '0';
			sf.fe.entry[i].size    =  0 ;
			for (j = 0; j < 222; j++)
				sf.fe.entry[i].block[j] = 0;
		}

		return sf;

}

// Liste
void sfslist(filesystem fs) {

	// Code was here

}

// Ajout
void sfsadd(filesystem fs, char file[]) {

	// Infos du fichier (nom + taille)
	// Partition fichier
	// Pour chaque bloc :
	// 	Trouver bloc libre dans Bitmap (premier bit à 0) ==> Inverser bit
	//	Sauvegarder l'index du bit dans File Entries
	//	Sauvegarder le contenu dans File Content au même index

}

// Suppression
void sfsdel(filesystem fs, char file[]) {

	// Parcourir itérativement File Entries jusqu'à trouver le fichier correspondant 
	char *name;
	int index = -1;
	while (strcmp(name, file) != 0) {
		index++;
		name = fs.fe.entry[index].name;		
	}

	printf("File_Entry index = %d\n", index);

	// 	==> Changer le premier caractère du nom du fichier et sa taille
	fs.fe.entry[index].name[0] = '0';
	fs.fe.entry[index].size    =  0 ;

	printf("File : %s (%d bytes)\n", fs.fe.entry[index].name, fs.fe.entry[index].size);

	// Pour chaque bloc du File Entry :
	// 	Récupérer son index
	//	Mettre le bit correspondant dans Bitmap à 0
	int i;
	for (i = 0; i < 222; i++)
		if (fs.fe.entry[index].block[i] != 0) { printf("Bitmap[%d] = 0\n", fs.fe.entry[index].block[i]);
			fs.bitmap[fs.fe.entry[index].block[i]] = 0; }

}

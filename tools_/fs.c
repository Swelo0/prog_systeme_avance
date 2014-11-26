// fs.c
#include "fs.h"
#include <stdio.h>
#include <string.h>

// Création
filesystem sfscreate() {

		filesystem sf;
		
		// Superblock
		strcpy(sf.sb.signature,    "SFSv0100");
		sf.sb.sectors_per_block  = 2          ;
		sf.sb.bitmap_size        = 1          ;
		sf.sb.file_entry_size    = 256        ;
		sf.sb.file_entry_blocks  = 16         ;
		sf.sb.file_content_size  = 8192       ;
		
		// Init du bitmap à 0;
		int i,j;
		for (i = 0; i < 1024; i++)
			sf.bitmap[i] = 0;

		// Init du file entries à 0;
		for (i = 0; i < 16; i++)
			for (j = 0; j < 1024; j++)
				sf.file_entry[i][j] = 0;

		return sf;

}

// Liste
void sfslist() {

	// Code was here

}

// Ajout
void sfsadd(char file[]) {

	// Infos du fichier (nom + taille)
	// Partition fichier
	// Pour chaque bloc :
	// 	Trouver bloc libre dans Bitmap (premier bit à 0) ==> Inverser bit
	//	Sauvegarder l'index du bit dans File Entries
	//	Sauvegarder le contenu dans File Content au même index

}

// Suppression
void sfsdel() {

	// Parcourir itérativement File Entries jusqu'à trouver le fichier correspondant ==> Changer en "0" le premier caractère du nom du fichier
	// Pour chaque bloc du File Entry :
	// 	Récupérer son index
	//	Mettre le bit correspondant dans Bitmap à 0

}

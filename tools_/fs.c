/*----------------------------------------------------------------------
 * 					Système de fichier (version linux)
 * 	Fonctionnalité :
 * 		-sfscreate: Initialise notre système de fichier.
 * 		-sfsadd   : Permet d'ajouter un fichier au système,
 * 					on chercher une entrée libre dans le file entry pour
 * 					notre fichier et on l'écris en blocks dans le file 
 * 					content, le bitmap est mis à jour en parrallèle.
 * 
 * 		-sfsdel   : Met simplement à 0 le premier caractère du file 
 * 					entry de notre fichier ainsi que les bitmap qui le
 * 					concerne
 * 
 *  Remarques :  /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ 
 * 
 * 				Le premier blocks du content (qui à la valeur 0 en c)
 * 				est considéré comme le 1 ici. Ainsi si dans notre file
 * 				entry, notre fichier est dans le block [1], en réalité
 * 				c'est le block [0] en mémoire.
 * 				exemple :
 * 						fileEntry[1].blocs[1] == fileContent[0]
 * 
 * -------------------------------------------------------------------*/

#include "fs.h"

// Création
filesystem sfscreate() {

		filesystem sf;
		
		// Superblock
		strcpy(sf.sb.signature,    "SFSv0100")     ;
		sf.sb.sectors_per_block  = 2               ;
		sf.sb.bitmap_size        = 1               ;
		sf.sb.file_entry_size    = file_entry_sz   ;
		sf.sb.file_entry_blocks  = file_entries_num;
		sf.sb.file_content_size  = file_contents   ;
		
		// Init du bitmap à 0;
		sf.bitmap = 0;

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

// Liste
void sfslist(filesystem *fs) {

	// On parcourt le File Entries
	int index = 0;
	while (index < file_entries_num) {
		if ((*fs).fe[index].name[0] != '\0')
			printf("%s\n", (*fs).fe[index].name);
		index++;
	}
}


// Ajout
void sfsadd(filesystem *fs, char fileName[]) {

	FILE* fp;
	block blockTemp;
	int   ptByte = 0;
	char  ch;
	int	  fileLen, numEntry, currentBlock = 0, numBlock = 0;
	
	// Mode lecture
	fp = fopen(fileName,"r"); 
	
	if( fp == NULL ) perror("Error while opening the file.\n");
	
	// On trouve une entrée libre.
	numEntry = -1;
	while ((*fs).fe[++numEntry].name[0] != '\0');
	strcpy((*fs).fe[numEntry].name, fileName);
	
	// Longueur du fichier
	fseek(fp, 0, SEEK_END);
	// Nombre de bytes dans le fichier	
	fileLen=ftell(fp); 
	fseek(fp, 0, SEEK_SET);
	
	(*fs).fe[numEntry].size = fileLen;
	
	int i=0;
	// On parcourt le fichier par block (1024o) 
	for (i=0;i<(fileLen/block_size);i++) {
		fread( blockTemp , block_size , 1 , fp );
		// On met a jour le Bitmap et écrit les données, writeBlock(...)
		// On trouve un block libre
		while ((*fs).bitmap&1<<numBlock++); 
		// Mise à jour de Bitmap
		(*fs).bitmap |= 1<<numBlock-1; 
		// Ecrit 2
		(*fs).fe[numEntry].blocs[currentBlock++] = numBlock; 
		// Si le deuxième block est libre (donc réellement le bloc[1])
		memmove((*fs).file_content[numBlock], blockTemp, block_size);
	}
	
	// Quand il reste moins de 1024o de données à écrire. 
	while( ( ch = fgetc(fp) ) != EOF ) blockTemp[ptByte++] = ch;
	blockTemp[ptByte] = '\0'; //fin du fichier
	
	// On met a jour le Bitmap et écrit les données, writeBlock(...)
	numBlock = 0;
	// On trouve un block libre
	while ((*fs).bitmap&1<<numBlock++); 
	// Mise à jour de bitmap
	(*fs).bitmap |= 1<<numBlock-1; 
	// Ecrit 2
	(*fs).fe[numEntry].blocs[currentBlock++] = numBlock; 
	// Si le deuxième block est libre (donc réellement le bloc[1])
	memmove((*fs).file_content[numBlock], blockTemp, block_size);
	
        fclose(fp);
    
}


// Suppression fichier
void sfsdel(filesystem *fs, char file[]) {

	// Parcourir File Entries jusqu'à trouver le fichier correspondant 
	int index = -1;

	while ((index < file_contents) && (strcmp((*fs).fe[++index].name, file) != 0));
	if (index < 0) return;

	// Changer le premier caractère du nom du fichier et sa taille
	(*fs).fe[index].name[0] = '\0';
	(*fs).fe[index].size    =  0 ;

	// Pour chaque bloc du File Entry :
	// 	Récupérer son index
	//	Mettre le bit correspondant dans Bitmap à 0
	int i;
	for (i = 0; i < max_blocks; i++) 
		if ((*fs).fe[index].blocs[i] != 0) {
			(*fs).bitmap ^= 1 << (*fs).fe[index].blocs[i]-1; 
		}
}

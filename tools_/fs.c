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
		sf.bitmap = 0;

		// Init du file entries à 0;
		int i,j;
		for (i = 0; i < 16; i++) {
			sf.fe[i].name[0] = '\0';
			sf.fe[i].size    =  0 ;
			for (j = 0; j < 222; j++)
				sf.fe[i].blocs[j] = 0;
		}
		//Fichier expérimental de test
		/*
		strcpy(sf.fe[3].name, "TestFile\0");
		sf.fe[3].size = 3;
		sf.fe[3].blocs[0] = 1;
		sf.fe[3].blocs[1] = 2;
		sf.fe[3].blocs[2] = 3;
		int64_t one = 1;
		sf.bitmap |= one << 0; 
		sf.bitmap |= one << 1; 
		sf.bitmap |= one << 2; 
		strcpy(sf.file_content[0], "cahsidjahs\0");
		strcpy(sf.file_content[1], "sdfhgsdh\0");
		strcpy(sf.file_content[2], "siduhsdfjns\0");*/

		return sf;

}

// Liste
void sfslist(filesystem *fs) {
	//On va parcourir le Files Entries pour sortir tous les fichiers.
	int index = 0;
	printf("Voici la liste des fichiers:\n");
	while ((index < 16)){
		while ((*fs).fe[index++].name[0] == '\0');
		if((*fs).fe[index-1].size != 0)
			printf("- %s\n",(*fs).fe[index-1].name);
	}
}


// Ajout
void sfsadd(filesystem *fs, char fileName[]) {

	FILE* fp;
	block blockTemp;
	int   ptByte = 0;
	char  ch;
	int	  fileLen, numEntry, currentBlock = 0, numBlock = 0;
	
	fp = fopen(fileName,"r"); // read mode
	
	if( fp == NULL )
	  perror("Error while opening the file.\n");
	  //exit(EXIT_FAILURE);
	}
	
	//On trouve une entrée libre.
	numEntry = -1;
	while ((*fs).fe[++numEntry].name[0] != '\0');
	
	//printf("index : %d \n",numEntry);
	
	strcpy((*fs).fe[numEntry].name, fileName);
	
	//printf("fichier : %s \n",(*fs).fe[numEntry].name);
	//Get file length
	fseek(fp, 0, SEEK_END);
	fileLen=ftell(fp); //Nombre de byte dans le fichier
	fseek(fp, 0, SEEK_SET);
	
	(*fs).fe[numEntry].size = fileLen;
	
	int i=0;
	//On parcours le fichier par block (1024o) 
	for (i=0;i<(fileLen/block_size);i++)
	{
		fread( blockTemp , block_size , 1 , fp );
		//On maj le bitmap et écris les données, writeBlock(...)
		while ((*fs).bitmap&1<<numBlock++); //on trouve un block libre.
		(*fs).bitmap |= 1<<numBlock-1; // maj de bitmap.
		(*fs).fe[numEntry].blocs[currentBlock++] = numBlock; // écrit 2
		// si le deuxième block est libre. (donc réellement le bloc[1])
		//strcpy((*fs).file_content[numBlock], blockTemp);
		memmove((*fs).file_content[numBlock], blockTemp, block_size);
		
	}
	
	//Quand il reste des données < 1024 on les lit et on rempli le reste
	//de 0.
	//A FINIR, on remplie pas le rest
	while( ( ch = fgetc(fp) ) != EOF )
	{
      blockTemp[ptByte++] = ch;
      //ensuite on doit remplir de 0
	}
	blockTemp[ptByte] = '\0'; //A enlever
	
	//On maj le bitmap et écris les données, writeBlock(...)
	numBlock = 0;
	while ((*fs).bitmap&1<<numBlock++); //on trouve un block libre.
	(*fs).bitmap |= 1<<numBlock-1; // maj de bitmap.
	(*fs).fe[numEntry].blocs[currentBlock++] = numBlock; // écrit 2
	// si le deuxième block est libre. (donc réellement le bloc[1])
	//strcpy((*fs).file_content[numBlock], blockTemp);
	memmove((*fs).file_content[numBlock], blockTemp, block_size);
	
	
    fclose(fp);
    
  // return 0;
	
	// Infos du fichier (nom + taille)
	// Partition fichier
	// Pour chaque bloc :
	// 	Trouver bloc libre dans Bitmap (premier bit à 0) ==> Inverser bit
	//	Sauvegarder l'index du bit dans File Entries
	//	Sauvegarder le contenu dans File Content au même index
	// Infos du fichier (nom + taille)
	// Partition fichier
	// Pour chaque bloc :
	// 	Trouver bloc libre dans Bitmap (premier bit à 0) ==> Inverser bit
	//	Sauvegarder l'index du bit dans File Entries
	//	Sauvegarder le contenu dans File Content au même index
}


// Suppression fichier
void sfsdel(filesystem *fs, char file[]) {

	// Parcourir File Entries jusqu'à trouver le fichier correspondant 
	int index = -1;

	while ((index < 53) && (strcmp((*fs).fe[++index].name, file) != 0));
	if (index < 0) return;

	// Changer le premier caractère du nom du fichier et sa taille
	(*fs).fe[index].name[0] = '\0';
	(*fs).fe[index].size    =  0 ;

	// Pour chaque bloc du File Entry :
	// 	Récupérer son index
	//	Mettre le bit correspondant dans Bitmap à 0
	int i;
	for (i = 0; i < 222; i++) 
		if ((*fs).fe[index].blocs[i] != 0) {
			(*fs).bitmap ^= 1 << (*fs).fe[index].blocs[i]-1; 
		}
}


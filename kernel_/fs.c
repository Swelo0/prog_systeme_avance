#include "fs.h"

int get_stat(char *filename, struct stat_t *stat) {
	int ret = 0;
	sectorPos = 0;
	// Position =  numéro du file_entry
	position = 0;

	// Itérer tant qu'on a pas le bon fichier
	while ((((*stat).name) != filename) && (ret == 0)){
		ret = iterator(filename, &position);
		// Gérer les erreurs
		if (ret == -1) { 
			print_string("Erreur : Fichier introuvable ==> ");
			print_string(filename);
			print_string("\r\n");
			return -1;
		}
		else if (ret == -2) {
			print_string("Erreur : Position introuvable ==> ");
			print_string(position);
			print_string(" \r\n");
			return -2;
		}
	}
	print_string("La taille du fichier ");
	print_string((*stat).name);
	print_string(" est de ");
	print_string((*stat).size);
	print_string(" bits.\r\n");
		
	
	return 0;
}

int read_file(char *filename, unsigned char *buf, struct stat_t *stat) {
	
}

int remove_file(char *filename, struct stat_t *stat) {
	
}

//Iterateur pour trouver un fichier
int iterator(char *filename, int* sector, struct stat_t *stat){

	int index;
	int i;
	int j;
		
	// Test de validité
	if ((position >= file_entries_num) || (position < 0)) return -2;

	// 2 File Entries par secteur
	// File Entry 0/1 = Secteur 12	
	do {
		//sectorPos = 0 si première partie du secteur, 1 si deuxième partie du secteur
		sectorPos = (int) position % 2;
		
		if(position == 0)
			sector = first_fe_sect;
		else if(sectorPos == 0)
			sector++;
		
		read_sector(sector, sectBuf);
		if (position < file_entries_num)
			position++;
		else
			return -1;
	} while (sectBuf[0] == '\0');
	
	j = 0;
	//On récupère le nom du fichier
	for(i = ((int)sectorPos*256); i < ((int)sectorPos*256+32); i++)
		(*stat).name[j++] += sectBuf[i];
	//On récupère la taille du fichier
	for(i = ((int)sectorPos*256+32); i < ((int)sectorPos*256+34); i++)
		(*stat).size += sectBuf[i];
	for(i = ((int)sectorPos*256+34); i < ((int)sectorPos*256+256); i+2){
		if(sectBuf[i] == '0'){
			(*stat).nbBlocks += 1;
		}else
			break;
	}
	
	return 0;
}

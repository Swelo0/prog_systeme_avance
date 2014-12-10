#include "fs.h"
//stat_t stat;
	//stat.name[0] = '\0';

int get_stat(char *filename, struct stat_t *stat) {

	// Position =  numéro du file_entry
	int position = 0;
	char *file = "";
	int ret = 0;

	// Itérer tant qu'on a pas le bon fichier
	while ((strcmp(file, filename) != 0) && (ret == 0))
		ret = iterator(filename, &position);

	// Gérer les erreurs
	if (ret == -1) { 
		printf("Erreur : Fichier \"%s\" introuvable\n", filename);
		return -1;
	}
	else if (ret == -2) {
		printf("Erreur : Position (%d) invalide\n", position);
		return -2;
	}
	else return 0;

}

int read_file(char *filename, unsigned char *buf) {
	
}

int remove_file(char *filename) {
	
}

//Iterateur pour trouver un fichier
int iterator(char *filename, int* position){

	int index;

	// Test de validité
	if ((position >= file_entries_num) || (position < 0)) return -2;

	// 2 File Entries par secteur
	// File Entry 0/1 = Secteur 14	
	do {
		index = (first_fe_sect) + (position / 2); // Erreur : need scalar
		read_sector(sect, index);
		if (position < file_entries_num)
			position++;
		else
			return -1;
	} while (sect[0] == '\0');
	
	strcpy(filename, sect);
	return 0;

}

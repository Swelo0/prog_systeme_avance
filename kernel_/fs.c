#include "fs.h"

//début du fileSystem = 146B (5227), comme les fichiers sont 4 secteurs + loin,
//on fait currentPosition = 5227 + 2048 = 7275 (1c6b) 
//du coup le currentSecteur sera 14 à l'initialisation, mais il faudra 
//ajouter 107 pour atteindre 7275, car adresse 14ème secteur = 7168 (1c00)
//currentPosition = 7275 - 7168 = 10

//stat_t stat;
	//stat.name[0] = '\0';

int get_stat(char *filename, struct stat_t *stat) {
	//Position =  numéro du file_entry
	position = 0;
	//Tant qu'on a pas le bon fichier, on appelle iterator.
	//Gérer les erreurs, gérer les tests sur le nom.	
}

int read_file(char *filename, unsigned char *buf) {
	
}

int remove_file(char *filename) {
	
}

//Iterateur pour trouver un fichier
int iterator(char *filename, int* position){

}

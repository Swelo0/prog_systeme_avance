#include "fs.h"
#include <stdio.h>

int main() {
	filesystem fs = sfscreate();
	sfsadd(fs, "test.txt");
	///////////////////
	numEntry = 0;
	while (fs.fe[numEntry].name[0] == '\0')
		numEntry++;
	
	printf("fichier : %s -> %d \n",fs.fe[numEntry].name, numEntry);
	return 0;

}

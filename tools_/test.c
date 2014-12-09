#include "fs.h"
#include <stdio.h>

int main() {

	filesystem fs = sfscreate();
	sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",(int64)fs.bitmap[0]);
	sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",(int64)fs.bitmap[0]);
	
	sfsdel(&fs, "test.txt");
	
	sfslist(&fs);
	
	printf("binarymap : %d \n",(int64)fs.bitmap[0]);

	return 0;
}

	///////////////////
	/*
	int numEntry = 0;
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1);
	
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1)	;
	*/

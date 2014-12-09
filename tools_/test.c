#include "fs.h"
#include <stdio.h>

int main() {

	filesystem fs = sfscreate();
	printf("binarymap : %d \n",fs.bitmap);
	sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",fs.bitmap);
	sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",fs.bitmap);
	///////////////////
	int numEntry = 0;
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1);
	
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1)	;
	
	
	// Dire à Sylvain de faire attention au numEntry -1.
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1);
	
	sfsdel(&fs, "TestFile");
	printf("binarymap : %d \n",fs.bitmap);
	
	numEntry = 0;
	while (fs.fe[numEntry++].name[0] == '\0');
	printf("fichier : %s -> %d \n",fs.fe[numEntry-1].name, numEntry-1);	

	return 0;
}

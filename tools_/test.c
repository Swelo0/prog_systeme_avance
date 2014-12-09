#include "fs.h"
#include <stdio.h>

int main() {

	filesystem fs = sfscreate();
	sfsadd(&fs, "test.txt"); printf("binarymap : %d \n",fs.bitmap);
	sfsadd(&fs, "test778.txt"); printf("binarymap : %d \n",fs.bitmap);
	sfsadd(&fs, "test54.txt"); printf("binarymap : %d \n",fs.bitmap);
	
	//sfsdel(&fs, "test.txt");
	
	sfslist(&fs);	

	return 0;
}

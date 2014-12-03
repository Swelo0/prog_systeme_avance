#include "fs.h"
#include <stdio.h>

int main() {

	filesystem fs = sfscreate();
	//sfsadd(fs, "test.txt");
	sfsdel(fs, "TestFile");

	return 0;

}

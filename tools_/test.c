#include "fs.h"
#include <stdio.h>

int main() {
	filesystem fs = sfscreate();
	sfsadd(fs, "test.txt");
	return 0;

}

#include "fs.h"
#include <stdio.h>

int main() {
	filesystem fs = sfscreate();
	fs.sfsadd("test.txt");
	return 0;

}

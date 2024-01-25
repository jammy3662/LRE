#include <stdio.h>
#include <math.h>

#include "pack.h"

int main (int argc, char** argv)
{
	printf ("Program ran successfully.\n");
	printf ("%c (endianness)\n", pack::endian);
	
	return 0;
}

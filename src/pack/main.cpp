#include <stdio.h>
#include <math.h>

#include "pack.h"

int main (int argc, char** argv)
{
	printf ("┌─────────────────────────────┐\n"
	        "│  Lagoon Resource Pack Tool  │\n"
					"└─────────────────────────────┘\n"
	        "Endianness: '%c'\n", pack::endian);
	
	return 0;
}

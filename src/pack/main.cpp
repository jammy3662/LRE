#include <stdio.h>
#include <math.h>

#include "pack.h"
#include "trie.h"

const char* usage =
"┌─────────────────────────────┐\n"
"│ USAGE: lgnpack [CMD] [ARGS] │\n"
"└─────────────────────────────┘\n"
"(Run with command 'help' for more options.)\n";

enum OP
{
	INFO=1,
	
	LOAD,
	SAVE,
	
	GET,
	LIST,
	
	ADD,
	SUB,
};

Trie <char, int, 0> options;

struct _setupOptionTree
{
	_setupOptionTree()
	{
		options.insert ("help", INFO);
		
		options.insert ("load", LOAD);
		options.insert ("save", SAVE);
		
		options.insert ("get", GET);
		options.insert ("list", LIST);
		options.insert ("ls", LIST);
		options.insert ("add", ADD);
		options.insert ("rm", SUB);
	}
}
_;

int main (int argc, char** argv)
{
	printf ("Endianness: '%c'\n", pack::endian);
	
	if (argc < 2)
	{
		fputs (usage, stdout);
		return 1;
	}
	
	int cmd = options.find (argv [1]);
	printf ("%s: %i\n", argv[1], cmd);
	
	return 0;
}

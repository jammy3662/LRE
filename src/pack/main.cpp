#include <stdio.h>
#include <math.h>

#include "pack.h"
#include "trie.h"

const char* usage =
"┌─────────────────────────────┐\n"
"│ USAGE: lgnpack [CMD] [ARGS] │\n"
"└─────────────────────────────┘\n"
"(Run with command 'help' for more options.)\n";

void nop(int, char**){};

void help (int, char**)
{
	printf ("lgnpack - Combine external resources into a compact resource pack binary\n");
}

void endian (int, char**)
{
	printf ("'%c' - current endianness\n", pack::endian);
}

typedef void (* handler) (int, char**);
handler commands [] =
{
	help,
	nop, nop, nop, nop, nop, nop,
	endian
};

Trie <char, 0, int, -1> options;

enum OP
{
	INFO, LOAD, SAVE, GET,
	LIST, ADD, SUB, END
};

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
		
		options.insert ("end", END);
	}
}
_;

int main (int argc, char** argv)
{
	if (argc < 2)
	{
		fputs (usage, stdout);
		return 1;
	}
	
	int cmd = options.find (argv [1]);
	printf ("%s: %i\n", argv[1], cmd);
	
	if (cmd <= sizeof commands / sizeof *commands)
		commands[cmd](argc, argv);
	
	if (cmd == END) printf ("Endianness: '%c'\n", pack::endian);
	
	return 0;
}

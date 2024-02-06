#include <stdio.h>
#include <math.h>

#include "pack.h"
#include "trie.h"

#include <ncurses.h>

enum OP
{
	ABOUT, LIST, ADD, SUB
};

const char* mainHelp =
"_________________________\n"
"lgnpack |COMMAND| |ARGS| \n"
"-------------------------\n"
"(Try command 'help.') \n";
;
const char* help =
"_________\n"
"lgnpack  | Combine external resources into a compact binary resource pack\n"
"---------\n"
"help  ->  Display this help page\n"
"  ls  ->  Display contents of a pack\n"
" add  ->  Load external resource(s) into a pack\n"
"  rm  ->  Delete resource(s) from a pack, permanently\n"
"---------\n"
"-- Hint: Run a command with no args for help on that command. --\n"
;
const char* listHelp =
"_________________\n"
"lgnpack ls -PACK-\n"
"-----------------\n"
"Show each resource contained in the pack, including\n"
"a unique identifier 'ID,' the resource type, and any\n"
"assigned name.\n";
;
const char* addHelp =
"________________________________________\n"
"lgnpack add |PACK| |FILE1| |FILE2| |...|\n"
"----------------------------------------\n"
"Add supported external resource(s) to the pack.\n"
"-- Warning: Resources cannot be converted back to their\n"
"original format once in the pack. Please keep a backup. --\n"
;
const char* subHelp =
"___________________________________\n"
"lgnpack rm |PACK| |ID1| |ID2| |...|\n"
"-----------------------------------\n"
"Delete a resource in the pack. You can find the ID of a\n"
"resource by running the 'ls' (list) command.\n"
;

const char* helpStrings [] =
{ mainHelp, help, listHelp, addHelp, subHelp };

void nop(int, char**){};

typedef void (* handler) (int, char**);
handler commands [] =
{
	nop, nop, nop, nop,
};

// initialize prefix tree with some function
// calls in a constructor
Trie <char, 0, int, -1> options;
struct _setupOptionTree
{ _setupOptionTree()
{
	options.insert ("help", ABOUT);
	options.insert ("list", LIST);
	options.insert ("ls", LIST);
	options.insert ("add", ADD);
	options.insert ("rm", SUB);
}} _;

int main (int argc, char** argv)
{
	if (argc < 2)
	{
		printf ("%s", mainHelp);
		return 1;
	}
	
	int cmd = options.find (argv [1]);
	
	if (argc < 3)
		printf ("%s", helpStrings [cmd+1]);
	
	if (cmd <= sizeof commands / sizeof *commands)
		commands[cmd](argc, argv);
}

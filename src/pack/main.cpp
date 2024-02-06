#include <stdio.h>
#include <math.h>

#include "pack.h"
#include "trie.h"

#include <ncurses.h>

enum OP
{
	ABOUT, LIST, NEW, ADD, SUB
};

const char* mainHelp =
"__________________________\n"
" lgnpack |COMMAND| |ARGS| \n"
"--------------------------\n"
"(Try command 'help.') \n";
;
const char* help =
"___________\n"
"| lgnpack | Combine external resources into an OpenGL-friendly binary resource pack\n"
"-----------\n"
"help  ->  Display this help page\n"
"  ls  ->  Display contents of a pack\n"
" new  ->  Create a new, empty pack\n"
" add  ->  Load external resource(s) into a pack\n"
"  rm  ->  Delete resource(s) from a pack, permanently\n"
"---------\n"
"-- Hint: Run a command with no args for help on that command. --\n"
;
const char* listHelp =
"___________________\n"
" lgnpack ls |PACK| \n"
"-------------------\n"
"Show each resource contained in the pack, including\n"
"a unique identifier 'ID,' the resource type, and any\n"
"assigned name.\n";
;
const char* newHelp =
"_________________________\n"
" lgnpack new |PATH| (fv) \n"
"-------------------------\n"
"Create an empty resource pack at the given filepath.\n"
"f ~ overwrite the file at the given path if it exists\n"
"v ~ show a message if an existing file was overwritten\n"
;
const char* addHelp =
"__________________________________________\n"
" lgnpack add |PACK| |FILE1| |FILE2| |...| \n"
"------------------------------------------\n"
"Add supported external resource(s) to the pack.\n"
"-- Warning: Resources cannot be converted back to their\n"
"original format once in the pack. Please keep a backup. --\n"
;
const char* subHelp =
"_____________________________________\n"
" lgnpack rm |PACK| |ID1| |ID2| |...|\n"
"-------------------------------------\n"
"Delete a resource in the pack. You can find the ID of a\n"
"resource by running the 'ls' (list) command.\n"
;

const char* helpStrings [] =
{ mainHelp, help, listHelp, newHelp, addHelp, subHelp };

void nop(int, char**){};

typedef void (* handler) (int, char**);
handler commands [] =
{
	nop, nop, nop, nop, nop
};

// initialize prefix tree with some function
// calls in a constructor
Trie <char, 0, int, -1> options;
struct _setupOptionTree
{ _setupOptionTree()
{
	options.insert ("--help", ABOUT);
	options.insert ("help", ABOUT);
	options.insert ("list", LIST);
	options.insert ("ls", LIST);
	options.insert ("add", ADD);
	options.insert ("rm", SUB);
	options.insert ("new", NEW);
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

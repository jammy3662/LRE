#include <stdio.h>
#include <math.h>

#include "pack.h"
#include "trie.h"
#include "import.h"

#include <ncurses.h>

enum OP
{
	ABOUT, LIST, NEW, ADD, SUB, OP_CT
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
"v ~ show a message if a file was replaced\n"
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

void newPack (int argc, char** args)
{
	bool overwrite = false, verbose = false;
	
	if (argc > 1)
	{
	// parse options
	char* c = args[1];
	if (*c == '-') ++c;
	for (; *c != 0; ++c)
	switch (*c)
	{
		case 'f':
			overwrite = true;
			break;
		case 'v':
			verbose = true;
			break;
		
		default:
			fprintf (stderr, "[o] '%c' Unknown option (ignored)\n", *c);
			break;
	}}
	
	const char* path = args [0];
	FILE* dst = fopen (path, "r");
	
	// file already exists
	if (dst != 0x0)
	{
		if (!overwrite)
		{
			fprintf (stderr, "[x] File at '%s' already exists (cancelled)\n", path);
			fclose (dst);
			return;
		}
		
		if (verbose)
			fprintf (stderr, "[o] Replaced file at '%s'\n", path);
	}
	
	pack::save (path);
}

void nop(int, char**){};

typedef void (* handler) (int, char**);
handler commands [] =
{
	nop, nop, newPack, nop, nop, nop,
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
		fprintf (stderr, "%s", mainHelp);
		return 1;
	}
	
	int cmd = options.find (argv [1]);
	
	if (argc < 3 or cmd == -1)
	{
		fprintf (stderr, "%s", helpStrings [cmd+1]);
		return 2;
	}
	
	pack::loadShader ("SHADER", "SHADER");
	
	if (cmd <= sizeof commands / sizeof *commands)
		commands[cmd](argc-2, argv+2);
}

#ifndef PACK_DOT_H
#define PACK_DOT_H

/*________________________________________________________________
|
| Read from a binary file and convert to IR, or vice versa.
| Loaded resources are buffered, similarly to within the binary.
|________________________________________________________________*/

typedef int rid;

namespace pack
{
	enum ENDIAN
	{ LIL = 'l', BIG = 'b' };
	
	extern char endian;
	
	extern const char* filepath;
	
	void save (const char* path = filepath); // only for editing a pack
	void load (const char* path);
	
	rid texture (const char* name);
	rid model (const char* name);
	rid pipe (const char* name);
}

#endif

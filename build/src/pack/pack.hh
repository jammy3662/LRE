#ifndef PACK_DOT_H
#define PACK_DOT_H

/*________________________________________________________________
|
| Read from a binary file and convert to IR, or vice versa.
| Loaded resources are buffered, similarly to within the binary.
|________________________________________________________________*/

#include "resource.h"

// REPLACE WITH FRONTEND RESOURCE STRUCTS
typedef struct{} temp_t;

namespace pack
{
	enum ENDIAN
	{ LIL = 'l', BIG = 'b' };
	
	extern char endian;
	
	extern const char* filepath;
	
	void writeFile (const char* path = filepath);
	void loadFile (const char* path);
	
	temp_t getTexture (const char* name);
	temp_t getModel (const char* name);
}

#endif

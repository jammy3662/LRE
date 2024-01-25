#ifndef PACK_DOT_H
#define PACK_DOT_H

/*________________________________________________________________
|
| Read from a binary file and convert to IR, or vice versa.
| Loaded resources are buffered, similarly to within the binary.
|________________________________________________________________*/

// TODO: move these into resource module
// tell compiler to treat these as seperate types instead of just int
typedef enum{} ridt; // texture resource
typedef enum{} ridm; // model resource
typedef enum{} ridp; // pipeline resource

namespace pack
{
	enum ENDIAN
	{ LIL = 'l', BIG = 'b' };
	
	static char endian;
	
	static const char* filepath;
	
	void writeFile (const char* path = filepath);
	void loadFile (const char* path);
	
	ridt texture (const char* name);
	ridm model (const char* name);
	ridp pipe (const char* name);
}

#endif

#ifndef PACK_DOT_H
#define PACK_DOT_H

/*________________________________________________________________
|
| Read from a binary file and convert to IR, or vice versa.
| Loaded resources are buffered, similarly to within the binary.
|________________________________________________________________*/

// TODO: move these into resource (frontend) module (aka renderer)
typedef enum{} ridt; // texture resource
typedef enum{} ridm; // model resource
typedef enum{} ridp; // pipeline resource

namespace pack
{
	enum ENDIAN
	{ LIL = 'l', BIG = 'b' };
	
	extern const char endian;
	
	extern const char* filepath;
	
	void save (const char* path = filepath); // only for editing a pack
	void load (const char* path);
	
	ridt texture (const char* name);
	ridm model (const char* name);
	ridp pipe (const char* name);
}

#endif

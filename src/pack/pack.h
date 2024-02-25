#ifndef PACK_DOT_H
#define PACK_DOT_H

//________________________________________________________________
//|
//| Read from a binary file and convert to IR, or vice versa.
//| Loaded resources are buffered, similarly to within the binary.
//|________________________________________________________________

#define rid int

namespace pack
{	
	#include <stdint.h>
	
	struct res
	{
		int16_t type;
		int16_t length;
		void* data;
	}
	
	typedef int16_t rsid;
	
	enum ENDIAN
	{ LIL = 'l', BIG = 'b' };
	
	extern char endian;
	
	extern const char* filepath;
	
	void save (const char* path = filepath); // only for editing a pack
	void load (const char* path);
	
	rsid getres (const char* name);
	
	void loadShader (const char* vertex, const char* pixel);
	
	rsid texture (const char* name);
	rsid model (const char* name);
	rsid pipe (const char* name);
}

#endif

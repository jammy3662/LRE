#include "import.h"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

Shader importShader (const char* vs, const char* ps)
{
	Shader ret;
	
	FILE* vert;
	FILE* pixl;

	vert = fopen (vs, "r");
	fseek (vert, 0, SEEK_END);
	
	int sz = ftell (vert);
	arr<int8_t> vstring;
	vstring.allocate (sz+1);
	
	fseek (vert, 0, SEEK_SET);
	fread (vstring, 1, sz, vert);
	fclose (vert);
	vstring [sz+1] = 0;
	
	pixl = fopen (ps, "r");
	fseek (pixl, 0, SEEK_END);
	
	sz = ftell (pixl);
	arr<int8_t> pstring;
	pstring.allocate (sz+1);
	
	fseek (pixl, 0, SEEK_SET);
	fread (pstring, 1, sz, pixl);
	fclose (pixl);
	pstring [sz+1] = 0;
	
	ret.vertex = vstring;
	ret.pixel = pstring;
	
	return ret;
}

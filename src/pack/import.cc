#include "import.h"

#include <stdio.h>

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

namespace loader {

int8_t* importShader (const char* vs, const char* ps, int* lenVs, int* lenPs)
{
	FILE* vert;
	FILE* pixl;

	vert = fopen (vs, "r");
	pixl = fopen (ps, "r");
	
	if (!vert or !pixl)
	{
		fprintf (stderr, "[x] Shader file at '%s'/'%s' failed to open\n", vs, ps);
		return 0x0;
	}
	
	fseek (vert, 0, SEEK_END);
	
	arr<int8_t> string;
	
	int szV = ftell (vert);
	string.allocate (szV+1);
	string.count = szV+1;
	
	fseek (vert, 0, SEEK_SET);
	fread (string.buf, 1, szV, vert);
	fclose (vert);
	string [string.count] = 0;
	
	fseek (pixl, 0, SEEK_END);
	
	int szP = ftell (pixl);
	string.allocate (szP+1 + string.count);
	string.count += szP+1;
	
	fseek (pixl, 0, SEEK_SET);
	fread (string.buf + string.count, 1, szP, pixl);
	fclose (pixl);
	string [string.count] = 0;
	
	if (lenVs) *lenVs = szV;
	if (lenPs) *lenPs = szP;
	
	return string;
}

} // namespace

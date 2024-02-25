#include "import.h"

#include <stdio.h>

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

#include "pack.dev.h"

namespace loader {

void importShader (const char* vs, const char* ps)
{
	Shader shr;
	
	FILE* vert;
	FILE* pixl;
	
	arr<int8_t> vertex;
	arr<int8_t> pixel;

	vert = fopen (vs, "r");
	pixl = fopen (ps, "r");
	
	if (!vert or !pixl)
	{
		fprintf (stderr, "[x] Shader file at '%s'/'%s' failed to open\n", vs, ps);
		return;
	}
	
	fseek (vert, 0, SEEK_END);
	
	int szV = ftell (vert);
	vertex.allocate (szV+1);
	vertex.count = szV+1;
	
	fseek (vert, 0, SEEK_SET);
	fread (vertex.buf, 1, szV, vert);
	fclose (vert);
	vertex [vertex.count] = 0;
	
	fseek (pixl, 0, SEEK_END);
	
	int szP = ftell (pixl);
	pixel.allocate (szP+1);
	pixel.count += szP+1;
	
	fseek (pixl, 0, SEEK_SET);
	fread (pixel.buf + pixel.count, 1, szP, pixl);
	fclose (pixl);
	pixel [pixel.count] = 0;
	
	shr.vertex = vertex;
	shr.pixel = pixel;
	pack::insert (shr);
}

} // namespace

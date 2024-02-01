/*
________________________________________________________________________________________________________________________________
|
| To guarantee platform independent output:
|
| - using fixed-size int types (stdint.h)
| - floats match standard IEEE 754 (for most architectures)
| - storing data as little endian internally
| - checking and converting endianness at runtime
| - no byte padding
|
|________________________________________________________________________________________________________________________________
*/

#include "brief.h"
#include "container.h"
#include "trie.h"
#include "bytes.h"
#include "pack.h"
#include "resource.h"

#include <stdio.h>

char pack::endian = '?';
const char* pack::filepath;

typedef int8_t chr;

struct platform
{
	platform ()
	{ // test byte order only once upfront
		pack::endian = bytes::testendian ();
	}
}
platform;

// track loaded resources by name and index
Trie <chr, rid, 0>
texturenames = {0},
modelnames = {0};

// fixed data structures
// (reference variable length buffers)
arr<Texture> textures;
arr<Material> materials;
arr<Mesh> meshes;

// raw data streams
// indeterminate size
arr<Shader> shaders;
arr<int8_t> imagesBuf;
arr<float> verticesBuf;
arr<int16_t> indicesBuf;
arr<arr<int16_t> > models;

void save (const char* path)
{
	FILE* out = fopen (path, "w");
	
	// write fixed-size data first, which points to internal 'heap'
	
	fprintf (out, "%hu", textures.used);
	fwrite (textures, sizeof (Texture), textures.used, out);

	fprintf (out, "%hu", materials.used);
	fwrite (materials, sizeof (Material), materials.used, out);

	fprintf (out, "%hu", meshes.used);
	fwrite (meshes, sizeof (Mesh), meshes.used, out);
	
	// buffers and streams, variable-size data
	fprintf (out, "%hu", shaders.used);
	for (int16_t i = 0; i < shaders.used; ++i)
	{
		const Shader s = shaders [i];
		fprintf (out, "%s", s.vertex);
		fprintf (out, "%s", s.pixel);
	}
	
	fprintf (out, "%hu", models.used);
	for (int16_t i = 0; i < models.used; ++i)
	{
		arr<int16_t> mdl = models [i];
		
		fprintf (out, "%hu", mdl.used);
		fwrite (mdl, sizeof (int16_t), mdl.used, out);
	}
}

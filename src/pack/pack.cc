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
	
	fprintf (out, "%hu", textures.count);
	fwrite (textures, sizeof (Texture), textures.count, out);

	fprintf (out, "%hu", materials.count);
	fwrite (materials, sizeof (Material), materials.count, out);

	fprintf (out, "%hu", meshes.count);
	fwrite (meshes, sizeof (Mesh), meshes.count, out);
	
	// buffers and streams, variable-size data
	fprintf (out, "%hu", shaders.count);
	for (int16_t i = 0; i < shaders.count; ++i)
	{
		const Shader s = shaders [i];
		fprintf (out, "%s", s.vertex);
		fprintf (out, "%s", s.pixel);
	}
	
	fprintf (out, "%hu", models.count);
	for (int16_t i = 0; i < models.count; ++i)
	{
		arr<int16_t> mdl = models [i];
		
		fprintf (out, "%hu", mdl.count);
		fwrite (mdl, sizeof (int16_t), mdl.count, out);
	}
	
	fclose (out);
}

void load (const char* path)
{
	FILE* in = fopen (path, "r");
	
	fscanf (in, "%hu", &textures.count);
	textures.allocate (textures.count);
	for (int i = 0; i < textures.count; ++i)
	{
		fread (textures, sizeof (Texture), textures.count, in);
	}
	
	fscanf (in, "%hu", &materials.count);
	materials.allocate (materials.count);
	for (int i = 0; i < materials.count; ++i)
	{
		fread (materials, sizeof (Material), materials.count, in);
	}
	
	fscanf (in, "%hu", &meshes.count);
	textures.allocate (meshes.count);
	for (int i = 0; i < meshes.count; ++i)
	{
		fread (meshes, sizeof (Mesh), meshes.count, in);
	}
}

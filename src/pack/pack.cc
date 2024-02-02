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
Trie <chr, 0, rid, -1>
texturenames = {0},
modelnames = {0};

// fixed data structures
// (reference variable length buffers)
arr<Texture> textures;
arr<Material> materials;
arr<Mesh> meshes;

// raw data streams
// indeterminate size
arr<int8_t> shaders;
arr<int8_t> images;
arr<float> vertices;
arr<int16_t> indices;
arr<int16_t> models;

template <typename T>
void writearr (arr<T> src, FILE* dst)
{
	fprintf (dst, "%hu", src.count);
	fwrite (src, sizeof(T), src.count, dst);
}

template <typename T>
void readarr (FILE* src, arr<T>& dst)
{
	fscanf (src, "%hu", &dst.count);
	dst.allocate (dst.count);
	fread (dst, sizeof(T), dst.count, src);
}

void save (const char* path)
{
	FILE* out = fopen (path, "w");
	
	if (out == 0)
	{
		fprintf (stderr, "Can't save the resource pack at the given location. ('%s')\n", path);
		return;
	}
	
	writearr (textures, out);
	writearr (materials, out);
	writearr (meshes, out);
	
	// buffers and streams, variable-size data
	writearr (shaders, out);
	writearr (images, out);
	writearr (vertices, out);
	writearr (indices, out);
	writearr (models, out);
	
	fclose (out);
}

void load (const char* path)
{
	FILE* in = fopen (path, "r");
	
	if (in == 0)
	{
		fprintf (stderr, "Can't open the file or resource pack. ('%s')\n", path);
		return;
	}
	
	readarr (in, textures);
	readarr (in, materials);
	readarr (in, meshes);
	
	// buffers and streams, variable-size data
	readarr (in, shaders);
	readarr (in, images);
	readarr (in, vertices);
	readarr (in, indices);
	readarr (in, models);
	
	fclose (in);
}

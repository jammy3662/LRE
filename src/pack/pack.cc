//________________________________________________________________________________________________________________________________
//|
//| To guarantee platform independent output:
//|
//| - using fixed-size int types (stdint.h)
//| - floats match standard IEEE 754 (for most architectures)
//| - storing data as little endian internally
//| - checking and converting endianness at runtime
//| - no byte padding
//|
//|________________________________________________________________________________________________________________________________

#include "container.h"

#include "pack.h"
#include "pack.dev.h"

#include "trie.h"
#include "bytes.h"
#include "import.h"

#include "resource.h"

#include <stdio.h>

void pack::insert (Shader shr) {}
void pack::insert (Material mtl) {}
void pack::insert (Texture txr) {}
void pack::insert (Mesh msh) {}

using namespace ir;

char endian = '?';
const char* filepath = 0x0;

template <typename T>
T reord (T t)
{ return t; }

Shader reord (Shader shr)
{
	// shader code uses single-byte chars
	// no conversion needed
	return shr;
}

Material reord (Material mtl)
{
	if (pack::endian != 'l')
	{
		mtl.shine = bytes::bswap (mtl.shine);
		mtl.refl = bytes::bswap (mtl.refl);
		
		mtl.texture.diffuse = bytes::bswap (mtl.texture.diffuse);
		mtl.texture.normal = bytes::bswap (mtl.texture.normal);
		mtl.texture.height = bytes::bswap (mtl.texture.height);
		mtl.texture.specular = bytes::bswap (mtl.texture.specular);
	}
	return mtl;
}

Texture reord (Texture txr)
{
	if (pack::endian != 'l')
	{
		txr.bits = bytes::bswap (txr.bits);
		txr.width = bytes::bswap (txr.width);
		txr.height = bytes::bswap (txr.height);
		txr.depth = bytes::bswap (txr.depth);
		txr.texels = bytes::bswap (txr.texels);
	}
	return txr;
}

Mesh reord (Mesh msh)
{
	if (pack::endian != 'l')
	{
		for (int i = 0; i < 8; ++i)
		{
			msh.attribs [i] = bytes::bswap (msh.attribs [i]);
			msh.material = bytes::bswap (msh.material);
			msh.stream.vertex = bytes::bswap (msh.stream.vertex);
			msh.stream.index = bytes::bswap (msh.stream.index);
		}
	}
	return msh;
}

struct platform
{
	platform ()
	{ // test byte order only once upfront
		endian = bytes::testendian ();
	}
}
platform;

// track loaded resources by name and index
Trie <int8_t, 0, rid, -1>
texturenames,
modelnames;

// fixed data structures
// (reference variable length buffers)
arr<Texture> textures;
arr<Material> materials;
arr<Mesh> meshes;

// raw data streams
// indeterminate size
arr<int8_t> shaders;
arr<int8_t> images;
arr<int8_t> vertices;
arr<int16_t> indices;
arr<int16_t> models;

template <typename T>
void writearr (arr<T> src, FILE* dst)
{
	if (pack::endian == 'b') src.count = bytes::bswap ((int16_t) src.count);
	
	for (int i = 0; i < src.count; ++i)
	{
		src [i] = reord (src [i]);
	}
	
	fwrite (&src.count, sizeof src.count, 1, dst);
	
	fwrite (src, sizeof(T), src.count, dst);
}

template <typename T>
void readarr (FILE* src, arr<T>& dst)
{
	fread (&dst.count, sizeof dst.count, 1, src);
	
	if (pack::endian == 'b') dst.count = bytes::bswap ((int16_t) dst.count);
	
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

void loadShader (const char* vs, const char* fs)
{
	int vln, sln, ct;
	loader::importShader (vs, fs);
}

} // namespace

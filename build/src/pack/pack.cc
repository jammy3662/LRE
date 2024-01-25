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

using namespace res;

namespace pack
{
	// track loaded resources by name and index
	static Trie <int8, int16, 0> texturenames = {0},
		               modelnames = {0};

	static arr <Shader>
		shaders = {0};

	static arr <Texture>
		textures = {0};

	static arr <Material>
		materials = {0};

	static arr <Mesh>
		meshes = {0};

	static arr <Model>
		models = {0};
}

static
struct platform
{
	platform ()
	{ // test byte order only once upfront
		pack::endian = bytes::testendian (); }
}
platform;

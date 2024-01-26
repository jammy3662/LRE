#ifndef RESOURCE_DOT_H
#define RESOURCE_DOT_H

/*________________________________________________________________
|
| Memory layout of resources in IR (intermediate representation).
|________________________________________________________________*/

#include <stdint.h>
#include "container.h"

// no padding (single-byte aligned)
#pragma pack (push, 1)

typedef enum { RGB, GBR, BRG, RBG, GRB, BGR } texel_type;
typedef int8_t attrib;

typedef int8_t chr;
typedef int16_t rid; // index into internal buffer of resource pack

namespace res {
	
struct Shader
{
	const chr* vertexCode;
	const chr* fragmentCode;
};

struct Texture
{
	struct // texture metadata
	{
		int8_t type : 2;
		int8_t channels : 3;
		int8_t order : 3;
	}
	properties;
	
	int16_t width, height, depth;
	
	// array of raw texels (could be pixels or voxels, etc)
	arr <int8_t> texels;
};

struct Material
{
	float shine, refl;
	rid diffuse, normal, height, specular;
};

// a collection of vertices amd indices
struct Mesh
{
	int8_t nAttribs;
	
	struct // what's in each vertex?
	{
		enum { CHAR = 1, SHORT = 2, INT = 4,
		       LONG = 8, FLOAT = 4, DOUBLE = 8, }
		type : 4;
		
		int8_t
		count : 4;
	}
	attribs [8];
	
	int32_t nVertices, nIndices;

	arr <float> vertexStream;
	arr <int16_t> indexStream;

	rid material;
};

// one or more meshes to be drawn as a single object
struct Model
{
	arr <Mesh> meshes;
};

}

// restore default byte alignment
#pragma pack (pop)

#endif

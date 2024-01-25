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

typedef int16_t rid; // index into internal buffer of resource pack

namespace res {
	
struct Shader
{
	const int8_t* vertexCode;
	const int8_t* fragmentCode;
};

struct Texture
{
	int8_t properties; // texture metadata
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
	int8_t attribTypes [8];
	int8_t attribCounts [8];
	
	int32_t nVertices, nIndices;

	arr <float> vertexStream;
	arr <int16_t> indexStream;

	rid mtl;
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

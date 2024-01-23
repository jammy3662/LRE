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

namespace res {
	
struct Shader
{
	const int8_t* vertexCode;
	const int8_t* fragmentCode;
};

// raw texel data in a buffer
typedef arr <int8_t> Image;

struct Texture
{
	int8_t properties; // texture metadata
	int16_t width, height, depth;
	
	typedef arr <int8_t> Image;

	arr <Image> 

	arr <int8_t> texels; // array of raw texels (could be pixels or voxels, etc)
};

struct Material
{
	float shine, refl;
	int16_t diffuse, normal, height, specular;
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

	int16_t mtl; // index into material list
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

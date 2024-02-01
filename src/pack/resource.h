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
	
struct Shader
{
	//struct
	//{
		int8_t* vertex;
	  int8_t* pixel;
	//}
	//code;
};

struct Texture
{
	struct // metadata bitfield
{ int8_t type : 2;
	int8_t channels : 3;
	int8_t order : 3; }
	bits;
	
	int16_t width, height, depth;
	
	int16_t texels;
};

struct Material
{
	float shine, refl;
	
	struct
	{ int16_t diffuse, normal,
	          height, specular; }
	texture;
};

// a collection of vertices amd indices
struct Mesh
{
	struct
	{ int8_t count : 4;
	  int8_t type : 4;
	}
	attribs [8];
	
	int16_t material;
	
	struct { int16_t vertex, index; }
	stream;
};

// restore default byte alignment
#pragma pack (pop)

#endif

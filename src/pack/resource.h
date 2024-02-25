#ifndef RESOURCE_DOT_H
#define RESOURCE_DOT_H

//________________________________________________________________
//|
//| Memory layout of resources in IR (intermediate representation).
//|________________________________________________________________

#include <stdint.h>
#include "container.h"

namespace ir {

// no padding (single-byte aligned)
#pragma pack (push, 1)

struct Shader
{
	int8_t* vertex;
	int8_t* pixel;
};

struct Texture
{
	// T - dimensionality
	// C - # channels
	// R - rgb order
	// ~~~~~~~~~
	// TT CC CR RR
	// ~~~~~~~~~
	int8_t bits;
	
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
	// C - # values
	// T - type of value
	// ~~~~~~~~~
	// CCCC TTTT
	// ~~~~~~~~~
	int8_t attribs [8];
	
	int16_t material;
	
	struct { int16_t vertex, index; }
	stream;
};

} // namespace

// restore default byte alignment
#pragma pack (pop)

#endif

#pragma once
#include <vector>

template <typename T>
using array = std::vector <T>;

using byte = unsigned char;

// placeholder definitions;
// replace with struct / pointer / whatever
typedef void* Renderable;
typedef void* Uniform;
typedef void* Frame;
typedef void* Shader;



// 2D object with (optional) texture
struct Sprite
{
	float x, y;
	float w, h;
	
	// index of texture to draw
	unsigned short tex;
};

struct Renderable
{
	float x, y, z; // position
	float pitch, yaw, roll; // rotation
	float sx, sy, sz; // scale
};

// series of render commands and associated data
struct Pipe
{
	array <Renderable*> objects;
	
	Shader shader;
	array <Uniform*> uniforms;
	
	Frame* target;
};

// a series of render pipes to produce the final frame
using Pipeline = array <Pipe>;

template <typename T>
void serialize (T data);

#ifndef IMPORT_DOT_H
#define IMPORT_DOT_H

/*________________________________________________________________
|
| Load common resource formats from files and convert into
| low-level IR. These formats include meshes, textures, and
| rendering pipelines, as well as other related data.
|________________________________________________________________*/

#include "container.h"
#include "resource.h"

Shader importShader (const char* vrtPath, const char* pixPath);
Texture importTexture (const char* path);

// import meshes from '.obj' file, including
// any attached textures and materials
arr<int16_t> importModel ();

#endif

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

namespace loader {

int8_t* importShader (const char* vrtPath, const char* pixPath, int* vrtLen = 0x0, int* pixLen = 0x0);
Texture importTexture (const char* path);

// import meshes from '.obj' file, including
// any attached textures and materials
arr<int16_t> importModel ();

} // namespace

#endif

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

using namespace ir;

// index into interal pack array
typedef int16_t rsid;

void importShader (const char* vrtPath, const char* pixPath);
void importTexture (const char* path);
void importModel (const char* path);

/* TODO: write the file format */
void importPipeline (const char* path);

} // namespace

#endif

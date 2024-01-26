The pack module handles game resources.

This includes
 - loading a resource pack from a file,
 - modifying a resource pack,
 - saving a resource pack to a file, and
 - importing game resources from common file
   formats.

The purpose of resource packs is to
precalculate the most optimal organization of
rendering calls, and to provide a
straightforward interface to integrate
resources with any project, without the
boilerplate and semantics of calling OpenGL
directly, and managing its state yourself.


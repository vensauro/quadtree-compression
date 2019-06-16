#ifndef __QuadTree__
#define __QuadTree__

#include "EstruturasDeDados.h"

typedef struct quadtree
{
	tQuadrante *key_value;

	struct quadtree *childs[4];

} TQuadtree;

TQuadtree *new (tPonto pBase, int h, int w, int cor, int altura_nivel);

void nivel(TQuadtree **child, tPonto inicio, int h, int w, int altura_nivel, int cor_pai);

void in(TQuadtree node);

void inNivel(TQuadtree node, int lvl);

void parseError(TQuadtree **node, int err);

#endif // __QuadTree__

#ifndef __QuadTree__
#define __QuadTree__

#include "EstruturasDeDados.h"

typedef struct quadtree
{
	tQuadrante *key_value;

	struct quadtree *childs[4];

} TQuadtree;

TQuadtree *new (tPonto pBase, int h, int w, int cor, int altura_nivel);

void in(TQuadtree node);

#endif // __QuadTree__

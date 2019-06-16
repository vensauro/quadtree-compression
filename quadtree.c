#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"

TQuadtree *new (tPonto pBase, int h, int w, int cor, int altura_nivel)
{
	TQuadtree *node = malloc(sizeof(TQuadtree));
	if (node == NULL)
		return NULL;

	tQuadrante *key = malloc(sizeof(tQuadrante));

	key->pBase = pBase;
	key->h = h;
	key->w = w;
	key->cor = cor;
	key->erro = 0.0;
	key->nivel = altura_nivel;

	node->key_value = key;
	for (int i = 0; i < 4; i++)
	{
		node->childs[i] = NULL;
	}

	return node;
}

void in(TQuadtree node)
{
	printf("Nó de nivel %d com valor %d\n", node.key_value->nivel, node.key_value->cor);
	if (node.childs[0] != NULL)
		in(*node.childs[0]);

	if (node.childs[1] != NULL)
		in(*node.childs[1]);

	if (node.childs[2] != NULL)
		in(*node.childs[2]);

	if (node.childs[3] != NULL)
		in(*node.childs[3]);
}

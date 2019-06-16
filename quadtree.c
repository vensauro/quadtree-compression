#include <stdio.h>
#include <stdlib.h>
#include "winGL.h"
#include "quadtree.h"

extern int iHeight, iWidth;
extern unsigned char *image;

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

void nivel(TQuadtree **child, tPonto inicio, int h, int w, int altura_nivel, int cor_pai)
{
	int largura = w;
	// == 1 ? w : inicio.x + w;
	int altura = h;
	//  == 1 ? h : inicio.y + h;
	int soma = 0;
	float pixels[w * h];
	int iterate = 0;

	for (int i = inicio.y; i < inicio.y + h; i++)
		for (int j = inicio.x; j < inicio.x + w; j++)
		{
			int pixel = image[i * iWidth + j];
			soma += pixel;
			pixels[iterate++] = pixel;
		}

	float media = soma / (largura * altura);
	// printf("Media: %d", largura);
	float greater = 0;

	for (int i = 0; i < largura * altura; i++)
	{
		float abs = media - pixels[i];
		abs = abs >= 0 ? abs : -abs;
		abs /= pixels[i];
		// abs *= 100;
		if (abs > greater)
			greater = abs;
	}

	*child = new (inicio, altura, largura, media, altura_nivel);
	(*child)->key_value->erro = greater;

	if (largura <= 1)
		return;
	else if (altura <= 1)
		return;

	tPonto envia_nivel = inicio;
	nivel(&(*child)->childs[0], envia_nivel, altura / 2, largura / 2, altura_nivel + 1, media);

	envia_nivel.x += largura / 2;
	nivel(&(*child)->childs[1], envia_nivel, altura / 2, largura / 2, altura_nivel + 1, media);

	envia_nivel.y += altura / 2;
	nivel(&(*child)->childs[2], envia_nivel, altura / 2, largura / 2, altura_nivel + 1, media);

	envia_nivel.x = inicio.x;
	nivel(&(*child)->childs[3], envia_nivel, altura / 2, largura / 2, altura_nivel + 1, media);
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

void inNivel(TQuadtree node, int lvl)
{
	// printf("Nó de nivel %d com valor %d\n", node.key_value->nivel, node.key_value->cor);
	if (node.key_value->erro <= 0.05 * lvl)
	{
		tPonto final;
		final.x = node.key_value->pBase.x + node.key_value->w;
		final.y = node.key_value->pBase.y + node.key_value->h;
		desenhaQuadrante(node.key_value->pBase, final, node.key_value->cor);

		// printf("i.x: %d  i.y: %d\t", node.key_value->pBase.x, node.key_value->pBase.y);
		// printf("f.x: %d  f.y: %d\n", final.x, final.y);
		// printf("cor: %f\n", node.key_value->erro);

		return;
	}
	if (node.childs[0] != NULL)
		inNivel(*node.childs[0], lvl);

	if (node.childs[1] != NULL)
		inNivel(*node.childs[1], lvl);

	if (node.childs[2] != NULL)
		inNivel(*node.childs[2], lvl);

	if (node.childs[3] != NULL)
		inNivel(*node.childs[3], lvl);
}

void parseError(TQuadtree **node, int err)
{
	// for (int i = inicio.y; i < inicio.y + h; i++)
	// 	for (int j = inicio.x; j < inicio.x + w; j++)
	// 	{
	// 		soma += image[i * iWidth + j];
	// 	}

	// int media = soma / (largura * altura)

	if ((*node)->childs[0] != NULL)
		parseError(&(*node)->childs[0], err);

	if ((*node)->childs[1] != NULL)
		parseError(&(*node)->childs[1], err);

	if ((*node)->childs[2] != NULL)
		parseError(&(*node)->childs[2], err);

	if ((*node)->childs[3] != NULL)
		parseError(&(*node)->childs[3], err);
}

// #define erroValue = 0.05;

// void erroParse(TQuadtree **pai)
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		bool b;
// 		float v = (*pai)->key_value->cor / (*pai)->childs[i]->key_value->cor;
// 		v--;
// 		if (erroValue >= v)
// 		{
// 			b = true;
// 			return b;
// 		}
// 	}
// }

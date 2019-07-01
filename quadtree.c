#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "winGL.h"
#include "quadtree.h"

extern int iHeight, iWidth, max_level, max_erro;
extern unsigned char *image;

TQuadtree *new (tPonto pBase, int h, int w, int cor, int altura_nivel, float erro)
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
	key->erro = erro;

	node->key_value = key;
	for (int i = 0; i < 4; i++)
	{
		node->childs[i] = NULL;
	}

	return node;
}

void monta(TQuadtree **child, tPonto inicio, int altura, int largura, int altura_nivel)
{
	if (altura_nivel > max_level)
		max_level = altura_nivel;

	int soma = 0;
	float pixels[largura * altura];
	int iterate = 0;

	for (int i = inicio.y; i < inicio.y + altura; i++)
		for (int j = inicio.x; j < inicio.x + largura; j++)
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
		if (abs > greater)
			greater = abs;
	}
	if (greater > max_erro)
		greater = max_erro;

	*child = new (inicio, altura, largura, media, altura_nivel, greater);

	float l = largura;
	float a = altura;

	if (l <= 1)
		return;
	else if (a <= 1)
		return;

	tPonto envia_nivel = inicio;
	monta(&(*child)->childs[0], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);

	envia_nivel.x += largura / 2;
	monta(&(*child)->childs[1], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);

	envia_nivel.y += altura / 2;
	monta(&(*child)->childs[2], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);

	envia_nivel.x = inicio.x;
	monta(&(*child)->childs[3], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);
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

void inNivel(TQuadtree node, int lvl, bool isErro)
{
	// printf("Nó de nivel %d com valor %d\n", node.key_value->nivel, node.key_value->cor);

	if (isErro ? node.key_value->erro <= 0.05 * lvl : node.key_value->nivel == lvl)
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
		inNivel(*node.childs[0], lvl, isErro);

	if (node.childs[1] != NULL)
		inNivel(*node.childs[1], lvl, isErro);

	if (node.childs[2] != NULL)
		inNivel(*node.childs[2], lvl, isErro);

	if (node.childs[3] != NULL)
		inNivel(*node.childs[3], lvl, isErro);
}

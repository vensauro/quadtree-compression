#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>

#include "EstruturasDeDados.h"
#include "winGL.h"
#include "arvore.h"

#include "quadtree.h"

unsigned char *image = NULL; // image file
int iHeight,
	iWidth,
	iChannels;

bool desenha = false;

TQuadtree *root = NULL;

// ***********************************************
// ******                                   ******
// ***********************************************

char pegaCor(int x, int y)
{
	return image[y * iWidth + x];
}

void desenhaInverso()
{
	for (int j = 0; j < iHeight; j++)
		for (int i = 0; i < iWidth; i++)
		{
			// printf("altura: %d | largura: %d\n", j, i);
			tPonto inicio, fim;
			inicio.x = i;
			inicio.y = j;
			fim.x = i + 1;
			fim.y = j + 1;

			desenhaQuadrante(inicio, fim, pegaCor((iWidth - i), j));
			if (j == 0)
			{
				// printf("%d\n", iHeight + iWidth * 2);
				// printf("%d\n", 0 + 0 * iWidth);
			}
		}
}

void Xadrez()
{
	tPonto p0, p1;

	p0.x = 0;
	p0.y = iHeight;

	p1.x = 100;
	p1.y = iHeight - 100;
	desenhaQuadrante(p0, p1, 64);

	// p0.x = iWidth;
	// p0.y = iHeight;
	// desenhaQuadrante(p0, p1, 222);
}

void nivel(TQuadtree **child, tPonto inicio, int h, int w, int altura_nivel)
{
	int largura = w;
	// == 1 ? w : inicio.x + w;
	int altura = h;
	//  == 1 ? h : inicio.y + h;
	int soma = 0;

	for (int i = inicio.y; i < inicio.y + h; i++)
		for (int j = inicio.x; j < inicio.x + w; j++)
		{
			soma += image[i * iWidth + j];
		}

	int media = soma / (largura * altura);
	// printf("Media: %d", largura);

	*child = new (inicio, altura, largura, media, altura_nivel);

	if (largura <= 1)
		return;
	else if (altura <= 1)
		return;

	tPonto envia_nivel = inicio;
	nivel(&(*child)->childs[0], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);

	envia_nivel.x += largura / 2;
	nivel(&(*child)->childs[1], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);

	envia_nivel.y += altura / 2;
	nivel(&(*child)->childs[2], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);

	envia_nivel.x = inicio.x;
	nivel(&(*child)->childs[3], envia_nivel, altura / 2, largura / 2, altura_nivel + 1);
}

void inNivel(TQuadtree node, int lvl);
int level = 0;
void desenhaArvore()
{
	printf("Aqui eu vou desenhar a arvore\n");
	tPonto final;
	final.x = 128 * 2;
	final.y = 128;
	tPonto inicio;
	inicio.x = 128;
	inicio.y = 0;
	// desenhaQuadrante(inicio, final, 122);
	inNivel(*root, level);
}

void inNivel(TQuadtree node, int lvl)
{
	// printf("Nó de nivel %d com valor %d\n", node.key_value->nivel, node.key_value->cor);
	if (node.key_value->nivel == lvl)
	{
		tPonto final;
		final.x = node.key_value->pBase.x + node.key_value->w;
		final.y = node.key_value->pBase.y + node.key_value->h;
		// printf("i.x: %d  i.y: %d\t", node.key_value->pBase.x, node.key_value->pBase.y);
		// printf("f.x: %d  f.y: %d\n", final.x, final.y);
		// printf("cor: %d\n", node.key_value->cor);
		desenhaQuadrante(node.key_value->pBase, final, node.key_value->cor);
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

/// ***********************************************************************
/// **
/// ***********************************************************************

void montaArvore()
{

	printf("Aqui eu vou montar a arvore\n");

	tPonto inicio;
	inicio.x = 0;
	inicio.y = 0;

	nivel(&root, inicio, iHeight, iWidth, 0);
	printf("\nmontado\n");
	// in(*root);
}

/// ***********************************************************************
/// **
/// ***********************************************************************

void teclado(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'q':
	case 'Q':
		montaArvore();
		break;
	case 'i':
	case 'I':
		desenha = !desenha;
		break;
	case '=':
		level++;
		break;
	case '-':
		level--;
		break;
	}
	glutPostRedisplay();
}

/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y)
{

	if (button_state == GLUT_DOWN)
	{
		switch (button)
		{

		case GLUT_LEFT_BUTTON:
			printf("botao esquerdo?\n");
			printf("esquerd0 | x: %d, y: %d\n", x, y);
			break;

		case GLUT_RIGHT_BUTTON:
			printf("botao direito?\n");
			break;
		}
		glutPostRedisplay();
	}
}

/// ***********************************************************************
/// **
/// ***********************************************************************

void desenho(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	if (desenha)
		desenhaArvore();
	else
		glDrawPixels(iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, image);

	glutSwapBuffers();
}

/// ***********************************************************************
/// **
/// ***********************************************************************

int main(int argc, char **argv)
{

	char *filename = "images/lena.png";

	if (argc > 1)
		filename = argv[1];

	image = leImagem(filename);

	criaJanela(argc, argv);

	initOpenGL();

	initEventos();

	return 0;
}

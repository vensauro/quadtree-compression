#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>

#include "EstruturasDeDados.h"
#include "winGL.h"
#include "arvore.h"

unsigned char *image = NULL; // image file
int iHeight,
	iWidth,
	iChannels;

bool desenha = false;

/* Minhas referencias: Ivens */
#include "quadtree.h"
TQuadtree *root = NULL;
int level = 0, max_level = 0;
bool isErro = true;

int max_erro = 100;

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaArvore()
{
	printf("Arvore desenhada");
	if (isErro)
	{
		printf("\tquantidade de erro: %f", level * 0.05);
	}
	else
	{
		printf("\tquantidade de nivel: %d", level);
	}
	printf("\n");

	inNivel(*root, level, isErro);
}

/// ***********************************************************************
/// **
/// ***********************************************************************

void montaArvore()
{
	// printf("Aqui eu vou montar a arvore\n");

	tPonto inicio;
	inicio.x = 0;
	inicio.y = 0;

	monta(&root, inicio, iHeight, iWidth, 0);

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
	case 'j':
	case 'J':
		if (isErro == true)
		{
			printf("Visualização por nivel\n");
			printf("Tente diminuir o nivel com 'k'\n");
			level = max_level;
			isErro = false;
		}
		else
		{
			printf("Visualização por erro\n");
			printf("Tente aumentar o erro com 'l'\n");
			level = 0;
			isErro = true;
		}
		break;
	case 'k':
	case 'K':
		level = level == 0 ? 0 : level - 1;

		break;
	case 'l':
	case 'L':
		if (isErro)
			level = level * 0.05 < max_erro ? level + 1 : max_erro;
		else
			level = level < max_level ? level + 1 : level;

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

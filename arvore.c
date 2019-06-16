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
int level = 0;

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaArvore()
{
	printf("Aqui eu vou desenhar a arvore\n");
	// tPonto final;
	// final.x = 128 * 2;
	// final.y = 128;
	// tPonto inicio;
	// inicio.x = 128;
	// inicio.y = 0;
	// desenhaQuadrante(inicio, final, 122);
	inNivel(*root, level);
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

	nivel(&root, inicio, iHeight, iWidth, 0, -1);

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

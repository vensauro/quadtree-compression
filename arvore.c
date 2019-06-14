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

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaArvore()
{

	printf("Aqui eu vou desenhar a arvore\n");

	// rotina que deve ser implementada para visualizacao da arvore
	// utilize a rotina desenhaQuadrante(p0, p1, cor)
	// fornecendo os pontos inicial e final do quadrante e a sua cor
	// funcao do valor do pixel ou da regiao que voce quer desenhar

	tPonto p0, p1;

	p0.x = p0.y = 0;

	p1.x = iWidth / 2;
	p1.y = iHeight / 2;
	desenhaQuadrante(p0, p1, 64);

	p0.x = iWidth;
	p0.y = iHeight;
	desenhaQuadrante(p0, p1, 222);
}

/// ***********************************************************************
/// **
/// ***********************************************************************

void montaArvore()
{

	printf("Aqui eu vou montar a arvore\n");

	// codifique aqui a sua rotina de montagem da arvore
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

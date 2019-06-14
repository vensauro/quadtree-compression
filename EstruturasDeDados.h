#ifndef __EstruturasDeDados__
#define __EstruturasDeDados__ 1

#define GRAU_ARVORE 2

typedef struct point
{
	int x;
	int y;
} tPonto;

typedef struct
{
	tPonto pBase;
	int h, w;
	int nivel;
	int cor;
	float erro;
} tQuadrante;

#endif // __EstruturasDeDados__

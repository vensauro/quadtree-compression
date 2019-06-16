.c.o:   $*.h
	gcc -c $*.c -I./external/SOIL/inc

.cpp.o:	$*.h
	g++	-c $*.cpp -I./externals/SOIL/inc

all:	arvore

arvore:  arvore.o winGL.o quadtree.o
	g++ -o $@ $^ -L./external/SOIL/lib -lglut -lGL -lGLU -lsoil

clean:
	rm *.o *.*~ *~ arvore

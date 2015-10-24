all : Bombermine

Bombermine : jeu.o niveau.o main.o
	gcc -o bombermine niveau.o main.o jeu.o `sdl-config --libs --cflags` -lSDL_ttf

jeu.o : jeu.c constantes.h niveau.h
	gcc -c jeu.c

main.o : main.cpp constantes.h
	gcc -c main.cpp

niveau.o : niveau.c constantes.h
	gcc -c niveau.c
clean :
	rm -fr *.o Bombermine

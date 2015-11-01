all : Bombermine

Bombermine :  main.o niveau.o display.o deplacement.o
	gcc -o Bombermine main.o niveau.o display.o deplacement.o `sdl-config --libs --cflags` -lSDL_ttf -g

main.o : main.c constantes.h main.h niveau.h
	gcc -c main.c

niveau.o : niveau.c
	gcc -c niveau.c

dipslay.o : display.c 
	gcc -c display.c

deplacement.o : deplacement.c constantes.h main.h
	gcc -c deplacement.c

clean :
	rm -fr *.o Bombermine

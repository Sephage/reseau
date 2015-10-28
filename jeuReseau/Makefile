all : Bombermine

Bombermine :  main.o niveau.o
	gcc -o Bombermine main.o niveau.o `sdl-config --libs --cflags` -lSDL_ttf -g

main.o : main.c constantes.h main.h niveau.h
	gcc -c main.c

niveau.o : niveau.c
	gcc -c niveau.c

clean :
	rm -fr *.o Bombermine

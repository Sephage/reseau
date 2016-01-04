all : Bombermine

Bombermine :  main.o niveau.o display.o deplacement.o client.o 
	gcc -o Bombermine main.o niveau.o display.o deplacement.o client.o `sdl-config --libs --cflags` -lSDL_ttf -g

main.o : main.c constantes.h main.h niveau.h client.h
	gcc -c main.c

niveau.o : niveau.c
	gcc -c niveau.c

dipslay.o : display.c
	gcc -c display.c

deplacement.o : deplacement.c constantes.h main.h
	gcc -c deplacement.c

client.o : client.c client.h
	gcc -c client.c

clean :
	rm -fr *.o Bombermine

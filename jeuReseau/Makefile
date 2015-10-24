all : Bombermine

Bombermine :  main.o 
	gcc -o Bombermine main.o  `sdl-config --libs --cflags` -lSDL_ttf

main.o : main.c constantes.h main.h
	gcc -c main.c

clean :
	rm -fr *.o Bombermine

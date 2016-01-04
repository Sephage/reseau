#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "player.h"

void display(int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], Character character[2]){
		system("clear");
		int i,j;
		for(i=0;i<NB_BLOCS_LARGEUR;i++){
				for(j=0;j<NB_BLOCS_HAUTEUR;j++){
						if(map[i][j] < 10)
								printf("%d  ",map[i][j]);
						else
								printf("%d ",map[i][j]);
						if(character[0]->x == i && character[0]->y == j)
								printf("X  ");
						if(character[1]->x == i && character[1]->y == j);
						printf("Y  ");
				}
				printf("\n");
		}
}

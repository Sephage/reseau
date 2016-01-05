#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "player.h"

void display(int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], Character character[2]){
		system("clear");
		int i,j;
		for(i=0;i<NB_BLOCS_LARGEUR;i++){
				for(j=0;j<NB_BLOCS_HAUTEUR;j++){
					if(character[0]->x == i && character[0]->y == j || character[1]->x == i && character[1]->y == j){
						if(character[0]->x == i && character[0]->y == j)
							printf("X  ");
						if(character[1]->x == i && character[1]->y == j)
							printf("Y  ");
					}else{
						if(map[i][j] < 10)
								printf("%d  ",map[i][j]);
						else
								printf("%d ",map[i][j]);
					}
				}
				printf("\n");
		}
		for(i = 0 ; i<2;i++){
			printf("J%d\n",i+1);
			printf("life = %d ", character[i]->life);
			printf("key = %d ", character[i]->key);
			printf("gold = %d ", character[i]->gold);
			printf("X = %d ", character[i]->x);
			printf("Y = %d \n", character[i]->y);
		}

}

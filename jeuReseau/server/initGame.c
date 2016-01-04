#include <stdio.h>
#include <stdlib.h>

#include "../constantes.h"
#include "../main.h"
/*Function which initialize the map with the good character and the good map
 * TODO :	change the file with a string
 *			I don't know if the syntax of the struc is correct
 */
void initGame(Character character[2], int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]){
	char file[200] = "map/niveau2.map";
	int i=0, j=0, k=0;


	initCarte(map, file);
	
	for(j = 0; j<NB_BLOCS_HAUTEUR;j++){
			for(i = 0;i<NB_BLOCS_LARGEUR;i++){
					if(map[i][j] == PERSONNAGE){
							if(k <= 1){
									character[k]->position->x = i;
									character[k]->position->y = j;
									map[i][j] = VIDE;
									k++;
							}
					}
			}
	}

}

#include <stdio.h>
#include <stdlib.h>

#include "../constantes.h"
#include "../main.h"
/*Function which initialize the map with the good character and the good map
 * TODO :	change the file with a string
 *			I don't know if the syntax of the struc is correct
 */
void initGame(Character charac[2], int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]){
	int i=0, j=0, k=0;

	initCarte(map, "../map/niveau2.map");
	
	for(i = 0; i<NB_BLOCS_LARGEUR;i++){
			for(j = 0;j<NB_BLOCS_HAUTEUR;j++){
					if(map[i][j] == PERSONNAGE){
							if(k <= 1){
									charac[k]->position->x = i;
									charac[k]->position->y = j;
									charac[k]->life = 10;
									charac[k]->gold = 0;
									charac[k]->key = 0;
									map[i][j] = VIDE;
									k++;
							}
					}
			}
	}

}

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


/*Function which initialize the map with the good character and the good map
 * TODO :	change the file with a string
 *			I don't know if the syntax of the struc is correct
 */
void initGame(Character character[2], int map[][]){
	string file = "map/niveau2.map";
	int i=0, j=0, k=0;
	character[0]->character[BAS] = SDL_LoadBMP("sprites/BomberFront.bmp");
	character[0]->character[HAUT] = SDL_LoadBMP("sprites/BomberBack.bmp");
	character[0]->character[DROITE] = SDL_LoadBMP("sprites/BomberRight.bmp");
	character[0]->character[GAUCHE] = SDL_LoadBMP("sprites/BomberLeft.bmp");
	character[0]->actualCharacter = character[HAUT];
	
	SDL_SetColorKey(character[0]->character[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[BAS]->format, 255, 255, 255));
	SDL_SetColorKey(character[0]->character[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[HAUT]->format, 255, 255, 255));
	SDL_SetColorKey(character[0]->character[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[DROITE]->format, 255, 255, 255));
	SDL_SetColorKey(character[0]->character[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[GAUCHE]->format, 255, 255, 255));



	/*Load different pictures here*/
	character[1]->character[BAS] = SDL_LoadBMP("sprites/BomberFront.bmp");
	character[1]->character[HAUT] = SDL_LoadBMP("sprites/BomberBack.bmp");
	character[1]->character[DROITE] = SDL_LoadBMP("sprites/BomberRight.bmp");
	character[1]->character[GAUCHE] = SDL_LoadBMP("sprites/BomberLeft.bmp");
	character[1]->actualCharacter = character[HAUT];

	SDL_SetColorKey(character[1]->character[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[BAS]->format, 255, 255, 255));
	SDL_SetColorKey(character[1]->character[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[HAUT]->format, 255, 255, 255));
	SDL_SetColorKey(character[1]->character[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[DROITE]->format, 255, 255, 255));
	SDL_SetColorKey(character[1]->character[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(character[0]->character[GAUCHE]->format, 255, 255, 255));


	initCarte(map, file);
	
	for(j = 0; j<NB_BLOCS_HAUTEUR;j++){
			for(i = 0;i<NB_BLOC_LARGEUR;i++){
					if(carte[i][j] == PERSONNAGE){
							if(k <= 1){
									character[k]->position.x = i;
									character[k]->position.y = j;
									map[i][j] = VIDE;
									k++;
							}
					}
			}
	}

}

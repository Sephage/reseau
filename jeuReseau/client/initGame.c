#include <stdio.h>
#include <stdlib.h>
#include "../joueur.h" /*Déf de la structure Character a faire*/
/*A définir les différentes lib SDL*/
/*Fonctions qui initialise les différents sprites de personnages, leur position etc...*/
void initGame(Character character[2]){
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

}

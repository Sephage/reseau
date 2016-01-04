#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "constantes.h"
#include "niveau.h"
#include "client.h"

void initGame(Character character[2]){
	character[0]->character[BAS] = SDL_LoadBMP("sprites/BomberFront.bmp");
	character[0]->character[HAUT] = SDL_LoadBMP("sprites/BomberBack.bmp");
	character[0]->character[DROITE] = SDL_LoadBMP("sprites/BomberRight.bmp");
	character[0]->character[GAUCHE] = SDL_LoadBMP("sprites/BomberLeft.bmp");
	character[0]->actualCharacter = character[0]->character[HAUT];

/*	SDL_SetColorKey(character[0]->character[BAS], SDL_SRCCOLORKEY, SDL_MapRGB((character[0]->character[BAS]->format), 255, 255, 255));
	printf("COUCOU\n");
	SDL_SetColorKey(character[0]->character[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB((character[0]->character[HAUT]->format), 255, 255, 255));
	SDL_SetColorKey(character[0]->character[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB((character[0]->character[DROITE]->format), 255, 255, 255));
	SDL_SetColorKey(character[0]->character[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB((character[0]->character[GAUCHE]->format), 255, 255, 255));
*/

	/*Load different pictures here*/
	character[1]->character[BAS] = SDL_LoadBMP("sprites/BomberFront.bmp");
	character[1]->character[HAUT] = SDL_LoadBMP("sprites/BomberBack.bmp");
	character[1]->character[DROITE] = SDL_LoadBMP("sprites/BomberRight.bmp");
	character[1]->character[GAUCHE] = SDL_LoadBMP("sprites/BomberLeft.bmp");
	character[1]->actualCharacter = character[1]->character[HAUT];
/*
	SDL_SetColorKey(character[1]->character[BAS], SDL_SRCCOLORKEY, SDL_MapRGB((character[1]->character[BAS]->format), 255, 255, 255));
	SDL_SetColorKey(character[1]->character[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB((character[1]->character[HAUT]->format), 255, 255, 255));
	SDL_SetColorKey(character[1]->character[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(character[1]->character[DROITE]->format, 255, 255, 255));
	SDL_SetColorKey(character[1]->character[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(character[1]->character[GAUCHE]->format, 255, 255, 255));
*/
}
/**Fonction main : Affichage de l'aide, appel des fonctions, initialisation des tableau **/
int main(int argc, char *argv[]){
    /* Initialisation des différentes bibliotheques SDL*
     * Ici TTF et SDL
     * */

    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *screen = NULL, *imageMenu;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;
	Character character[2];
	int i;
	for(i=0;i<2;i++){
		character[i] = malloc(sizeof(struct character));
		character[i]->position = malloc(sizeof(SDL_Rect));

		character[i]->character[0] = malloc(sizeof(SDL_Surface));
		character[i]->character[1] = malloc(sizeof(SDL_Surface));
		character[i]->character[2] = malloc(sizeof(SDL_Surface));
		character[i]->character[3] = malloc(sizeof(SDL_Surface));

		character[i]->actualCharacter = malloc(sizeof(SDL_Surface));
	}
	character[0]->life = 10;
	character[0]->gold = 0;
    SDL_WM_SetCaption("Jeu version 1.0", NULL);
    screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    positionMenu.x = 0;
    positionMenu.y = 0;

    /* L'image du menu est chargé ici, il faudra faire une aute fonction */
    imageMenu = SDL_LoadBMP("sprites/menu.bmp");
    /* La variable continuer se met a 0 lorsque :
     * Le joueur gagne
     * Le joueur perd
     * Le joueur quitte la partie
     * */

    while(continuer)
    {
        SDL_WaitEvent(&event);
        /* Ici on récupère quel est le type d'évènement */
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
                /*Ici on récupère la touche sur laquelle le joueur tape (quand il l'enfonce)*/
            case SDL_KEYDOWN:
                /*event.key... est la variable où c'est stocké*/
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_KP1:
                case SDLK_a:
                    jouer(screen, character);
                    afficher_ecran_de_fin(screen, character[0]);
                    pauseSDL();
                    //continuer = 0;
                    break;
                case SDLK_KP2:
                case SDLK_z:
                    aide(screen);
                    break;
                case SDLK_KP3:
                case SDLK_e:
                    continuer = 0;
                    break;
                default:
                    break;
            }
                break;
            default:
                break;
        }
        SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,0,0,0));
        SDL_BlitSurface(imageMenu,NULL, screen, &positionMenu);
        SDL_Flip(screen);
        }

        afficher_ecran_de_fin(screen, character[0]);

    /**Libération des police et fermeture des bibliothčque**/
    SDL_FreeSurface(imageMenu);

    SDL_Quit();
    TTF_Quit();
    /*******************************************************/
    return EXIT_SUCCESS;
}

/**********************************************************************************/
/******************************* Boucle principal : *******************************/
/*********** Initialisation de toutes les images, appel des fonctions : ***********/
/******************* de déplacement et de gestion de collisions *******************/
/**********************************************************************************/

void jouer(SDL_Surface *screen, Character character[2]){

  Client client;
  int* info = malloc(BUFF_SIZE_RECV*sizeof(int));

  int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
  int k = 0, l, m;

	SDL_Surface *monstreActuel = NULL;
    SDL_Rect positionMonstre;

    SDL_Event event;
    int continuer = 1,i,j, nbTour = 0;


  connexionToServer(&client);

  /* Mettre un message disant "Attente d'un autre joueur" */

  info = receiveFromServer(client);

  m = 0;
  while((k < 300) && (m < 20)) {
    for(l=0; l < 15; l++) {
      carte[l][m] = info[k];
      k++;
    }
    m++;
  }
  character[0]->life = info[300];
  character[0]->key = info[301];
  character[0]->gold = info[302];
  character[0]->position->x = info[303];
  character[0]->position->y = info[304];

  character[1]->life = info[305];
  character[1]->key = info[306];
  character[1]->gold = info[307];
  character[1]->position->x = info[308];
  character[1]->position->y = info[309];
  initGame(character);

	afficher_carte(carte,screen, monstreActuel, character);
    
    /*******************************************************************/

	/*CLIENT*/
    SDL_EnableKeyRepeat(100, 100);

    /*Gestion du déplacement, PdV et autres états du jeu */
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
						/* Ici la gestion des déplacements (CLIENT)
						 * personnageActuel = character.actualCharacter
						 * deplacer_personnage prend en param :
						 * Un tableau de Character
						 * (peut-être échanger avec un mineChar et EnnemyChar)
						 * ESCAPE = ECHAP UP/DOWN/RIGHT/LEFT = touche fléché*/
                    case SDLK_UP: //touche du haut
                        sendToServer(client, 0);
                        break;
                    case SDLK_DOWN: // touche du bas
                        sendToServer(client, 1);
                        break;
                    case SDLK_RIGHT: // touche de droite
                        sendToServer(client, 3);
                        break;
                    case SDLK_LEFT: //touche de gauche
                        sendToServer(client, 2);
                        break;
                    case SDLK_a: //On pose une bombe
                        sendToServer(client, 18);
                        break;
                    default:
                        break;
                }
                break;
        }

        /*Algorithme qui fait exploser les bombes tous les 5 tours*/
		/*
            for(i=0;i<NB_BLOCS_LARGEUR;i++){
                for(j=0; j<NB_BLOCS_HAUTEUR;j++){

                    if(carte[i][j] > BOMBE_EXPL && carte[i][j] <= BOMBE)
                        carte[i][j] --;
                    if(carte[i][j] == BOMBE_EXPL){
                        carte[i][j] = EXPLOSION;
                        if((carte[i][j+1] == ROCHER || carte[i][j+1] == VIDE) && j+1 < NB_BLOCS_HAUTEUR){
                            carte[i][j+1] = EXPLOSION_HAUT;
                        }
                        if((carte[i][j-1] == ROCHER || carte[i][j-1] == VIDE) && j-1 >= 0){
                            carte[i][j-1] = EXPLOSION_BAS;
                        }
                        if((carte[i+1][j] == ROCHER || carte[i+1][j] == VIDE) && i+1 < NB_BLOCS_LARGEUR){
                            carte[i+1][j] = EXPLOSION_DROITE;
                        }
                        if((carte[i-1][j] == ROCHER || carte[i-1][j] == VIDE) && i-1 >= 0){
                            carte[i-1][j] = EXPLOSION_GAUCHE;
                        }
                    }

                }
            }
		*/

      info = receiveFromServer(client);

      m = 0;
      while(k < 300) {
        for(l=0; l < 15; l++) {
          carte[l][m] = info[k];
          k++;
        }
        m++;
      }
      character[0]->life = info[300];
      character[0]->key = info[301];
      character[0]->gold = info[302];
      character[0]->position->x = info[303];
      character[0]->position->y = info[304];

      character[1]->life = info[305];
      character[1]->key = info[306];
      character[1]->gold = info[307];
      character[1]->position->x = info[308];
      character[1]->position->y = info[309];

      afficher_carte(carte,screen, monstreActuel, character);
    }

  	deconnexionFromServer(&client);
}

void deplacer_monstre(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *positionMonstre, SDL_Rect *positionJoueur, int vieClefOr[3], SDL_Surface *monstreActuel)
{
    SDL_Surface *monstre[4] = {NULL, NULL, NULL, NULL};
    int i;


    monstre[BAS] = SDL_LoadBMP("sprites/Slim_violet_face.bmp");
    monstre[HAUT] = SDL_LoadBMP("sprites/Slim_violet_dos.bmp");
    monstre[DROITE] = SDL_LoadBMP("sprites/Slim_violet_droite.bmp");
    monstre[GAUCHE] = SDL_LoadBMP("sprites/Slim_violet_gauche.bmp");

    SDL_SetColorKey(monstre[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(monstre[BAS]->format, 255, 255, 255));
    SDL_SetColorKey(monstre[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(monstre[HAUT]->format, 255, 255, 255));
    SDL_SetColorKey(monstre[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(monstre[DROITE]->format, 255, 255, 255));
    SDL_SetColorKey(monstre[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(monstre[GAUCHE]->format, 255, 255, 255));



    if(positionJoueur->x - positionMonstre->x < 0)
    {
        if(positionMonstre->x + 1 == positionJoueur->x)
        {
            vieClefOr[0]--;
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
        }
        else
        {
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
            positionMonstre->x ++;
            carte[positionMonstre->x][positionMonstre->y] = MONSTRE;
            monstreActuel = monstre[DROITE];
        }
    }
    else if(positionJoueur->x - positionMonstre->x > 0)
    {
        if(positionMonstre->x - 1 == positionJoueur->x)
        {
            vieClefOr[0]--;
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
        }
        else
        {
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
            positionMonstre->x --;
            carte[positionMonstre->x][positionMonstre->y] = MONSTRE;
            monstreActuel = monstre[GAUCHE];
        }
    }
    else if(positionJoueur->y - positionMonstre->y > 0)
    {
        if(positionMonstre->y - 1 == positionJoueur->x)
        {
            vieClefOr[0]--;
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
        }
        else
        {
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
            positionMonstre->y --;
            carte[positionMonstre->x][positionMonstre->y] = MONSTRE;
            monstreActuel = monstre[HAUT];
        }
    }
    else if(positionJoueur->y - positionMonstre->y < 0)
    {
        if(positionMonstre->y + 1 == positionJoueur->y)
        {
            vieClefOr[0]--;
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
        }
        else
        {
            carte[positionMonstre->x][positionMonstre->y] = VIDE;
            positionMonstre->y ++;
            carte[positionMonstre->x][positionMonstre->y] = MONSTRE;
            monstreActuel = monstre[BAS];
        }
    }

    for(i=0; i<4; i++)
    {
        SDL_FreeSurface(monstre[i]);
    }

}


/****************************************************************************/
/**********************Fonction qui met le jeu en pause**********************/
/************************dans la fonction ecran_de_fin***********************/
/****************************************************************************/

void pauseSDL(){
    SDL_Event event;
    int continuer = 1;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    default:
                        continuer = 0;
                        break;
                }
                break;
        default:
            break;
        }
    }
}

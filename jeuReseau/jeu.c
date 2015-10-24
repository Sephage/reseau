#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "niveau.h"
#include "main.h"

void jouer(SDL_Surface *screen, int vieClefOr[3])
{
    SDL_Surface *personnage[4] = {NULL}, *monstre[4] = {NULL};
    SDL_Surface *piege = NULL, *coffre = NULL, *personnageActuel = NULL;
    SDL_Surface *monstreActuel = NULL, *clef = NULL, *pieceOr = NULL;

    SDL_Rect positionJoueur, position;

    int i, j;
    int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {VIDE};

    clef = SDL_LoadBMP("clef.bmp");
    piege = SDL_LoadBMP("piege.bmp");
    coffre = SDL_LoadBMP("coffre.bmp");
    pieceOr = SDL_LoadBMP("or.bmp");
    personnage[BAS] = SDL_LoadBMP("Singe_face.bmp");
    personnage[HAUT] = SDL_LoadBMP("Singe_dos.bmp");
    personnage[DROITE] = SDL_LoadBMP("Singe_droite.bmp");
    personnage[GAUCHE] = SDL_LoadBMP("Singe_gauche.bmp");
    monstreActuel = SDL_LoadBMP("Slim_violet_face.bmp");

    personnageActuel = personnage[BAS];

    init_carte(carte);

    for(i=0; i<NB_BLOCS_HAUTEUR; i++)
    {
        for(j=0;j<NB_BLOCS_LARGEUR; j++)
        {
            if(carte[i][j] == PERSONNAGE)
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
            }

        }
    }

    for(i=0; i<4; i++)
    {
        SDL_FreeSurface(personnage[i]);
        SDL_FreeSurface(monstre[i]);
    }
    SDL_FreeSurface(piege);
    SDL_FreeSurface(coffre);
    SDL_FreeSurface(personnageActuel);
    SDL_FreeSurface(monstreActuel);
    SDL_FreeSurface(clef);
    SDL_FreeSurface(pieceOr);
}

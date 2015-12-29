#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"

void afficher_carte(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *positionJoueur, SDL_Surface *screen, SDL_Surface *personnageActuel, int vieClefOr[3], SDL_Surface *monstreActuel)
{
    SDL_Surface *piege = NULL, *coffre = NULL;
    SDL_Surface /**monstreActuel = NULL,*/ *clef = NULL, *pieceOr = NULL;
    SDL_Surface *rocher = NULL, *herbe = NULL;
    SDL_Surface *bombe = NULL, *explosion= NULL, *explosionHaut = NULL, *explosionBas = NULL, *explosionGauche = NULL, *explosionDroite = NULL;

    SDL_Surface *texteVie = NULL, *texteOr = NULL, *texteClef = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleurVerte = {0,250,0};

    char tabVie[15] = "";
    char tabOr[15] = "";
    char tabClef[15] = "";

    police = TTF_OpenFont("police/impact.ttf", 20);

    int i, j;

    /* Chargement des images et gestion de la transparence
     * Pour le moment aucun monstre n'est chargé, c'est pour cela qu'il et grisé, voir pour le mettre dans une
     * autre focntion
     * */
    herbe = SDL_LoadBMP("sprites/herbe.bmp");
    clef = SDL_LoadBMP("sprites/clef.bmp");
    piege = SDL_LoadBMP("sprites/piege.bmp");
    coffre = SDL_LoadBMP("sprites/coffre.bmp");
    pieceOr = SDL_LoadBMP("sprites/or.bmp");
    /*monstreActuel = SDL_LoadBMP("sprites/Slim_violet_face.bmp");*/
    rocher = SDL_LoadBMP("sprites/Ice.bmp");

    bombe = SDL_LoadBMP("sprites/Bomb.bmp");
    explosion = SDL_LoadBMP("sprites/Explosion.bmp");
    explosionBas = SDL_LoadBMP("sprites/Explosion_Haut.bmp");
    explosionHaut = SDL_LoadBMP("sprites/Explosion_Bas.bmp");
    explosionGauche = SDL_LoadBMP("sprites/Explosion_Gauche.bmp");
    explosionDroite = SDL_LoadBMP("sprites/Explosion_Droite.bmp");



    SDL_SetColorKey(clef, SDL_SRCCOLORKEY, SDL_MapRGB(clef->format, 255, 255, 255));
    SDL_SetColorKey(piege, SDL_SRCCOLORKEY, SDL_MapRGB(piege->format, 255, 255, 255));
    SDL_SetColorKey(coffre, SDL_SRCCOLORKEY, SDL_MapRGB(coffre->format, 255, 255, 255));
    /*SDL_SetColorKey(monstreActuel, SDL_SRCCOLORKEY, SDL_MapRGB(monstreActuel->format, 255, 255, 255));*/
    SDL_SetColorKey(pieceOr, SDL_SRCCOLORKEY, SDL_MapRGB(pieceOr->format, 255, 255, 255));
    SDL_SetColorKey(rocher, SDL_SRCCOLORKEY, SDL_MapRGB(rocher->format, 255, 255, 255));

    SDL_SetColorKey(bombe, SDL_SRCCOLORKEY, SDL_MapRGB(bombe->format, 255, 255, 255));
    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY, SDL_MapRGB(explosion->format, 255, 255, 255));
    SDL_SetColorKey(explosionHaut, SDL_SRCCOLORKEY, SDL_MapRGB(explosionHaut->format, 255, 255, 255));
    SDL_SetColorKey(explosionBas, SDL_SRCCOLORKEY, SDL_MapRGB(explosionBas->format, 255, 255, 255));
    SDL_SetColorKey(explosionGauche, SDL_SRCCOLORKEY, SDL_MapRGB(explosionGauche->format, 255, 255, 255));
    SDL_SetColorKey(explosionDroite, SDL_SRCCOLORKEY, SDL_MapRGB(explosionDroite->format, 255, 255, 255));




        /**Efface l'écran puis réaffiche les blocs réactualisé**/
    /** C'est cette fonction qui réactualise l'écran, il faut en faire une fonction */

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0,0,0));
        for(i=0;i<NB_BLOCS_LARGEUR; i++)
        {
            for(j=0;j<NB_BLOCS_HAUTEUR; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;
                /*Toutes les cases sont de l'herbe*/

                SDL_BlitSurface(herbe, NULL, screen, &position);
            
                /* Suivant s'il y à unobjet de jeu ou pas on l'affiche */
                switch(carte[i][j])
                {
                    case CLEF:
                        SDL_BlitSurface(clef, NULL, screen, &position);
                        break;
                    case MONSTRE:
                        SDL_BlitSurface(monstreActuel, NULL, screen, &position);
                        break;
                    case COFFRE:
                        SDL_BlitSurface(coffre, NULL, screen, &position);
                        break;
                    case PIEGE:
                        SDL_BlitSurface(piege, NULL, screen, &position);
                        break;
                    case OR:
                        SDL_BlitSurface(pieceOr, NULL, screen, &position);
                        break;
                    case ROCHER:
                        SDL_BlitSurface(rocher, NULL, screen, &position);
                        break;
                    case EXPLOSION:
                        SDL_BlitSurface(explosion, NULL, screen, &position);
                        break;
                    case EXPLOSION_HAUT:
                        SDL_BlitSurface(explosionHaut, NULL, screen, &position);
                        break;
                    case EXPLOSION_BAS:
                        SDL_BlitSurface(explosionBas, NULL, screen, &position);
                        break;
                    case EXPLOSION_GAUCHE:
                        SDL_BlitSurface(explosionGauche, NULL, screen, &position);
                        break;
                    case EXPLOSION_DROITE:
                        SDL_BlitSurface(explosionDroite, NULL, screen, &position);
                        break;
                }

                /*Remise des cases où une bombe à explosée en VIDE */
                if(carte[i][j] <= 18 && carte[i][j] > 8){
                    SDL_BlitSurface(bombe,NULL,screen, &position);
                }
                    /*Si la bombe à déjà explosée*/
                    if(carte[i][j] >= 19){
                        carte[i][j] = VIDE;
                    }
            }
        }
                /** Gestion du texte de vie, clef et or du joueur **/

        sprintf(tabVie,"Vie : %d", vieClefOr[0]);
        texteVie = TTF_RenderText_Solid(police, tabVie, couleurVerte);
        sprintf(tabClef,"Clef : %d", vieClefOr[1]);
        texteClef = TTF_RenderText_Solid(police, tabClef, couleurVerte);
        sprintf(tabOr, "Or : %d", vieClefOr[2]);
        texteOr = TTF_RenderText_Solid(police, tabOr, couleurVerte);

        position.x = NB_BLOCS_LARGEUR * TAILLE_BLOC;
        position.y = 0;
        SDL_BlitSurface(texteVie, NULL, screen, &position);
        position.y = 40;
        SDL_BlitSurface(texteClef, NULL, screen, &position);
        position.y = 80;
        SDL_BlitSurface(texteOr, NULL, screen, &position);

    position.x = positionJoueur->x * TAILLE_BLOC;
    position.y = positionJoueur->y * TAILLE_BLOC;
    SDL_BlitSurface(personnageActuel, NULL, screen, &position);
    SDL_Flip(screen);

    /**Libération des surfaces**/
    SDL_FreeSurface(piege);
    SDL_FreeSurface(coffre);
    SDL_FreeSurface(monstreActuel);
    SDL_FreeSurface(clef);
    SDL_FreeSurface(pieceOr);
    SDL_FreeSurface(rocher);
    SDL_FreeSurface(texteVie);
    SDL_FreeSurface(texteClef);
    SDL_FreeSurface(texteOr);
    SDL_FreeSurface(herbe);
    SDL_FreeSurface(bombe);

    SDL_FreeSurface(explosion);
    SDL_FreeSurface(explosionHaut);
    SDL_FreeSurface(explosionBas);
    SDL_FreeSurface(explosionGauche);
    SDL_FreeSurface(explosionDroite);



    TTF_CloseFont(police);
}



void afficher_monstre(SDL_Rect *positionMonstre, SDL_Surface *screen, SDL_Surface *monstreActuel)
{
    SDL_Rect position;

    position.x = positionMonstre->x * TAILLE_BLOC;
    position.y = positionMonstre->y * TAILLE_BLOC;

    SDL_BlitSurface(monstreActuel, NULL, screen, &position);
    SDL_Flip(screen);
}

/*****************************************************************************/
/******************* Affiche l'écran de fin suivant les cas ******************/
/*****************************************************************************/

void afficher_ecran_de_fin(SDL_Surface *screen, int vieClefOr[3])
{
    SDL_Surface *texte;
    TTF_Font *police;
    SDL_Color couleurVerte = {0,200,0};
    SDL_Color couleurNoire = {0,0,0};
    SDL_Rect position;

    police = TTF_OpenFont("police/pala.ttf", 65);  //Chargement de la police

    position.y = 375-35;


    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0,0,0));

    if(vieClefOr[0] ==  0)  //SI la vie descend a 0
    {
        texte = TTF_RenderText_Shaded(police,"Vous avez perdu !!", couleurVerte, couleurNoire);
        position.x = 280;

    }
    else if(vieClefOr[2] >= 10) //Si le joueur à plus de 10 pičces d'or
    {
        texte = TTF_RenderText_Shaded(police, "Vous avez gagne !!", couleurVerte, couleurNoire);
        position.x = 270;
    }
    else    //Si le joueur décide de quitter avant la fin
    {
        texte = TTF_RenderText_Shaded(police,"Au revoir !!", couleurVerte, couleurNoire);
        position.x = 365;
    }
        SDL_BlitSurface(texte, NULL, screen, &position);
        SDL_Flip(screen);
        pause();
        /**Libération des pointeurs**/
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
}

/**************************************************************/
/***************** Afficher la fenętre d'aide *****************/
/**************************************************************/
void aide(SDL_Surface *screen)
{
    SDL_Surface *aide = NULL;
    SDL_Rect position;

    aide = SDL_LoadBMP("sprites/aide.bmp");

    position.x = 0;
    position.y = 0;

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0,0,0));

    SDL_BlitSurface(aide, NULL, screen, &position);
    SDL_Flip(screen);
    pause();

    SDL_FreeSurface(aide);
}

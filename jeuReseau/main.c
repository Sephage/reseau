#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "constantes.h"


/**Fonction main : Affichage de l'aide, appel des fonctions, initialisation des tableau **/
int main(int argc, char *argv[])
{
    /* Initialisation des différentes bibliothčques SDL*
     * Ici TTF et SDL
     * */

    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *screen = NULL, *imageMenu;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;
    int vieClefOr[3] = {10,0,0};

    SDL_WM_SetCaption("Jeu version 1.0", NULL);
    screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    positionMenu.x = 0;
    positionMenu.y = 0;

    /* L'image du menu est chargé ici, il faudra faire une aute fonction */
    imageMenu = SDL_LoadBMP("sprites/menu_deux.bmp");
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
                    jouer(screen, vieClefOr);
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

        afficher_ecran_de_fin(screen, vieClefOr);

    /**Libération des police et fermeture des bibliothčque**/
    SDL_FreeSurface(imageMenu);

    SDL_Quit();
    TTF_Quit();
    /*******************************************************/
    return EXIT_SUCCESS;
}


/*********************************************************/
/******** Initialisation des cases de la carte ***********/
/***** Ici il faudra mettre tout ça dans un dossier ******/
/*En même temps il faudra le mettre dans un autre fichier*/
/******** où il y aura des fonctions sur la carte ********/
/*********************************************************/

void init_carte(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR])
{
        int i, j;

        for (i = 0; i < NB_BLOCS_LARGEUR; i++)
        {
            for(j = 0; j < NB_BLOCS_HAUTEUR; j++)
            {
                carte[i][j] = VIDE;
            }
        }

/********** Initialisation des cases autres que VIDE ***********/
        /* Les cases où Monstres apparaissent sont pour le moment inutilisée, aucun monstre n'est programmé, mais le sprite existe */

        carte[0][0] = PERSONNAGE;
        carte[13][0] = MONSTRE;
        carte[15][0] = OR;
        carte[19][0] = MONSTRE;
        carte[12][1] = CLEF;
        carte[19][2] = COFFRE;
        carte[0][3] = CLEF;
        carte[4][3] = CLEF;
        carte[15][10] = CLEF;
        carte[4][5] = OR;
        carte[12][5] = OR;
        carte[7][7] = ROCHER;
        carte[8][7] = ROCHER;
        carte[9][7] = ROCHER;
        carte[6][8] = PIEGE;
        carte[7][8] = MONSTRE;
        carte[8][8] = COFFRE;
        carte[9][8] = ROCHER;
        carte[16][8] = MONSTRE;
        carte[18][8] = MONSTRE;
        carte[7][9] = ROCHER;
        carte[8][9] = ROCHER;
        carte[9][9] = ROCHER;
        carte[18][9] = OR;
        carte[19][9] = OR;
        carte[16][10] = ROCHER;
        carte[18][10] = ROCHER;
        carte[19][10] = ROCHER;
        carte[19][11] = COFFRE;
        carte[15][12] = ROCHER;
        carte[16][12] = ROCHER;
        carte[17][12] = ROCHER;
        carte[18][12] = ROCHER;
        carte[19][12] = ROCHER;
        carte[1][13] = PIEGE;
        carte[2][13] = PIEGE;
        carte[3][13] = PIEGE;
        carte[4][13] = PIEGE;
        carte[18][13] = MONSTRE;
        carte[19][13] = PIEGE;
        carte[0][14] = MONSTRE;
        carte[1][14] = ROCHER;
        carte[2][14] = COFFRE;
        carte[3][14] = COFFRE;
        carte[4][14] = ROCHER;
        carte[5][14] = MONSTRE;
        carte[9][14] = OR;
        carte[12][14] = MONSTRE;
        carte[18][14] = PIEGE;
        carte[19][14] = CLEF;
        /**********************/

}



void afficher_carte(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *positionJoueur, SDL_Surface *screen, SDL_Surface *personnageActuel, int vieClefOr[3], SDL_Surface *monstreActuel)
{
    SDL_Surface *piege = NULL, *coffre = NULL;
    SDL_Surface /**monstreActuel = NULL,*/ *clef = NULL, *pieceOr = NULL;
    SDL_Surface *rocher = NULL, *herbe = NULL;

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
    rocher = SDL_LoadBMP("sprites/rocher.bmp");


    SDL_SetColorKey(clef, SDL_SRCCOLORKEY, SDL_MapRGB(clef->format, 255, 255, 255));
    SDL_SetColorKey(piege, SDL_SRCCOLORKEY, SDL_MapRGB(piege->format, 255, 255, 255));
    SDL_SetColorKey(coffre, SDL_SRCCOLORKEY, SDL_MapRGB(coffre->format, 255, 255, 255));
    /*SDL_SetColorKey(monstreActuel, SDL_SRCCOLORKEY, SDL_MapRGB(monstreActuel->format, 255, 255, 255));*/
    SDL_SetColorKey(pieceOr, SDL_SRCCOLORKEY, SDL_MapRGB(pieceOr->format, 255, 255, 255));
    SDL_SetColorKey(rocher, SDL_SRCCOLORKEY, SDL_MapRGB(rocher->format, 255, 255, 255));




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

        position.x = 1000;
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




/**********************************************************************************/
/******************************* Boucle principal : *******************************/
/*********** Initialisation de toutes les images, appel des fonctions : ***********/
/******************* de déplacement et de gestion de collisions *******************/
/**********************************************************************************/

void jouer(SDL_Surface *screen, int vieClefOr[3])
{

    SDL_Surface *personnage[4] = {NULL, NULL, NULL, NULL};
    SDL_Surface *personnageActuel = NULL;
    SDL_Surface *monstreActuel = NULL;
    SDL_Rect positionJoueur, positionMonstre;

    SDL_Event event;
    int continuer = 1,i,j;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR];


    personnage[BAS] = SDL_LoadBMP("sprites/Singe_face.bmp");
    personnage[HAUT] = SDL_LoadBMP("sprites/Singe_dos.bmp");
    personnage[DROITE] = SDL_LoadBMP("sprites/Singe_droite.bmp");
    personnage[GAUCHE] = SDL_LoadBMP("sprites/Singe_gauche.bmp");


    SDL_SetColorKey(personnage[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(personnage[BAS]->format, 255, 255, 255));
    SDL_SetColorKey(personnage[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(personnage[HAUT]->format, 255, 255, 255));
    SDL_SetColorKey(personnage[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(personnage[DROITE]->format, 255, 255, 255));
    SDL_SetColorKey(personnage[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(personnage[GAUCHE]->format, 255, 255, 255));


    /*******************************************************************/

    personnageActuel = personnage[BAS]; //Personnage de départ et celui de face

    init_carte(carte);

    /**Initialisation de la position du joueur pour la premičre fois**/

    for(i=0; i<NB_BLOCS_LARGEUR; i++)
    {
        for(j=0;j<NB_BLOCS_HAUTEUR; j++)
        {
            if(carte[i][j] == PERSONNAGE)
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    SDL_EnableKeyRepeat(100, 100);

    /*Gestion du déplacement, PdV et autres états du jeu */
    while(continuer && vieClefOr[0] != 0 && vieClefOr[2] < 10)
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
                   case SDLK_UP: //touche du haut
                        personnageActuel = personnage[HAUT];
                        deplacer_personnage(carte, &positionJoueur, HAUT, vieClefOr);
                        break;
                    case SDLK_DOWN: // touche du bas
                        personnageActuel = personnage[BAS];
                        deplacer_personnage(carte, &positionJoueur, BAS, vieClefOr);
                        break;
                    case SDLK_RIGHT: // touche de droite
                        personnageActuel = personnage[DROITE];
                        deplacer_personnage(carte, &positionJoueur, DROITE, vieClefOr);
                        break;
                    case SDLK_LEFT: //touche de gauche
                        personnageActuel = personnage[GAUCHE];
                        deplacer_personnage(carte, &positionJoueur, GAUCHE, vieClefOr);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        /**********************************************************/

/*
        for(i=0;i<NB_BLOCS_LARGEUR; i++)
        {
            for(j=0; j<NB_BLOCS_HAUTEUR; j++)
            {
                if(carte[i][j] == MONSTRE)
                   {
                        positionMonstre.x = i;
                        positionMonstre.y = j;

                        deplacer_monstre(carte, &positionMonstre, &positionJoueur, vieClefOr, monstreActuel);
                        //afficher_monstre(carte, &positionMonstre, screen, monstreActuel);
                   }
            }
        }
        */
        afficher_carte(carte,&positionJoueur ,screen, personnageActuel, vieClefOr, monstreActuel);
        /**********************************************************/


    }


    SDL_FreeSurface(personnageActuel);
    SDL_FreeSurface(monstreActuel);

    for(i=0; i<4; i++)
    {
        SDL_FreeSurface(personnage[i]);
    }

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


/**********************************************************************/
/********** Boucle de déplacement de personnage, change la ************/
/************ positionJoueur, et gestion des collisions ***************/
/**********************************************************************/

void deplacer_personnage(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *position, int direction, int vieClefOr[3])
{
    switch(direction) /**y-1*/
    {
      /**/case HAUT:
            if(position->y - 1 < 0)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[position->x][position->y-1] == VIDE)
                {
                    position->y--;
                }
                else
                {
                    if(carte[position->x][position->y-1] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[position->x][position->y-1] == CLEF)
                    {
                        vieClefOr[1] = vieClefOr[1] + 1;
                        carte[position->x][position->y-1] = VIDE;
                        position->y--;
                    }
                    else if(carte[position->x][position->y-1] == OR)
                    {
                        vieClefOr[2] = vieClefOr[2] + 1;
                        carte[position->x][position->y-1] = VIDE;
                        position->y--;
                    }

                    else if(carte[position->x][position->y-1] == PIEGE || carte[position->x][position->y-1] == MONSTRE)
                    {
                        vieClefOr[0] = vieClefOr[0] - 1;
                        carte[position->x][position->y-1] = VIDE;
                        position->y--;
                    }

                    else if(carte[position->x][position->y - 1] == COFFRE)
                    {
                        if(vieClefOr[1] > 0)
                        {
                            vieClefOr[1] = vieClefOr[1] - 1;
                            vieClefOr[2] = vieClefOr[2] + 2;
                            carte[position->x][position->y-1] = VIDE;
                            position->y--;
                        }

                        else
                        {
                            /**On arręte si on n'a pas de clef pour ouvrir le coffre**/
                        }
                    }
                }
            }

        /**/break;

        case BAS: /**y+1**/
            if(position->y + 1 > NB_BLOCS_HAUTEUR-1)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[position->x][position->y+1] == VIDE)
                {
                    position->y++;
                }
                else
                {
                   if(carte[position->x][position->y+1] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[position->x][position->y+1] == CLEF)
                    {
                        vieClefOr[1] = vieClefOr[1] + 1;
                        carte[position->x][position->y+1] = VIDE;
                        position->y++;
                    }
                    else if(carte[position->x][position->y+1] == OR)
                    {
                        vieClefOr[2] = vieClefOr[2] + 1;
                        carte[position->x][position->y+1] = VIDE;
                        position->y++;
                    }
                    else if(carte[position->x][position->y+1] == PIEGE || carte[position->x][position->y+1] == MONSTRE)
                    {
                        vieClefOr[0] = vieClefOr[0] - 1;
                        carte[position->x][position->y+1] = VIDE;
                        position->y++;
                    }
                    else if(carte[position->x][position->y + 1] == COFFRE)
                    {
                        if(vieClefOr[1] > 0)
                        {
                            vieClefOr[1] = vieClefOr[1] - 1;
                            vieClefOr[2] = vieClefOr[2] + 2;
                            carte[position->x][position->y+1] = VIDE;
                            position->y++;
                        }
                        else
                        {
                            /**On arręte si on n'a pas de clef pour ouvrir le coffre**/
                        }
                    }
                }

            }
            break;

        case DROITE:/**x+1**/
            if(position->x+1 > NB_BLOCS_LARGEUR-1)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[position->x+1][position->y] == VIDE)
                {
                    position->x++;
                }
                else
                {
                    if(carte[position->x+1][position->y] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[position->x+1][position->y] == CLEF)
                    {
                        vieClefOr[1] = vieClefOr[1] + 1;
                        carte[position->x+1][position->y] = VIDE;
                        position->x++;
                    }
                    else if(carte[position->x+1][position->y] == OR)
                    {
                        vieClefOr[2] = vieClefOr[2] + 1;
                        carte[position->x+1][position->y] = VIDE;
                        position->x++;
                    }

                    else if(carte[position->x+1][position->y] == PIEGE || carte[position->x+1][position->y] == MONSTRE)
                    {
                        vieClefOr[0] = vieClefOr[0] - 1;
                        carte[position->x+1][position->y] = VIDE;
                        position->x++;
                    }

                    else if(carte[position->x+1][position->y] == COFFRE)
                    {
                        if(vieClefOr[1] > 0)
                        {
                            vieClefOr[1] = vieClefOr[1] - 1;
                            vieClefOr[2] = vieClefOr[2] + 2;
                            carte[position->x+1][position->y] = VIDE;
                            position->x++;
                    }

                        else
                        {
                            /**On arręte si on n'a pas de clef pour ouvrir le coffre**/
                        }
                    }
                }
            }

            break;

        case GAUCHE:/**x-1**/
            if(position->x - 1 < 0)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[position->x-1][position->y] == VIDE)
                {
                    position->x--;
                }
                else
                {
                    if(carte[position->x-1][position->y] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[position->x-1][position->y] == CLEF)
                    {
                        vieClefOr[1] = vieClefOr[1] + 1;
                        carte[position->x-1][position->y] = VIDE;
                        position->x--;
                    }
                    else if(carte[position->x-1][position->y] == OR)
                    {
                        vieClefOr[2] = vieClefOr[2] + 1;
                        carte[position->x-1][position->y] = VIDE;
                        position->x--;
                    }

                    else if(carte[position->x-1][position->y] == PIEGE || carte[position->x-1][position->y] == MONSTRE)
                    {
                        vieClefOr[0] = vieClefOr[0] - 1;
                        carte[position->x-1][position->y] = VIDE;
                        position->x--;
                    }

                    else if(carte[position->x-1][position->y] == COFFRE)
                    {
                        if(vieClefOr[1] > 0)
                        {
                            vieClefOr[1] = vieClefOr[1] - 1;
                            vieClefOr[2] = vieClefOr[2] + 2;
                            carte[position->x-1][position->y] = VIDE;
                            position->x--;
                        }

                        else
                        {
                            /**On arręte si on n'a pas de clef pour ouvrir le coffre**/
                        }
                    }
                }
            }

            break;
    }

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
    else if(vieClefOr[2] >= 10) //Si le joueur ŕ plus de 10 pičces d'or
    {
        texte = TTF_RenderText_Shaded(police, "Vous avez gagné !!", couleurVerte, couleurNoire);
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





/****************************************************************************/
/**********************Fonction qui met le jeu en pause**********************/
/************************dans la fonction ecran_de_fin***********************/
/****************************************************************************/

void pause()
{
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


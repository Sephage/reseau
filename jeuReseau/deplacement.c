#include <stdio.h>
#include <SDL/SDL.h>

#include "main.h"
#include "constantes.h"
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
        break;

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
        /*case RESTER:
            if(carte[position->x][position->y] > 8){
                vieClefOr[0]--;
            }
            break;*/
    }

}

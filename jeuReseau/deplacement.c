#include <stdio.h>
#include <SDL/SDL.h>

#include "main.h"
#include "constantes.h"
/**********************************************************************/
/********** Boucle de déplacement de personnage, change la ************/
/************ personnage->positionJoueur, et gestion des collisions ***************/
/**********************************************************************/

void deplacer_personnage(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int direction, Character *personnage){
    switch(direction) /**y-1*/
    {
      /**/case HAUT:
            if(personnage->personnage->position.y - 1 < 0)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[personnage->position->x][personnage->position->y-1] == VIDE)
                {
                    personnage->position->y--;
                }
                else
                {
                    if(carte[personnage->position->x][personnage->position->y-1] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[personnage->position->x][personnage->position->y-1] == CLEF)
                    {
                        personnage->key = personnage->key + 1;
                        carte[personnage->position->x][personnage->position->y-1] = VIDE;
                        personnage->position->y--;
                    }
                    else if(carte[personnage->position->x][personnage->position->y-1] == OR)
                    {
                        personnage->gold = personnage->gold + 1;
                        carte[personnage->position->x][personnage->position->y-1] = VIDE;
                        personnage->position->y--;
                    }

                    else if(carte[personnage->position->x][personnage->position->y-1] == PIEGE || carte[personnage->position->x][personnage->position->y-1] == MONSTRE)
                    {
                        personnage->life = personnage->life - 1;
                        carte[personnage->position->x][personnage->position->y-1] = VIDE;
                        personnage->position->y--;
                    }

                    else if(carte[personnage->position->x][personnage->position->y - 1] == COFFRE)
                    {
                        if(personnage->key > 0)
                        {
                            personnage->key = personnage->key - 1;
                            personnage->gold = personnage->gold + 2;
                            carte[personnage->position->x][personnage->position->y-1] = VIDE;
                            personnage->position->y--;
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
            if(personnage->position->y + 1 > NB_BLOCS_HAUTEUR-1)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[personnage->position->x][personnage->position->y+1] == VIDE)
                {
                    personnage->position->y++;
                }
                else
                {
                   if(carte[personnage->position->x][personnage->position->y+1] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[personnage->position->x][personnage->position->y+1] == CLEF)
                    {
                        personnage->key = personnage->key + 1;
                        carte[personnage->position->x][personnage->position->y+1] = VIDE;
                        personnage->position->y++;
                    }
                    else if(carte[personnage->position->x][personnage->position->y+1] == OR)
                    {
                        personnage->gold =  personnage->gold + 1;
                        carte[personnage->position->x][personnage->position->y+1] = VIDE;
                        personnage->position->y++;
                    }
                    else if(carte[personnage->position->x][personnage->position->y+1] == PIEGE || carte[personnage->position->x][personnage->position->y+1] == MONSTRE)
                    {
                        personnage->life = personnage->life - 1;
                        carte[personnage->position->x][personnage->position->y+1] = VIDE;
                        personnage->position->y++;
                    }
                    else if(carte[personnage->position->x][personnage->position->y + 1] == COFFRE)
                    {
                        if(personnage->key > 0)
                        {
                            personnage->key = personnage->key - 1;
                            personnage->gold = personnage->gold + 2;
                            carte[personnage->position->x][personnage->position->y+1] = VIDE;
                            personnage->position->y++;
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
            if(personnage->position->x+1 > NB_BLOCS_LARGEUR-1)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[personnage->position->x+1][personnage->position->y] == VIDE)
                {
                    personnage->position->x++;
                }
                else
                {
                    if(carte[personnage->position->x+1][personnage->position->y] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[personnage->position->x+1][personnage->position->y] == CLEF)
                    {
                        personnage->key++;
                        carte[personnage->position->x+1][personnage->position->y] = VIDE;
                        personnage->position->x++;
                    }
                    else if(carte[personnage->position->x+1][personnage->position->y] == OR)
                    {
                        personnage->gold++;
                        carte[personnage->position->x+1][personnage->position->y] = VIDE;
                        personnage->position->x++;
                    }

                    else if(carte[personnage->position->x+1][personnage->position->y] == PIEGE || carte[personnage->position->x+1][personnage->position->y] == MONSTRE)
                    {
                        personnage->life--;
                        carte[personnage->position->x+1][personnage->position->y] = VIDE;
                        personnage->position->x++;
                    }

                    else if(carte[personnage->position->x+1][personnage->position->y] == COFFRE)
                    {
                        if(personnage->key > 0)
                        {
                            personnage->key--;
                            personnage->key++;
                            carte[personnage->position->x+1][personnage->position->y] = VIDE;
                            personnage->position->x++;
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
            if(personnage->position->x - 1 < 0)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(carte[personnage->position->x-1][personnage->position->y] == VIDE)
                {
                    personnage->position->x--;
                }
                else
                {
                    if(carte[personnage->position->x-1][personnage->position->y] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(carte[personnage->position->x-1][personnage->position->y] == CLEF)
                    {
                        personnage->key++;
                        carte[personnage->position->x-1][personnage->position->y] = VIDE;
                        personnage->position->x--;
                    }
                    else if(carte[personnage->position->x-1][personnage->position->y] == OR)
                    {
                        personnage->gold++;
                        carte[personnage->position->x-1][personnage->position->y] = VIDE;
                        personnage->position->x--;
                    }

                    else if(carte[personnage->position->x-1][personnage->position->y] == PIEGE || carte[personnage->position->x-1][personnage->position->y] == MONSTRE)
                    {
                        personnage->life--;
                        carte[personnage->position->x-1][personnage->position->y] = VIDE;
                        personnage->position->x--;
                    }

                    else if(carte[personnage->position->x-1][personnage->position->y] == COFFRE)
                    {
                        if(personnage->key > 0)
                        {
                            personnage->key--;
							personnage->gold++;
                            carte[personnage->position->x-1][personnage->position->y] = VIDE;
                            personnage->position->x--;
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
            if(carte[personnage->position->x][personnage->position->y] > 8){
                vieClefOr[0]--;
            }
            break;*/
    }

}

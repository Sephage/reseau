#include <stdio.h>

#include "../constantes.h"
#include "../player.h"

/**********************************************************************/
/********** Boucle de déplacement de character, change la ************/
/************ characterJoueur, et gestion des collisions ***************/
/**********************************************************************/

void move_character(int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int direction, Character character){
    switch(direction) /**y-1*/
    {
      /**/case HAUT:
            if(character->y - 1 < 0)
            {
                /**On arrete ici si la case suivante sort du tableau**/
            }
            else
            {
                if(map[character->x][character->y-1] == VIDE)
                {
                    character->y--;
                }
                else
                {
                    if(map[character->x][character->y-1] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(map[character->x][character->y-1] == CLEF)
                    {
                        character->key = character->key + 1;
                        map[character->x][character->y-1] = VIDE;
                        character->y--;
                    }
                    else if(map[character->x][character->y-1] == OR)
                    {
                        character->gold = character->gold + 1;
                        map[character->x][character->y-1] = VIDE;
                        character->y--;
                    }

                    else if(map[character->x][character->y-1] == PIEGE || map[character->x][character->y-1] == MONSTRE)
                    {
                        character->life = character->life - 1;
                        map[character->x][character->y-1] = VIDE;
                        character->y--;
                    }

                    else if(map[character->x][character->y - 1] == COFFRE)
                    {
                        if(character->key > 0)
                        {
                            character->key = character->key - 1;
                            character->gold = character->gold + 2;
                            map[character->x][character->y-1] = VIDE;
                            character->y--;
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
            if(character->y + 1 > NB_BLOCS_HAUTEUR-1)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(map[character->x][character->y+1] == VIDE)
                {
                    character->y++;
                }
                else
                {
                   if(map[character->x][character->y+1] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(map[character->x][character->y+1] == CLEF)
                    {
                        character->key = character->key + 1;
                        map[character->x][character->y+1] = VIDE;
                        character->y++;
                    }
                    else if(map[character->x][character->y+1] == OR)
                    {
                        character->gold =  character->gold + 1;
                        map[character->x][character->y+1] = VIDE;
                        character->y++;
                    }
                    else if(map[character->x][character->y+1] == PIEGE || map[character->x][character->y+1] == MONSTRE)
                    {
                        character->life = character->life - 1;
                        map[character->x][character->y+1] = VIDE;
                        character->y++;
                    }
                    else if(map[character->x][character->y + 1] == COFFRE)
                    {
                        if(character->key > 0)
                        {
                            character->key = character->key - 1;
                            character->gold = character->gold + 2;
                            map[character->x][character->y+1] = VIDE;
                            character->y++;
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
            if(character->x+1 > NB_BLOCS_LARGEUR-1)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(map[character->x+1][character->y] == VIDE)
                {
                    character->x++;
                }
                else
                {
                    if(map[character->x+1][character->y] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(map[character->x+1][character->y] == CLEF)
                    {
                        character->key++;
                        map[character->x+1][character->y] = VIDE;
                        character->x++;
                    }
                    else if(map[character->x+1][character->y] == OR)
                    {
                        character->gold++;
                        map[character->x+1][character->y] = VIDE;
                        character->x++;
                    }

                    else if(map[character->x+1][character->y] == PIEGE || map[character->x+1][character->y] == MONSTRE)
                    {
                        character->life--;
                        map[character->x+1][character->y] = VIDE;
                        character->x++;
                    }

                    else if(map[character->x+1][character->y] == COFFRE)
                    {
                        if(character->key > 0)
                        {
                            character->key--;
                            character->key++;
                            map[character->x+1][character->y] = VIDE;
                            character->x++;
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
            if(character->x - 1 < 0)
            {
                /**On arręte ici si la case suivante sort du tableau**/
            }
            else
            {
                if(map[character->x-1][character->y] == VIDE)
                {
                    character->x--;
                }
                else
                {
                    if(map[character->x-1][character->y] == ROCHER)
                    {
                        /**Arręt si la case suivante est un rocher**/
                    }
                    else if(map[character->x-1][character->y] == CLEF)
                    {
                        character->key++;
                        map[character->x-1][character->y] = VIDE;
                        character->x--;
                    }
                    else if(map[character->x-1][character->y] == OR)
                    {
                        character->gold++;
                        map[character->x-1][character->y] = VIDE;
                        character->x--;
                    }

                    else if(map[character->x-1][character->y] == PIEGE || map[character->x-1][character->y] == MONSTRE)
                    {
                        character->life--;
                        map[character->x-1][character->y] = VIDE;
                        character->x--;
                    }

                    else if(map[character->x-1][character->y] == COFFRE)
                    {
                        if(character->key > 0)
                        {
                            character->key--;
							character->gold++;
                            map[character->x-1][character->y] = VIDE;
                            character->x--;
                        }

                        else
                        {
                            /**On arrete si on n'a pas de clef pour ouvrir le coffre**/
                        }
                    }
                }
            }

            break;
		case BOMBE:
			map[character->x][character->y] = BOMBE;
			break;
        /*case RESTER:
            if(map[character->x][character->y] > 8){
                vieClefOr[0]--;
            }
            break;*/
    }

}

#include "constantes.h"


void init_carte(int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR])
{
        int i, j;

        for (i = 0; i < NB_BLOCS_HAUTEUR; i++)
        {
            for(j = 0; j < NB_BLOCS_LARGEUR; j++)
            {
                carte[i][j] = VIDE;
            }
        }

        carte[0][0] = PERSONNAGE;
        carte[0][13] = MONSTRE;
        carte[0][15] = OR;
        carte[0][19] = MONSTRE;
        carte[2][19] = COFFRE;
        carte[5][4] = OR;
        carte[5][12] = OR;
        carte[7][7] = ROCHER;
        carte[7][8] = ROCHER;
        carte[7][9] = ROCHER;
        carte[8][6] = PIEGE;
        carte[8][7] = ROCHER;
        carte[8][8] = ROCHER;
        carte[8][9] = ROCHER;
        carte[8][16] = MONSTRE;
        carte[8][18] = MONSTRE;
        carte[9][7] = ROCHER;
        carte[9][8] = ROCHER;
        carte[9][9] = ROCHER;
        carte[9][18] = OR;
        carte[9][19] = OR;
        carte[10][16] = ROCHER;
        carte[10][18] = ROCHER;
        carte[10][19] = ROCHER;
        carte[11][19] = COFFRE;
        carte[12][15] = ROCHER;
        carte[12][16] = ROCHER;
        carte[12][17] = ROCHER;
        carte[12][18] = ROCHER;
        carte[12][19] = ROCHER;
        carte[13][1] = PIEGE;
        carte[13][2] = PIEGE;
        carte[13][3] = PIEGE;
        carte[13][18] = MONSTRE;
        carte[13][19] = PIEGE;
        carte[14][0] = MONSTRE;
        carte[14][1] = ROCHER;
        carte[14][2] = COFFRE;
        carte[14][3] = COFFRE;
        carte[14][4] = ROCHER;
        carte[14][5] = MONSTRE;
        carte[14][9] = OR;
        carte[14][12] = MONSTRE;
        carte[14][18] = PIEGE;
        carte[14][19] = OR;

}

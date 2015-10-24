/******************************************************************************************************/
/**                                    Jeu :                                                         **/
/**                            - Par Paul VALENTIN et bientôt reprise pas 4 autres personnes :D      **/
/**                            - Version : Alpha 1.0                                                 **/
/**                            - sans IA                                                             **/
/**                            - Modif : 21/12/2013                                                  **/
/******************************************************************************************************/


#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define NB_BLOCS_HAUTEUR    15
#define NB_BLOCS_LARGEUR    20
#define TAILLE_BLOC         50
#define HAUTEUR             (TAILLE_BLOC * NB_BLOCS_HAUTEUR)
#define LARGEUR             (TAILLE_BLOC * NB_BLOCS_LARGEUR) + 60

enum{SINGE_FACE = 0,SINGE_DOS = 1,SINGE_DROITE = 2,SINGE_GAUCHE = 3};
enum{MONSTRE_FACE = 0, MONSTRE_DOS = 1, MONSTRE_DROITE = 2, MONSTRE_GAUCHE = 3};
enum{VIDE = 0,ROCHER = 1,CLEF = 2,OR = 3,COFFRE = 4,MONSTRE = 5, PIEGE = 6, PERSONNAGE = 7};
enum{BAS = 0,HAUT = 1,GAUCHE = 2,DROITE = 3};


#endif // CONSTANTES_H_INCLUDED

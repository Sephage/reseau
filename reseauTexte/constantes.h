/******************************************************************************************************/
/**                                    Jeu :                                                         **/
/**                            - Par Paul VALENTIN      **/
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
enum{VIDE = 0,ROCHER = 1,CLEF = 2,OR = 3,COFFRE = 4,MONSTRE = 5, PIEGE = 6, PERSONNAGE = 7, BOMBE_EXPL = 8, BOMBE = 18, EXPLOSION=19, EXPLOSION_DROITE = 20, EXPLOSION_GAUCHE = 21,EXPLOSION_HAUT = 22, EXPLOSION_BAS = 23};
enum{HAUT = 0,BAS=1,GAUCHE=2,DROITE=3, EXIT=5};


#endif // CONSTANTES_H_INCLUDED

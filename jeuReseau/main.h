#include "constantes.h"

void pause();
void aide(SDL_Surface *screen);
void jouer(SDL_Surface *screen, int vieClefOr[3]);
void init_carte(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]);
void deplacer_personnage(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *position, int direction, int vieClefOr[3]);
void deplacer_monstre(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *positionMonstre,SDL_Rect *positionJoueur, int vieClefOr[3], SDL_Surface *monstreActuel);
void afficher_ecran_de_fin(SDL_Surface *screen, int vieClefOr[3]);
void afficher_carte(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect *positionJoueur, SDL_Surface *screen, SDL_Surface *personnageActuel, int vieClefOr[3],SDL_Surface *monstreActuel);
void afficher_monstre(SDL_Rect *positionMonstre, SDL_Surface *screen, SDL_Surface *monstreActuel);


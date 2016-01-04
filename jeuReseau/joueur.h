#include <SDL/SDL.h>
/*The structure for the character,
 * use it instead the normal variable*/
typedef struct character{
		SDL_Surface *character[4];
		SDL_Surface *actualCharacter;
		SDL_Rect *position;
		int life;
		int key;
		int gold;
}*Character;

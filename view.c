#ifndef VIEW_C
#define VIEW_C
#endif

#include "view.h"

void addWelcomePage(SDL_Surface* background, SDL_Surface* welcomePage) {
    SDL_Rect pos = {0, 0};
    SDL_BlitSurface(welcomePage, NULL, background, &pos);
}

void configure(SDL_Surface* background) {
    SDL_WM_SetCaption("Sokoban", NULL);
    SDL_EnableKeyRepeat(10, 100);
    SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 0, 0, 0));
}

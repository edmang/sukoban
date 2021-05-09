#ifndef MARIO_C
#define MARIO_C
#endif

#include "mario.h"

Mario initMario(char* up, char* down, char* left, char* right) {
    Mario marioDirection;
    marioDirection.marioUp = IMG_Load(up);
    marioDirection.marioDown = IMG_Load(down);
    marioDirection.marioLeft = IMG_Load(left);
    marioDirection.marioRight = IMG_Load(right);

    return marioDirection;
}

int getHeight(Mario mario) { return mario.marioDown->h; }

int getWidth(Mario mario) { return mario.marioDown->w; };

void freeMario(Mario* marioPtr) {
    SDL_FreeSurface(marioPtr->marioUp);
    SDL_FreeSurface(marioPtr->marioDown);
    SDL_FreeSurface(marioPtr->marioLeft);
    SDL_FreeSurface(marioPtr->marioRight);
}
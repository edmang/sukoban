#ifndef MARIO_C
#define MARIO_C
#endif

#include <stdlib.h>
#include "mario.h"

Mario initMario(char* up, char* down, char* left, char* right) {
    Mario mario;
    mario.marioUp = IMG_Load(up);
    mario.marioDown = IMG_Load(down);
    mario.marioLeft = IMG_Load(left);
    mario.marioRight = IMG_Load(right);

    mario.curMario = mario.marioDown;

    mario.curPos = malloc(sizeof(SDL_Rect*));
    mario.curPos->x = 0;
    mario.curPos->y = 0;

    // SDL_Rect curPos = {0, 0};
    // mario.curPos = &curPos; -> this is wrong,
    /*
    SDL_Rect rect;
    // ...
    return &rect;
    because the pointer is not valid anymore when the function exit ...
    */
    return mario;
}

int getHeight(Mario mario) { return mario.marioDown->h; }

int getWidth(Mario mario) { return mario.marioDown->w; };

void freeMario(Mario* marioPtr) {
    SDL_FreeSurface(marioPtr->marioUp);
    SDL_FreeSurface(marioPtr->marioDown);
    SDL_FreeSurface(marioPtr->marioLeft);
    SDL_FreeSurface(marioPtr->marioRight);
    free(marioPtr->curPos);
}
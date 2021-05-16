#ifndef MARIO_H
#define MARIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct Mario {
    SDL_Surface* marioUp;
    SDL_Surface* marioLeft;
    SDL_Surface* marioRight;
    SDL_Surface* marioDown;

    SDL_Surface* curMario;

    SDL_Rect* curPos;
} Mario;

Mario initMario(char* up, char* down, char* left, char* right);
int getHeight(Mario mario);
int getWidth(Mario mario);
void freeMario(Mario* marioPtr);

#endif

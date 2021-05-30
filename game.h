#ifndef CONTROL_H
#define CONTROL_H

#include <SDL/SDL_ttf.h>
#include <stdbool.h>

#include "mario.h"
#include "material.h"

typedef enum Direction { UP, DOWN, LEFT, RIGHT } Direction;

// void startGame(Material* material, SDL_Surface* background, SDL_Surface*
// levelPage,
//           Mario* marioPtr, SDL_Surface*** map, TTF_Font * police);

void startGame(SDL_Surface* background, SDL_Surface* levelPage,
               SDL_Surface* endPage, Mario* marioPtr, TTF_Font* police);
#endif

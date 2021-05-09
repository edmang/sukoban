#ifndef CONTROL_H
#define CONTROL_H

#include <stdbool.h>

#include "mario.h"

typedef enum Direction { UP, DOWN, LEFT, RIGHT } Direction;

void play(SDL_Surface* background, Mario* marioPtr, SDL_Surface*** map);

#endif

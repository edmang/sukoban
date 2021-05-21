#ifndef CONTROL_H
#define CONTROL_H

#include <stdbool.h>
#include "material.h"
#include "mario.h"

typedef enum Direction { UP, DOWN, LEFT, RIGHT } Direction;

void play(Material * material, SDL_Surface* background, Mario* marioPtr, SDL_Surface*** map);

#endif

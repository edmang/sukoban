#ifndef MOVE_H
#define MOVE_H

#include <SDL/SDL.h>
#include <stdbool.h>

#include "coord.h"
#include "material.h"

void move(Material* material, SDL_Surface*** map, Direction direction,
          Mario* mario);
#endif
#ifndef COORD_H
#define COORD_H

#include <SDL/SDL.h>

#include "game.h"
typedef struct Coord {
    int x;
    int y;
} Coord;

Coord getNextCoordFromPixel(Direction direction, SDL_Rect* curPos);

Coord getNextCoordFromCoord(Direction direction, Coord coord);

#endif
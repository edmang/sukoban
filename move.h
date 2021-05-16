#ifndef MOVE_H
#define MOVE_H

#include <SDL/SDL.h>
#include <stdbool.h>

#include "coord.h"
#include "material.h"

void up(Material* material, SDL_Surface*** map, SDL_Rect* position,
        Coord nextCoord);
void down(Material* material, SDL_Surface*** map, SDL_Rect* position,
          Coord nextCoord);
void left(Material* material, SDL_Surface*** map, SDL_Rect* position,
          Coord nextCoord);
void right(Material* material, SDL_Surface*** map, SDL_Rect* position,
           Coord nextCoord);

bool isBox(Material* material, SDL_Surface*** map, int y, int x);

bool isMoveOk(Material* material, SDL_Surface*** map, int y, int x);

bool isTarget(Material* material, SDL_Surface*** map, int y, int x);

#endif
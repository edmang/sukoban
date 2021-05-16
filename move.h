#ifndef MOVE_H
#define MOVE_H

#include <SDL/SDL.h>
#include <stdbool.h>

#include "coord.h"
#include "material.h"

void move(Material* material, SDL_Surface*** map, Direction direction,
          Mario* mario);

void up(Material* material, SDL_Surface*** map, Mario* mario, Coord nextCoord);
void down(Material* material, SDL_Surface*** map, Mario* mario,
          Coord nextCoord);
void left(Material* material, SDL_Surface*** map, Mario* mario,
          Coord nextCoord);
void right(Material* material, SDL_Surface*** map, Mario* mario,
           Coord nextCoord);

bool isBox(Material* material, SDL_Surface*** map, int y, int x);

bool isBoxOk(Material* material, SDL_Surface*** map, int y, int x);

bool isMoveOk(Material* material, SDL_Surface*** map, int y, int x);

bool isTarget(Material* material, SDL_Surface*** map, int y, int x);

#endif
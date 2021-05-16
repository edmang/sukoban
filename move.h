#ifndef MOVE_H
#define MOVE_H

#include <SDL/SDL.h>
#include "material.h"

void up(Material* material, SDL_Surface*** map, SDL_Rect* position);
void down(Material* material, SDL_Surface*** map, SDL_Rect* position);
void left(Material* material, SDL_Surface*** map, SDL_Rect* position);
void right(Material* material, SDL_Surface*** map, SDL_Rect* position);

#endif
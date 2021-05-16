
#include "move.h"

#include <SDL/SDL.h>
#include <stdbool.h>

#include "const.h"
#include "coord.h"
#include "material.h"

bool isNextBox(Material* material, SDL_Surface*** map, int nextY, int nextX) {
    return (map[nextY][nextX] == material->box) ||
           (map[nextY][nextX] == material->boxOk);
}

bool isNextMoveOk(Material* material, SDL_Surface*** map, int nextY,
                  int nextX) {
    return !((map[nextY][nextX] == material->wall) ||
             (map[nextY][nextX] == material->box) ||
             (map[nextY][nextX] == material->boxOk));
}

void up(Material* material, SDL_Surface*** map, SDL_Rect* position,
        Coord coord) {
    if (position->y > 0) {
        int y = coord.y;
        int x = coord.x;
        if (y >= 0 && y <= SIZE) {
            if (isNextMoveOk(material, map, y, x)) {
                position->y -= WINDOW_SCALE;
            }
        }
    }
}

void down(Material* material, SDL_Surface*** map, SDL_Rect* position,
          Coord coord) {
    if (position->y < (WINDOW_SIZE - WINDOW_SCALE)) {
        int y = coord.y;
        int x = coord.x;
        if (y >= 0 && y <= SIZE) {
            if (isNextMoveOk(material, map, y, x)) {
                position->y += WINDOW_SCALE;
            }
        }
    }
}

void left(Material* material, SDL_Surface*** map, SDL_Rect* position,
          Coord coord) {
    if (position->x > 0) {
        int y = coord.y;
        int x = coord.x;
        if (x >= 0 && x <= SIZE) {
            if (isNextMoveOk(material, map, y, x)) {
                position->x -= WINDOW_SCALE;
            }
        }
    }
}

void right(Material* material, SDL_Surface*** map, SDL_Rect* position,
           Coord coord) {
    if (position->x < (WINDOW_SIZE - WINDOW_SCALE)) {
        int y = coord.y;
        int x = coord.x;
        if (x >= 0 && x <= SIZE) {
            if (isNextMoveOk(material, map, y, x)) {
                position->x += WINDOW_SCALE;
            }
        }
    }
}

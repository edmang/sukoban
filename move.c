
#include "move.h"

#include <SDL/SDL.h>
#include <stdbool.h>

#include "const.h"
#include "coord.h"
#include "material.h"

bool isBox(Material* material, SDL_Surface*** map, int y, int x) {
    return (map[y][x] == material->box) || (map[y][x] == material->boxOk);
}

bool isTarget(Material* material, SDL_Surface*** map, int y, int x) {
    return map[y][x] == material->target;
}

bool isMoveOk(Material* material, SDL_Surface*** map, int y, int x) {
    return !((map[y][x] == material->wall) || (map[y][x] == material->box) ||
             (map[y][x] == material->boxOk));
}

void up(Material* material, SDL_Surface*** map, SDL_Rect* position,
        Coord coord) {
    if (position->y > 0) {
        int y = coord.y;
        int x = coord.x;
        if (y >= 0 && y <= SIZE) {
            if (isMoveOk(material, map, y, x)) {
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
            if (isMoveOk(material, map, y, x)) {
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
            if (isMoveOk(material, map, y, x)) {
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
            if (isMoveOk(material, map, y, x)) {
                position->x += WINDOW_SCALE;
            }
        }
    }
}

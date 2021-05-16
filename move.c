
#include "move.h"

#include <SDL/SDL.h>
#include <stdbool.h>

#include "const.h"
#include "material.h"

bool isWallOnY(Material* material, SDL_Surface*** map, int nextY, int x) {
    return map[nextY][x] == material->wall;
}

bool isWallOnX(Material* material, SDL_Surface*** map, int y, int nextX) {
    return map[y][nextX] == material->wall;
}

void up(Material* material, SDL_Surface*** map, SDL_Rect* position) {
    if (position->y > 0) {
        int nextY = (position->y - WINDOW_SCALE) / WINDOW_SCALE;
        int curX = (position->x / WINDOW_SCALE);
        if (nextY >= 0 && nextY <= SIZE) {
            if (!isWallOnY(material, map,nextY, curX)) {
                position->y -= WINDOW_SCALE;
            }
        }
    }
}

void down(Material* material, SDL_Surface*** map, SDL_Rect* position) {
    if (position->y < (WINDOW_SIZE - WINDOW_SCALE)) {
        int nextY = (position->y + WINDOW_SCALE) / WINDOW_SCALE;
        int curX = position->x / WINDOW_SCALE;
        if (nextY >= 0 && nextY <= SIZE) {
            if (!isWallOnY(material, map, nextY, curX)) {
                position->y += WINDOW_SCALE;
            }
        }
    }
}

void left(Material* material, SDL_Surface*** map, SDL_Rect* position) {
    if (position->x > 0) {
        int curY = position->y / WINDOW_SCALE;
        int nextX = (position->x - WINDOW_SCALE) / WINDOW_SCALE;
        if (nextX >= 0 && nextX <= SIZE) {
            if (!isWallOnX(material, map, curY, nextX)) {
                position->x -= WINDOW_SCALE;
            }
        }
    }
}

void right(Material* material, SDL_Surface*** map, SDL_Rect* position) {
    if (position->x < (WINDOW_SIZE - WINDOW_SCALE)) {
        int curY = position->y / WINDOW_SCALE;
        int nextX = (position->x + WINDOW_SCALE) / WINDOW_SCALE;
        if (nextX >= 0 && nextX <= SIZE) {
            if (!isWallOnX(material, map, curY, nextX)) {
                position->x += WINDOW_SCALE;
            }
        }
    }
}

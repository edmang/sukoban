
#include "move.h"

#include <SDL/SDL.h>
#include <stdbool.h>

#include "const.h"
#include "coord.h"
#include "material.h"

void handleMoveOutFromTarget(Material* material, SDL_Surface*** map,
                             Coord nextNextCoord) {
    if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
        map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
    } else {
        map[nextNextCoord.y][nextNextCoord.x] = material->box;
    }
}

void actuallyMove(Material* material, SDL_Surface*** map, Mario* mario,
                  Coord nextCoord, Coord nextNextCoord,
                  void (*fun)(Material*, SDL_Surface***, Mario*, Coord)) {
    fun(material, map, mario, nextCoord);

    if (isBox(material, map, nextCoord.y, nextCoord.x)) {
        if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
            handleMoveOutFromTarget(material, map, nextNextCoord);
            map[nextCoord.y][nextCoord.x] = material->empty;
            fun(material, map, mario, nextCoord);
        }
    }

    if (isBoxOk(material, map, nextCoord.y, nextCoord.x)) {
        if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
            handleMoveOutFromTarget(material, map, nextNextCoord);
            map[nextCoord.y][nextCoord.x] = material->target;
            fun(material, map, mario, nextCoord);
        }
    }
}

//
bool isBox(Material* material, SDL_Surface*** map, int y, int x) {
    return map[y][x] == material->box;
}

bool isBoxOk(Material* material, SDL_Surface*** map, int y, int x) {
    return map[y][x] == material->boxOk;
}

bool isTarget(Material* material, SDL_Surface*** map, int y, int x) {
    return map[y][x] == material->target;
}

bool isMoveOk(Material* material, SDL_Surface*** map, int y, int x) {
    return !((map[y][x] == material->wall) || (map[y][x] == material->box) ||
             (map[y][x] == material->boxOk));
}

void move(Material* material, SDL_Surface*** map, Direction direction,
          Mario* mario) {
    Coord nextCoord = getNextCoordFromPixel(direction, mario->curPos);
    Coord nextNextCoord = getNextCoordFromCoord(direction, nextCoord);

    switch (direction) {
        case UP:
            actuallyMove(material, map, mario, nextCoord, nextNextCoord, up);
            break;

        case DOWN:
            actuallyMove(material, map, mario, nextCoord, nextNextCoord, down);
            break;

        case LEFT:
            actuallyMove(material, map, mario, nextCoord, nextNextCoord, left);
            break;

        case RIGHT:
            actuallyMove(material, map, mario, nextCoord, nextNextCoord, right);
            break;
    }
}

void up(Material* material, SDL_Surface*** map, Mario* mario, Coord coord) {
    if (mario->curPos->y > 0) {
        int y = coord.y;
        int x = coord.x;
        if (y >= 0 && y <= SIZE) {
            if (isMoveOk(material, map, y, x)) {
                mario->curPos->y -= WINDOW_SCALE;
                mario->curMario = mario->marioUp;
            }
        }
    }
}

void down(Material* material, SDL_Surface*** map, Mario* mario, Coord coord) {
    if (mario->curPos->y < (WINDOW_SIZE - WINDOW_SCALE)) {
        int y = coord.y;
        int x = coord.x;
        if (y >= 0 && y <= SIZE) {
            if (isMoveOk(material, map, y, x)) {
                mario->curPos->y += WINDOW_SCALE;
                mario->curMario = mario->marioDown;
            }
        }
    }
}

void left(Material* material, SDL_Surface*** map, Mario* mario, Coord coord) {
    if (mario->curPos->x > 0) {
        int y = coord.y;
        int x = coord.x;
        if (x >= 0 && x <= SIZE) {
            if (isMoveOk(material, map, y, x)) {
                mario->curPos->x -= WINDOW_SCALE;
                mario->curMario = mario->marioLeft;
            }
        }
    }
}

void right(Material* material, SDL_Surface*** map, Mario* mario, Coord coord) {
    if (mario->curPos->x < (WINDOW_SIZE - WINDOW_SCALE)) {
        int y = coord.y;
        int x = coord.x;
        if (x >= 0 && x <= SIZE) {
            if (isMoveOk(material, map, y, x)) {
                mario->curPos->x += WINDOW_SCALE;
                mario->curMario = mario->marioRight;
            }
        }
    }
}

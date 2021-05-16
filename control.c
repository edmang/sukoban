
#include "control.h"

#include <SDL/SDL.h>

#include "const.h"
#include "coord.h"
#include "material.h"
#include "move.h"

void startLevel(SDL_Surface* background, SDL_Surface*** map, int size) {
    SDL_Rect curPos = {0, 0};
    for (int i = 0; i < size; i++) {
        curPos.x = 0;
        for (int j = 0; j < size; j++) {
            SDL_BlitSurface(map[i][j], NULL, background, &curPos);
            curPos.x += WINDOW_SCALE;
        }
        curPos.y += WINDOW_SCALE;
    }
}

void applyWindowScale(SDL_Rect* position) {
    position->x = position->x * WINDOW_SCALE;
    position->y = position->y * WINDOW_SCALE;
}

void initGame(SDL_Surface* background, SDL_Rect* curPos, Mario* marioPtr,
              SDL_Surface** curMarioDir) {
    curPos->x = 4;
    curPos->y = 4;
    applyWindowScale(curPos);
    *curMarioDir = marioPtr->marioDown;
}

void move(Material* material, SDL_Surface*** map, Direction direction,
          SDL_Surface** curMarioDir, Mario* marioPtr, SDL_Rect* curPos) {
    Coord nextCoord = getNextCoordFromPixel(direction, curPos);
    Coord nextNextCoord = getNextCoordFromCoord(direction, nextCoord);

    if (direction == UP) {
        up(material, map, curPos, nextCoord);
        *curMarioDir = marioPtr->marioUp;

        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                up(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioUp;
            }
        }

        if (isBoxOk(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->target;
                up(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioUp;
            }
        }

    } else if (direction == DOWN) {
        down(material, map, curPos, nextCoord);
        *curMarioDir = marioPtr->marioDown;

        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                down(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioDown;
            }
        }

        if (isBoxOk(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->target;
                down(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioDown;
            }
        }

    } else if (direction == LEFT) {
        left(material, map, curPos, nextCoord);
        *curMarioDir = marioPtr->marioLeft;

        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                left(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioLeft;
            }
        }

        if (isBoxOk(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->target;
                left(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioLeft;
            }
        }

    } else if (direction == RIGHT) {
        right(material, map, curPos, nextCoord);
        *curMarioDir = marioPtr->marioRight;

        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                right(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioRight;
            }
        }

        if (isBoxOk(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->target;
                right(material, map, curPos, nextCoord);
                *curMarioDir = marioPtr->marioRight;
            }
        }
    }
}

void play(Material* material, SDL_Surface* background, Mario* marioPtr,
          SDL_Surface*** map) {
    bool keep = true;
    bool isGameStart = false;
    SDL_Event event;
    SDL_Rect curPos;
    SDL_Surface* curMarioDir = NULL;

    while (keep) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                keep = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        initGame(background, &curPos, marioPtr, &curMarioDir);
                        isGameStart = true;
                        break;

                    case SDLK_UP:
                        move(material, map, UP, &curMarioDir, marioPtr,
                             &curPos);
                        break;

                    case SDLK_DOWN:
                        move(material, map, DOWN, &curMarioDir, marioPtr,
                             &curPos);
                        break;

                    case SDLK_LEFT:
                        move(material, map, LEFT, &curMarioDir, marioPtr,
                             &curPos);
                        break;

                    case SDLK_RIGHT:
                        move(material, map, RIGHT, &curMarioDir, marioPtr,
                             &curPos);
                        break;

                    case SDLK_ESCAPE:
                        keep = false;
                        break;
                }
                break;
        }

        if (isGameStart) {
            SDL_FillRect(background, NULL,
                         SDL_MapRGB(background->format, 220, 220, 220));
            startLevel(background, map, SIZE);
            SDL_BlitSurface(curMarioDir, NULL, background, &curPos);
            SDL_Flip(background);
        }
    }

    freeMario(marioPtr);
}

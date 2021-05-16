
#include "control.h"

#include <SDL/SDL.h>

#include "const.h"
#include "coord.h"
#include "material.h"
#include "move.h"

void displayMap(SDL_Surface* background, SDL_Surface*** map, int size) {
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

void initGame(Mario* marioPtr) {
    marioPtr->curPos->x = 4 * WINDOW_SCALE;
    marioPtr->curPos->y = 4 * WINDOW_SCALE;
}

void move(Material* material, SDL_Surface*** map, Direction direction,
          Mario* marioPtr) {
    Coord nextCoord = getNextCoordFromPixel(direction, marioPtr->curPos);
    Coord nextNextCoord = getNextCoordFromCoord(direction, nextCoord);

    if (direction == UP) {
        up(material, map, marioPtr, nextCoord);
        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                up(material, map, marioPtr, nextCoord);
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
                up(material, map, marioPtr, nextCoord);
            }
        }

    } else if (direction == DOWN) {
        down(material, map, marioPtr, nextCoord);
        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                down(material, map, marioPtr, nextCoord);
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
                down(material, map, marioPtr, nextCoord);
            }
        }

    } else if (direction == LEFT) {
        left(material, map, marioPtr, nextCoord);
        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                left(material, map, marioPtr, nextCoord);
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
                left(material, map, marioPtr, nextCoord);
            }
        }

    } else if (direction == RIGHT) {
        right(material, map, marioPtr, nextCoord);
        if (isBox(material, map, nextCoord.y, nextCoord.x)) {
            if (isMoveOk(material, map, nextNextCoord.y, nextNextCoord.x)) {
                if (isTarget(material, map, nextNextCoord.y, nextNextCoord.x)) {
                    map[nextNextCoord.y][nextNextCoord.x] = material->boxOk;
                } else {
                    map[nextNextCoord.y][nextNextCoord.x] = material->box;
                }
                map[nextCoord.y][nextCoord.x] = material->empty;
                right(material, map, marioPtr, nextCoord);
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
                right(material, map, marioPtr, nextCoord);
            }
        }
    }
}

void play(Material* material, SDL_Surface* background, Mario* marioPtr,
          SDL_Surface*** map) {
    bool keep = true;
    bool isGameStart = false;
    SDL_Event event;

    while (keep) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                keep = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        initGame(marioPtr);
                        isGameStart = true;
                        break;

                    case SDLK_UP:
                        move(material, map, UP, marioPtr);
                        break;

                    case SDLK_DOWN:
                        move(material, map, DOWN, marioPtr);
                        break;

                    case SDLK_LEFT:
                        move(material, map, LEFT, marioPtr);
                        break;

                    case SDLK_RIGHT:
                        move(material, map, RIGHT, marioPtr);
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
            displayMap(background, map, SIZE);
            SDL_BlitSurface(marioPtr->curMario, NULL, background, marioPtr->curPos);
            SDL_Flip(background);
        }
    }
}

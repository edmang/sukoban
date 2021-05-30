
#include "game.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "const.h"
#include "material.h"
#include "move.h"

void displayGameMap(SDL_Surface* background, SDL_Surface*** map, int size) {
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

void initMarioPosition(Mario* marioPtr, char* level, int size) {
    int i = 0;
    int j = 0;
    bool isEmpty = false;

    while (i < size) {
        j = 0;
        while (j < size) {
            if (level[i * size + j] == 'M') {
                isEmpty = true;
                break;
            }
            j++;
        }

        if (isEmpty) {
            break;
        }
        i++;
    }
    marioPtr->curPos->x = j * WINDOW_SCALE;
    marioPtr->curPos->y = i * WINDOW_SCALE;
    marioPtr->curMario = marioPtr->marioDown;
}

void modifyGameLevel(bool isIncreasing, int* level) {
    if (isIncreasing) {
        if (*level < MAX_LEVEL) {
            (*level)++;
        }
    } else {
        if (*level > 0) {
            (*level)--;
        }
    }
}

bool isWin(SDL_Surface*** map, Material* material, int size) {
    int i = 0;
    int j = 0;
    while (i < size) {
        j = 0;
        while (j < size) {
            if (map[i][j] == material->box) {
                return false;
            }
            j++;
        }
        i++;
    }

    return true;
}

void startGame(SDL_Surface* background, SDL_Surface* levelPage,
               SDL_Surface* endPage, Mario* mario, TTF_Font* police) {
    bool keep = true;
    bool isGameStart = false;
    bool isPlayStart = false;
    int selectedLevel = 0;
    char levelStr[2];
    char levelPath[10];
    sprintf(levelStr, "%d", selectedLevel);
    SDL_Color fontColor = {255, 255, 255};
    SDL_Surface* text = TTF_RenderText_Solid(police, levelStr, fontColor);

    // Load game context
    Material material = initMaterial(WALL, BOX, BOX_OK, TARGET);
    char* level = NULL;
    SDL_Surface*** map = NULL;

    SDL_Event event;
    while (keep) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            keep = false;
        } else if (event.type == SDL_KEYDOWN &&
                   event.key.keysym.sym == SDLK_SPACE) {
            isGameStart = true;
        }

        if (isGameStart && event.type == SDL_KEYDOWN) {  // choose level then
            if (!isPlayStart) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        modifyGameLevel(true, &selectedLevel);
                        break;

                    case SDLK_DOWN:
                        modifyGameLevel(false, &selectedLevel);
                        break;

                    case SDLK_RETURN:
                        sprintf(levelPath, "level/%d", selectedLevel);
                        level = loadLevel(levelPath);
                        map = convertLevelToMap(material, level, SIZE);
                        initMarioPosition(mario, level, SIZE);
                        isPlayStart = true;
                        break;
                }
            }

            SDL_Rect levelPagePos = {0, 0};
            SDL_BlitSurface(levelPage, NULL, background, &levelPagePos);

            sprintf(levelStr, "%d", selectedLevel);
            text = TTF_RenderText_Solid(police, levelStr, fontColor);
            SDL_Rect levelPos = {WINDOW_SIZE / 2, WINDOW_SIZE / 2};
            SDL_BlitSurface(text, NULL, background, &levelPos);

            bool gameEnd = false;
            if (isPlayStart && event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        move(&material, map, UP, mario);
                        break;

                    case SDLK_DOWN:
                        move(&material, map, DOWN, mario);
                        break;

                    case SDLK_LEFT:
                        move(&material, map, LEFT, mario);
                        break;

                    case SDLK_RIGHT:
                        move(&material, map, RIGHT, mario);
                        break;

                    case SDLK_ESCAPE:
                        map = convertLevelToMap(material, level, SIZE);
                        initMarioPosition(mario, level, SIZE);
                        break;
                }

                if (isWin(map, &material, SIZE)) {
                    if (selectedLevel < MAX_LEVEL) {
                        modifyGameLevel(true, &selectedLevel);
                        sprintf(levelPath, "level/%d", selectedLevel);
                        level = loadLevel(levelPath);
                        map = convertLevelToMap(material, level, SIZE);
                        initMarioPosition(mario, level, SIZE);
                    } else {
                        gameEnd = true;
                    }
                }

                if (!gameEnd) {
                    SDL_FillRect(background, NULL,
                                 SDL_MapRGB(background->format, 220, 220, 220));
                    displayGameMap(background, map, SIZE);
                    SDL_BlitSurface(mario->curMario, NULL, background,
                                    mario->curPos);
                } else {
                    SDL_BlitSurface(endPage, NULL, background, &levelPagePos);
                }
            }

            SDL_Flip(background);
        }
    }

    free(level);
    freeMaterial(&material);
    free(map);  // map points to material, which is already free
}

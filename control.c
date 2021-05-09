
#include "control.h"

#include <SDL/SDL.h>

#include "const.h"
#include "gameContext.h"

void move(Direction direction, SDL_Surface** curMarioDir, Mario* marioPtr,
          SDL_Rect* curPos);

void initGame(SDL_Surface* background, SDL_Rect* curPos, Mario* marioPtr,
              SDL_Surface** curMarioDir);

void startLevel(SDL_Surface* background, SDL_Surface*** map, int maxRow,
                int maxCol);

void play(SDL_Surface* background, Mario* marioPtr, SDL_Surface*** map) {
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
                        move(UP, &curMarioDir, marioPtr, &curPos);
                        break;

                    case SDLK_DOWN:
                        move(DOWN, &curMarioDir, marioPtr, &curPos);
                        break;

                    case SDLK_LEFT:
                        move(LEFT, &curMarioDir, marioPtr, &curPos);
                        break;

                    case SDLK_RIGHT:
                        move(RIGHT, &curMarioDir, marioPtr, &curPos);
                        break;

                    case SDLK_ESCAPE:
                        keep = false;
                        break;
                }
                break;
        }

        if (isGameStart) {
            SDL_FillRect(background, NULL,
                         SDL_MapRGB(background->format, 0, 0, 0));
            startLevel(background, map, ROW_SIZE, COL_SIZE);
            SDL_BlitSurface(curMarioDir, NULL, background, &curPos);
            SDL_Flip(background);
        }
    }

    freeMario(marioPtr);
}

// Private functions
void startLevel(SDL_Surface* background, SDL_Surface*** map, int maxRow,
                int maxCol) {
    SDL_Rect curPos = {0, 0};
    for (int i = 0; i < maxRow; i++) {
        curPos.x = 0;
        for (int j = 0; j < maxCol; j++) {
            SDL_BlitSurface(map[i][j], NULL, background, &curPos);
            curPos.x += WINDOW_SCALE;
        }
        curPos.y += WINDOW_SCALE;
    }
}

void initGame(SDL_Surface* background, SDL_Rect* curPos, Mario* marioPtr,
              SDL_Surface** curMarioDir) {
    curPos->x = 0;
    curPos->y = 0;
    *curMarioDir = marioPtr->marioDown;
}

void move(Direction direction, SDL_Surface** curMarioDir, Mario* marioPtr,
          SDL_Rect* curPos) {
    if (direction == UP) {
        if (curPos->y > 0) {
            curPos->y -= WINDOW_SCALE;
        }
        *curMarioDir = marioPtr->marioUp;

    } else if (direction == DOWN) {
        if (curPos->y < (HEIGHT - WINDOW_SCALE)) {
            curPos->y += WINDOW_SCALE;
        }
        *curMarioDir = marioPtr->marioDown;

    } else if (direction == LEFT) {
        if (curPos->x > 0) {
            curPos->x -= WINDOW_SCALE;
        }
        *curMarioDir = marioPtr->marioLeft;

    } else if (direction == RIGHT) {
        if ((curPos->x) < (WIDTH - WINDOW_SCALE)) {
            curPos->x += WINDOW_SCALE;
        }
        *curMarioDir = marioPtr->marioRight;
    }
}

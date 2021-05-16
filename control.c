
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

void play(Material* material, SDL_Surface* background, Mario* mario,
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
                        initGame(mario);
                        isGameStart = true;
                        break;

                    case SDLK_UP:
                        move(material, map, UP, mario);
                        break;

                    case SDLK_DOWN:
                        move(material, map, DOWN, mario);
                        break;

                    case SDLK_LEFT:
                        move(material, map, LEFT, mario);
                        break;

                    case SDLK_RIGHT:
                        move(material, map, RIGHT, mario);
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
            SDL_BlitSurface(mario->curMario, NULL, background,
                            mario->curPos);
            SDL_Flip(background);
        }
    }
}

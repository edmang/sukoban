#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "game.h"
#include "mario.h"
#include "material.h"
#include "view.h"

int main(int argn, char** argv) {
    // Start
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* police = TTF_OpenFont("img/CHERL.TTF", FONT_SIZE);

    SDL_Surface* background = SDL_SetVideoMode(WINDOW_SIZE, WINDOW_SIZE, 32,
                                               SDL_HWSURFACE | SDL_DOUBLEBUF);

    configure(background);
    Mario mario = initMario(MARIO_UP, MARIO_DOWN, MARIO_LEFT, MARIO_RIGHT);

    // Welcome
    SDL_Surface* welcomePage = IMG_Load(WELCOME_PAGE);
    addWelcomePage(background, welcomePage);
    SDL_Flip(background);

    // Engine
    SDL_Surface* levelPage = IMG_Load(LEVEL_PAGE);
    SDL_Surface* endPage = IMG_Load(END_PAGE);
    startGame(background, levelPage, endPage, &mario, police);

    // End
    freeMario(&mario);
    SDL_FreeSurface(welcomePage);
    SDL_FreeSurface(levelPage);
    SDL_FreeSurface(endPage);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

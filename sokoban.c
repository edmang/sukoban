#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "control.h"
#include "gameContext.h"
#include "mario.h"
#include "view.h"

int main(int argn, char** argv) {
    // Start
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* background =
        SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    configure(background);
    Mario mario = initMario(MARIO_UP, MARIO_DOWN, MARIO_LEFT, MARIO_RIGHT);

    // Welcome
    SDL_Surface* welcomePage = IMG_Load(WELCOME_PAGE);
    addWelcomePage(background, welcomePage);
    SDL_Flip(background);

    // Load game context
    Material material = initMaterial(WALL, BOX, BOX_OK, TARGET, EMPTY);
    char** level = loadLevel("level");
    SDL_Surface*** map = convertLevelToMap(material, level, ROW_SIZE, COL_SIZE);

    // Engine
    play(background, &mario, map);

    // End
    SDL_FreeSurface(welcomePage);
    freeMaterial(&material);
    SDL_Quit();

    return 0;
}

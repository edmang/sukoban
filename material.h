#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct Material {
    SDL_Surface* wall;
    SDL_Surface* box;
    SDL_Surface* boxOk;
    SDL_Surface* target;
    SDL_Surface* empty;
} Material;

Material initMaterial(char* wall, char* box, char* boxOk, char* target);

SDL_Surface*** convertLevelToMap(Material material, char** level, int size);

void freeMaterial(Material* materialPtr);

char** loadLevel(char* filePath);
#endif
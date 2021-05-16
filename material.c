#include "material.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"

char** initLevel(int size) {
    char** elements = (char**)malloc(sizeof(char*) * size);
    for (int i = 0; i < size; i++) {
        elements[i] = (char*)malloc(sizeof(char) * size);
    }

    return elements;
}

SDL_Surface*** initMap(int size) {
    SDL_Surface*** map = (SDL_Surface***)malloc(sizeof(SDL_Surface**) * size);
    for (int i = 0; i < size; i++) {
        map[i] = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * size);
        for (int j = 0; j < size; j++) {
            map[i][j] = NULL;
        }
    }

    return map;
}

SDL_Surface* convertCharToMaterial(char c, Material material) {
    switch (c) {
        case 'W':
            return material.wall;
        case 'B':
            return material.box;
        case 'T':
            return material.target;
        case 'O':
            return material.boxOk;
        case 'E':
            return material.empty;
        default:
            return NULL;
    }
}

SDL_Surface*** convertLevelToMap(Material material, char** level, int size) {
    SDL_Surface*** map = initMap(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            map[i][j] = convertCharToMaterial(level[i][j], material);
        }
    }

    return map;
}

void freeMaterial(Material* materialPtr) {
    free(materialPtr->box);
    free(materialPtr->boxOk);
    free(materialPtr->target);
    free(materialPtr->wall);
}

Material initMaterial(char* wall, char* box, char* boxOk, char* target) {
    Material material;
    material.wall = IMG_Load(wall);
    material.box = IMG_Load(box);
    material.boxOk = IMG_Load(boxOk);
    material.target = IMG_Load(target);
    return material;
}

char** loadLevel(char* filePath) {
    FILE* levelFile = fopen(filePath, "r+");

    if (levelFile != NULL) {
        char** elements = initLevel(SIZE);
        char* buffer = malloc(sizeof(char) * CHUNK_SIZE);
        int i = 0;
        while (fgets(buffer, CHUNK_SIZE, levelFile)) {
            for (int j = 0; j < SIZE; j++) {
                elements[i][j] = buffer[j];
            }
            i++;
        }

        free(buffer);
        fclose(levelFile);

        return elements;
    }
}

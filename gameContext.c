#include "gameContext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"

char** initLevel(int rowSize, int colSize);
SDL_Surface*** initMap(int maxRow, int maxCol);
SDL_Surface* convertCharToMaterial(char c, Material material);

//
void freeMaterial(Material* materialPtr) {
    free(materialPtr->box);
    free(materialPtr->boxOk);
    free(materialPtr->empty);
    free(materialPtr->target);
    free(materialPtr->wall);
}

SDL_Surface*** convertLevelToMap(Material material, char** level, int maxRow,
                                 int maxCol) {
    SDL_Surface*** map = initMap(maxRow, maxCol);

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            map[i][j] = convertCharToMaterial(level[i][j], material);
        }
    }

    return map;
}

Material initMaterial(char* wall, char* box, char* boxOk, char* target, char * empty) {
    Material material;
    material.wall = IMG_Load(wall);
    material.box = IMG_Load(box);
    material.boxOk = IMG_Load(boxOk);
    material.target = IMG_Load(target);
    material.empty = IMG_Load(empty);
    return material;
}

// Private functions
SDL_Surface*** initMap(int maxRow, int maxCol) {
    SDL_Surface*** map = (SDL_Surface***)malloc(sizeof(SDL_Surface**) * maxRow);
    for (int i = 0; i < maxRow; i++) {
        map[i] = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * maxCol);
        for (int j = 0; j < maxCol; j++) {
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

char** loadLevel(char* filePath) {
    FILE* levelFile = fopen(filePath, "r+");

    if (levelFile != NULL) {
        char** elements = initLevel(ROW_SIZE, COL_SIZE);
        char* buffer = malloc(sizeof(char) * CHUNK_SIZE);
        int i = 0;
        while (fgets(buffer, 14, levelFile)) {
            for (int j = 0; j < COL_SIZE; j++) {
                elements[i][j] = buffer[j];
            }
            i++;
        }

        free(buffer);
        fclose(levelFile);

        return elements;
    }
}

char** initLevel(int rowSize, int colSize) {
    char** elements = (char**)malloc(sizeof(char*) * rowSize);
    for (int i = 0; i < rowSize; i++) {
        elements[i] = (char*)malloc(sizeof(char) * colSize);
    }

    return elements;
}

#include "coord.h"

#include "const.h"

Coord getNextCoordFromCoord(Direction direction, Coord coord) {
    Coord nextCoord;
    nextCoord.x = coord.x;
    nextCoord.y = coord.y;
    switch (direction) {
        case UP:
            if (coord.y > 0) {
                nextCoord.y -= 1;
            }
            return nextCoord;

        case DOWN:
            if (coord.y < SIZE) {
                nextCoord.y += 1;
            }
            return nextCoord;

        case LEFT:
            if (coord.x > 0) {
                nextCoord.x -= 1;
            }
            return nextCoord;

        case RIGHT:
            if (coord.x < SIZE) {
                nextCoord.x += 1;
            }
            return nextCoord;
    }
}

Coord getNextCoordFromPixel(Direction direction, SDL_Rect* curPos) {
    Coord nextCoord;
    nextCoord.x = curPos->x / WINDOW_SCALE;
    nextCoord.y = curPos->y / WINDOW_SCALE;
    switch (direction) {
        case UP:
            if (nextCoord.y > 0) {
                nextCoord.y = (curPos->y - WINDOW_SCALE) / WINDOW_SCALE;
                nextCoord.x = (curPos->x / WINDOW_SCALE);
            }
            return nextCoord;

        case DOWN:
            if (nextCoord.y < SIZE) {
                nextCoord.y = (curPos->y + WINDOW_SCALE) / WINDOW_SCALE;
                nextCoord.x = (curPos->x / WINDOW_SCALE);
            }
            return nextCoord;

        case LEFT:
            if (nextCoord.x > 0) {
                nextCoord.y = (curPos->y / WINDOW_SCALE);
                nextCoord.x = (curPos->x - WINDOW_SCALE) / WINDOW_SCALE;
            }
            return nextCoord;

        case RIGHT:
            if (nextCoord.x < SIZE) {
                nextCoord.y = (curPos->y / WINDOW_SCALE);
                nextCoord.x = (curPos->x + WINDOW_SCALE) / WINDOW_SCALE;
            }
            return nextCoord;
    }
}

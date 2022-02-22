#ifndef DISPLAY_H
#define DISPLAY_H

#include "one_armed_bandits.h"
#include "display_utilities.h"

void *display_func(void *param);

SDL_Window* init_window();

extern int object_height;

void drawCoins(int count, int xPositionBeginCoins, int yPositionBeginCoins);

void drawWheels(int xPositionBeginWheels, int yPositionBeginWheels, int* yWheels);

void drawVictoryRectangles(int xPositionBeginWheels, int yPositionBeginWheels, game* gameInfos);

bool isAWinnerWheel(game *gameInfos, int indexWheel);

#endif
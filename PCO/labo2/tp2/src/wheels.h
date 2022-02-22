#ifndef WHEELS_H
#define WHEELS_H

#include <math.h>
#include "display_utilities.h"
#include "one_armed_bandits.h"

void *wheel_func(void *args);

int calculateWin(game* gameInfos);

void displayResultAndActualizeGame(game* gameInfos);

#endif
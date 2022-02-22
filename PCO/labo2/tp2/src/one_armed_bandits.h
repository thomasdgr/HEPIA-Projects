#ifndef ONE_ARMED_BANDITS
#define ONE_ARMED_BANDITS

#include <stdbool.h>

#include "multithreading_utilities.h"

#define WHEEL_NB 3

#define OBJECT_NB 7
#define BANK_INIT_MONEY 30
#define WALLET_INIT_MONEY 10
#define WHEELS_ALL_STOPPED WHEEL_NB -1 //Value for iStopWheels to indicates all wheels are stopped
#define WHEELS_ALL_ROTATING -1


/* main structure shared with every thread so data from the game
 * can be upgraded and display at any time
 * params : wallet -> current money in the player's wallet
            bank -> current money in the bank
            iStopWheels -> index of the last wheel stopped
	        barrierStop -> Barrier used to stop wheels and created with a semaphore to avoid deadlock
            quit -> true if player wants to leave the game
            yWheels -> arrray containing y coordinates of the image for each wheels
            numberOfWinningWheels -> number of wheels that are the same when they are all stopped
            semaWaitWheels -> semaphore used to ensure that all wheels are stopped before check victory.
 */
typedef struct game{
    int wallet;
    int bank;
    int iStopWheels;
	sem_barrier* barrierStop;
    bool quit;
    int *yWheels;
    int numberOfWinningWheels;
  sem_t* semaWaitWheels;
} game;

#endif

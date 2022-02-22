/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le Bandit Manchot réalisé dans le
           | _ _`\|        |          cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Fonctions permettant de gerer les
(___)  )\/  \_____/  ~\.   |                rotations des roues à partir d'une image
(___) . \   `         `\   |                ainsi que de gerer les conditions de
 (__)-    ,/        (   |  |			    victoire lorsque les roues sont arretees
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 24/05/2021

*****************************************************************************/

#include "wheels.h"

// global value taken from display.h
extern int object_height;

/* thread that manage a wheel and update yWheels[] from game structure -> one thread for each wheel
 * arg: void* args -> need to be convert to game*
 * return: void
 * description: each wheel has a specific thread and share the variavle wheelNumber. Their code update the position
 *	 of the wheel at a specific rate and store the y coordinate in the field "yWheels" from the structure given in argument.
 *	 They also have a passive wait triggered when the player decided to stop a wheel by pressing "SDLK_SPACE" on the keyboard.
 *	 When the 3 wheels are stoped, the last one calls the function calculateWin() to maybe update the money from the wallet and the bank.
 */

void* wheel_func(void* args){
	// we give a game object to update values from wheels
	game *gameInfos = (game *)args;

	// static variable assigned to a thread to get the index of each wheel without storing them in the game structure.
	int indexWheel = 0;
	static int wheelNumber = 0;
	// we use the mutex from the barrier to reduce parameters in game structure. This action is only done one time.
	mutex_lock(gameInfos->barrierStop->lock);
	indexWheel = wheelNumber;
	wheelNumber += 1;
	mutex_unlock(gameInfos->barrierStop->lock);

	// static as well to make sure we don't call calculateWin() when initializing the game
	static bool gameStarted = false;

	// structure used to refresh wheels values at a specific rate
	struct timespec waitWheelRotation;
	clock_gettime(CLOCK_MONOTONIC, &waitWheelRotation);

	// loop to change the y value from each wheel
	while (!gameInfos->quit){
		// no race condition here
		if (gameInfos->iStopWheels >= indexWheel){
			// if we wanna stop the wheel and if she's centered
			int testValue = (gameInfos->yWheels[indexWheel] - (object_height*3)/4) % (object_height/9);
			if(testValue == 0){
				sema_post(gameInfos->semaWaitWheels); //Post to indicates the wheels is positionned
				// we wanna make sure this is the last wheel that call calculateWin()
				if (indexWheel == WHEEL_NB -1){
					for(int i = 1; i <= WHEEL_NB; i++){
						sema_wait(gameInfos->semaWaitWheels); //Wait that all wheels are positionned (also the wheel itself)
					}
					 // we also need to check if this is the initialization to skip calling calculateWin()
					if(gameStarted){
						gameInfos->numberOfWinningWheels = calculateWin(gameInfos);
						displayResultAndActualizeGame(gameInfos);
					}
					gameStarted = true;
				}
				// wait until the other wheels are waiting AND the S_KEY is pressed
				sem_barrier_wait(gameInfos->barrierStop);
			}
		}
		// increase of 2 px each 6-indexWheel*2 ms
		waitWheelRotation = wait_until(waitWheelRotation, 6-indexWheel*2);
		gameInfos->yWheels[indexWheel] = (gameInfos->yWheels[indexWheel] + 2)  % (object_height - 2*(object_height/9));
	}
	return NULL;
}

/* function used to raise victory at the end of a game and print the status
 * arg: game* gameInfos -> store yWheels[] used to check the success
 * return: void
 * description: function that calculate the victory or defeat when every wheels are stopped
 *	 the player can win two coins if WHEEL_NB -1 are the same. Or he can win the jackpot if
 *	 every wheels are stopped on the same sign.
 */
int calculateWin(game* gameInfos){
	// deep copy from gameInfos to tmp
	int tmp[WHEEL_NB];
	for(int i = 0; i < WHEEL_NB; i++){
		tmp[i] = gameInfos->yWheels[i];
	}
	// for each wheel, we count the number of same values
	int count = 1;
	for(int i = 0; i < WHEEL_NB; i++){
		if(tmp[i]!=-1){
			for(int j = i + 1; j < WHEEL_NB; j++){
        	    if(tmp[i] == tmp[j]){
			        count++;
				    tmp[j] = -1;
			    }
	    	}
		}
 	}
	return count;
}

/* function used to tell to the player the result of the game and update the coins
 * arg: int count -> the max number of same wheels after they all stoped
 * return: void
 * description: display the result to the player and update the amount of coins
 * 	 from his wallet and from the bank
 */
void displayResultAndActualizeGame(game* gameInfos){
	// display the result of the game
	if(gameInfos->numberOfWinningWheels == WHEEL_NB - 1){
		if(gameInfos->bank >= 2){
			gameInfos->bank -= 2;
			gameInfos->wallet += 2;
			printf("you've just won two coins !\n");
		} else{
			gameInfos->wallet += gameInfos->bank;
			gameInfos->bank = 0;
			printf("you've won the rest of the bank, we have no coins left, sorry...\n");
		}
	} else if(gameInfos->numberOfWinningWheels == WHEEL_NB){
		int coinsWon = floor( (gameInfos->bank / 2) / 2);
		gameInfos->bank -= coinsWon;
		gameInfos->wallet += coinsWon;
		printf("Congratulations ! You've just won half the jackpot: +%d coins !\n", coinsWon);
	} else{
		printf("Nothing won, insert a new coin and try to win up to %d coins !\n", (int)floor((gameInfos->bank / 2) / 2));
	}
	printf("\n");
}

/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le Bandit Manchot réalisé dans le
           | _ _`\|        |          cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Fonction main du programme qui permet
(___)  )\/  \_____/  ~\.   |                de lancer une partie en initialisant
(___) . \   `         `\   |                la strucutre gameInfos et les différents
 (__)-    ,/        (   |  |			    threads utilisés par le programme
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 24/05/2021

*****************************************************************************/

#include "display.h"
#include "wheels.h"
#include "interaction_player.h"

/* Important note on the game:
    -> change WHEELS_NB in one_armed_bandits.h to increase the number of wheels
*/

/* main function used to declare the game structure, create each threads and join them at the end of the game
 * arg: void
 * return: void
 * description: this function is starting the game by declaring its main structure from utilities.h and delcaring
 *	 on thread for the display, on thread from the interactions with the player and on thread for each wheels
 *	 (the number of wheels is in one_armed_bandits.h also)
 */
int main(){

	// verifying the number of wheels is at least 3
	if(WHEEL_NB < 3){
		printf("Major error, the number of wheels must be 3 or more\n");
		return EXIT_FAILURE;
	}
	// array of each y coordinates. Initialized to 0
	int yWheels[WHEEL_NB];
	for (int i = 0; i < WHEEL_NB; i++){
		yWheels[i] = 0;
	}
	sem_barrier barrierStop;
	// we use barrierStop to wait initialization of object_height variable by display_func() that we need in wheels threads
	sem_barrier_init(&barrierStop, 0);

	// we use semaWaitWheels to ensure that all wheels are positionned before check if the player won
	sem_t * semaWaitWheels = sema_create(0);
	// initializing the main structure used in every thread
	game gameInfos = {WALLET_INIT_MONEY, BANK_INIT_MONEY, WHEELS_ALL_STOPPED, &barrierStop, false, yWheels, 0, semaWaitWheels};

	// initializing display and interaction threads but not the wheels because we need object_height first
  	pthread_t pthreadKeyboard;
  	thread_create(&pthreadKeyboard, keyboard_func, &gameInfos);

  	pthread_t pthreadDisplay;
  	thread_create(&pthreadDisplay, display_func, &gameInfos);

	// we wait until object_height is initialized with the correct value
  sem_wait(gameInfos.barrierStop->sem);

	// then, we re-init barrierStop, this time, to stop the wheels untils the player leave the program
	sem_barrier_destroy(&barrierStop);
    sem_barrier_init(&barrierStop, WHEEL_NB + 1); //WHEEL_B + 1 for wheels + keyboard thread

	// initializing wheels threads
  	pthread_t pthreadWheels[WHEEL_NB];
  	for(int i = 0; i < WHEEL_NB; i++){
    	thread_create(&pthreadWheels[i], wheel_func, &gameInfos);
  	}

	// join every thread after the user decided to leave the program
  	thread_join(pthreadKeyboard, NULL);
	thread_join(pthreadDisplay, NULL);
  	for(int i = 0; i < WHEEL_NB; i++){
    	thread_join(pthreadWheels[i], NULL);
  	}
	// destroying fields from the structure
	sem_barrier_destroy(&barrierStop);
	sema_destroy(semaWaitWheels);
	return EXIT_SUCCESS;
}

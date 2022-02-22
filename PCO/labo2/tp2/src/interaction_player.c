/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le Bandit Manchot réalisé dans le
           | _ _`\|        |          cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Fonctions permettant de gerer les
(___)  )\/  \_____/  ~\.   |                interractions entre le joueur et le
(___) . \   `         `\   |                jeu ainsi que de quitter propremment
 (__)-    ,/        (   |  |			    la partie quand le joueur le souhaite
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 24/05/2021

*****************************************************************************/

#include "interaction_player.h"

//Mutex are not necessary because some variables from the structure are only modified in this function

/* thread that manage every interactions from the player and update the game structure given
 * arg: void* args -> need to be convert to game*
 * return: void
 * description: loop that use a switch case to detect on which key the player pressed so we can update the
 *   gameInfo structure that will be use in display_func() and wheel_func(). The most significant part is
 *	 the update of the filed "stop" used in the wheel to detect when we have to stop a wheel, to restart a game
 *	 or to exit him.
 */
void* keyboard_func(void* args){
	game* gameInfos = (game *) args;
	SDL_Event event;
	do{
		// passive waiting on an event
	    SDL_WaitEvent(&event);
 	    switch (event.type){
	  	    case SDL_QUIT: // if SDL_Quit() called (at the end of the display_func() thread)
			  	// call the function to exit the game properly
			  	close_game(gameInfos);
 	  		    break;
	  	    case SDL_WINDOWEVENT: // if windows closed by user
	  		    if (event.window.event==SDL_WINDOWEVENT_CLOSE){
				  	close_game(gameInfos);
				}
				break;
	  	    case SDL_KEYDOWN: // if key pressed
	  		switch(event.key.keysym.sym){
	  			case SDLK_ESCAPE:
				  	// close the game
				  	close_game(gameInfos);
					break;
				case SDLK_SPACE:
	  				wait_key_release();
					// check if we need to stop a wheel
					if(gameInfos->iStopWheels < WHEELS_ALL_STOPPED){
						// update the game structure
						gameInfos->iStopWheels++;
					}
					break;
				case SDLK_s:
 	  				wait_key_release();
					// check if all the weels are stopped
					if(gameInfos->iStopWheels == WHEELS_ALL_STOPPED){
						// check if we are able to start a new game
						if(gameInfos->wallet > 0){
							// reset the count of wheels stopped
							gameInfos->numberOfWinningWheels = 0;
							gameInfos->iStopWheels = WHEELS_ALL_ROTATING;
							// trigger the barrier so the other wheels that were waiting start to rotate
							sem_barrier_wait(gameInfos->barrierStop);
							// update the values from the structure
							gameInfos->wallet--;
							gameInfos->bank++;
							printf("coin introduced, you have %d coin(s) left\n", gameInfos->wallet);
						} else {
							printf("you have no coins left\n");
						}
					} else {
						printf("you are already on a game\n");
					}
				    break;
 	  		}
 	    }
	// we loop until anything that quit the program
   	} while(!gameInfos->quit);
   	return NULL;
}

/* function that close properly the program using the barrier
 * arg: game* gameInfos -> contains the barrier
 * return: void
 * descirption: this function is called whenever the game has to be stoped. Wheels
 *   are maybe waiting on the sem_barrier_wait() function, so we have to send post for each
 *	 wheels stuck so every thread may leave properly and join before terminating the program
 */
void close_game(game* gameInfos){
	// set the flag to true so we quit all threads
	gameInfos->quit = true;
	// foreach wheels stoped, we send a post so they leave their barrier_wait()
	for(int i = 0; i <= gameInfos->iStopWheels; i++){
		sema_post(gameInfos->barrierStop->sem);
	}
}

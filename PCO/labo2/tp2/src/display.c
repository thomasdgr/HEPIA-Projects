/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le Bandit Manchot réalisé dans le
           | _ _`\|        |          cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Fonctions permettant de gerer  
(___)  )\/  \_____/  ~\.   |                l'affichage complet du jeu. Gère la
(___) . \   `         `\   |                pile du joueur, de la banque, du fond
 (__)-    ,/        (   |  |			    et des roues
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 24/05/2021

*****************************************************************************/

#include "display.h"

// the following global variables are defined for graphical objects only:
// the images size is 104x128 pixels
static SDL_Renderer *renderer;
static SDL_Texture *one_arm_texture, *objects_texture, *coin_texture;
static SDL_Rect one_arm_rect, coin_rect;
static SDL_Rect object_rect;
int object_height; // global for convenience

/* thread that manage the entire display from the game
 * arg: void* args -> need to be convert to game*
 * return: void
 * description: to manage display, we must know the number of coins from the player's wallet
 *	 and from the bank but we also need to set the position of each wheels from the yWheels array
 */
void *display_func(void *param){
	game* gameInfos = (game *) param;
	bool status = true;
	
	// set the position of the wheels to match with the background (in pixels)
	int xPositionBeginWheels = 85; 
	int yPositionBeginWheels = 410;

	// set the position of the wallet (in pixels)
	int xPositionBeginWallet = 700;
	int yPositionBeginWallet = 400;

	// set the position of the bank (in pixels)
	int xPositionBeginBank = 700;
	int yPositionBeginBank = 1020;

	// initializing the window that will be filled in the thread
	SDL_Window *window = init_window(gameInfos);
	
	// structure used to refresh display at a specific rate
	struct timespec waitDisplay;
	clock_gettime(CLOCK_MONOTONIC, &waitDisplay);
	
	// loop that refresh by recreating the content of the window every 20ms
	while(!gameInfos->quit){
		
		// we wait at the beggining so we can clear before display
		waitDisplay = wait_until(waitDisplay, 20);
		SDL_RenderClear(renderer);

		// we copy the layout of the game from the file "one_armed_bandits.png"
		SDL_RenderCopy(renderer, one_arm_texture, NULL, &one_arm_rect);
		
		// we create a coin in the player's stack from the game structure
		drawCoins(gameInfos->wallet, xPositionBeginWallet, yPositionBeginWallet);
		
		// same for the bank's stack
		drawCoins(gameInfos->bank, xPositionBeginBank, yPositionBeginBank);

		// same for the wheels by reading the y coordinate for each wheel in the game structure
		drawWheels(xPositionBeginWheels, yPositionBeginWheels, gameInfos->yWheels);
		
		// if the player won the game, we flash the winning wheels until the user quit or start a new game
		if(gameInfos->numberOfWinningWheels >= WHEEL_NB - 1){
			// flashing only 1/2 time
			if(status){
				drawVictoryRectangles(xPositionBeginWheels, yPositionBeginWheels, gameInfos);
			}
			status = !status; 
		}

		// set the content to display
		SDL_RenderPresent(renderer);
	}

	// destroying each texture and the window before exiting properly the program
	SDL_DestroyTexture(objects_texture);
  	SDL_DestroyTexture(one_arm_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return NULL;
}

/* function that initialize the window used during the game
 * arg: game* gameInfos -> the mutex is used to make sure object_height is created before used in wheels threads
 * return: SDL_Window* -> a pointer to the window initialized for the game
 * description: the display is set on a SDL_Window object that has to be create at the beggining of the thread to
 *	 be used. This function separate code we had from the teacher and code we wrote in the thread to manage display
 */
SDL_Window* init_window(game* gameInfos){
	// this part of the code is almost completly given by the teacher
	int one_arm_width, one_arm_height;
	SDL_Window *window;

	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
	
	get_image_file_size("./one_armed_bandit.png", &one_arm_width, &one_arm_height);
	assert((window = SDL_CreateWindow("one_armed_bandit", SDL_WINDOWPOS_UNDEFINED,
	        SDL_WINDOWPOS_UNDEFINED, one_arm_width, one_arm_height, SDL_WINDOW_OPENGL))!=NULL);
	assert((renderer = SDL_CreateRenderer(window, -1, 0))!=NULL);

	// allow transparent mode!
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
	assert((one_arm_texture=create_texture_from_image_file(renderer, "one_armed_bandit.png", &one_arm_rect))!=NULL);
	assert((coin_texture=create_texture_from_image_file(renderer, "coin.png", &coin_rect))!=NULL);

	// create the global texture containing all objects:
	assert((objects_texture=create_texture_from_image_file(renderer, "objects.png", &object_rect))!=NULL);
	
	object_height = object_rect.h;

	//Indicates to the main() the object_height is set so we can initialize wheels threads later
	sem_post(gameInfos->barrierStop->sem);

	return window;
}

/* function that add the coins from a specific stack to the renderer
 * arg: int count -> the number of coins in the stack
	    int xPositionBeginCoins, int yPositionBeginCoins the coordinates to start drawing a coin
 * return: void
 * description: given a specific count from the wallet or the bank with their coordinates, we draw the stack
 *	 that will be display on the main window (defined globally)
 */
void drawCoins(int count, int xPositionBeginCoins, int yPositionBeginCoins){
	for(int i = 0; i < count; i++){
		SDL_Rect coin_rect_pos={xPositionBeginCoins, yPositionBeginCoins-10*i, coin_rect.w, coin_rect.h};
		// copy the new content to the structure that will be display later
		SDL_RenderCopy(renderer, coin_texture, NULL, &coin_rect_pos);
	}
}

/* function that add the wheels to the renderer
 * arg: int xPositionBeginCoins, int yPositionBeginCoins the coordinates to start drawing a coin
	    int* yWheels -> the array that contains the position of each object that need to be display (taken from the structure "game")
 * return: void
 * description: given specific coordinates and the array of positions, the function will draw, in the main window, the wheels (the number
 *	 of wheels is defined in utilities.h)
 */
void drawWheels(int xPositionBeginWheels, int yPositionBeginWheels, int* yWheels){
	// variable to store the size of one wheel
  	int object_max_height = object_rect.h / 9;
	
	// source rectangle of the wheel used in SDL_RenderCopy()
	SDL_Rect dst_rect = object_rect;
	dst_rect.h = object_max_height * 1.5;
	dst_rect.y = yPositionBeginWheels - object_max_height / 2;

	// destination rectangle of the wheel used in SDL_RenderCopy()
	SDL_Rect src_rect;
	src_rect.w = dst_rect.w;
	src_rect.h = dst_rect.h;
	src_rect.x = 0;
	for(int i = 0; i < WHEEL_NB; i++){
		src_rect.y = yWheels[i];
		dst_rect.x = xPositionBeginWheels + object_rect.w * i;
		SDL_RenderCopy(renderer, objects_texture, &src_rect, &dst_rect);
	}
}

/* function that display a white rectangle for each winning wheels at the end of the game
 * arg: int xPositionBeginCoins, int yPositionBeginCoins the coordinates to start drawing a coin
	    game* gameInfos -> Informations of the game
 * return: void
 * description: given specific coordinates and the infos from the game, the function will draw a white rectangle in the main window
 *	 for every winning wheels
 */
void drawVictoryRectangles(int xPositionBeginWheels, int yPositionBeginWheels, game* gameInfos){
	// variable to store the size of one wheel
	int object_max_height = object_rect.h / 9;
	
	// source white rectangle used in SDL_RenderCopy()
	SDL_Rect whiteRectangle = object_rect;
	whiteRectangle.h = object_max_height;
	whiteRectangle.y = yPositionBeginWheels - object_max_height / 2 + object_max_height / 4;
	
	for(int i = 0; i < WHEEL_NB; i++){
		if(isAWinnerWheel(gameInfos, i)){
			whiteRectangle.x = xPositionBeginWheels + object_rect.w * i;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &whiteRectangle);
		}
	}
}

/* function used to know if a wheel is a winner wheel
 * arg: game* gameInfos -> Informations of the game
 * indexWheel -> index of a wheel contained in [0, WHEEL_NB[
 * return: bool
 * <!> We need to be sure the player won before calling this function
 * description: function that take the index of a certain wheel and return true if she is one of the winning wheels
 *    after the end of the game. Otherwise, it return false so we know if we have to identify the wheel when flashing
 *    her with the white rectangle on display.
 */
bool isAWinnerWheel(game* gameInfos, int indexWheel){
	for (int i = 0; i < WHEEL_NB;i ++){
		if(i != indexWheel && gameInfos->yWheels[i] ==  gameInfos->yWheels[indexWheel] && gameInfos->numberOfWinningWheels >= WHEEL_NB - 1){
			return true;
		}
	}
	return false;
}
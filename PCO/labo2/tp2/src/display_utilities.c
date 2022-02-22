/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le Bandit Manchot réalisé dans le
           | _ _`\|        |          cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Fonctions données par le professeur
(___)  )\/  \_____/  ~\.   |                pour créer des objets SDL et faire des 
(___) . \   `         `\   |                délais à partir de la librairie
 (__)-    ,/        (   |  |			    time.h
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 24/05/2021

*****************************************************************************/
#include "display_utilities.h"

typedef long long LL;
static bool img_init=false;

/* get the image size from an image file
 * args: bmp_filename: file name string
 *	     im_width: pointer on returned width
 * 	     im_height: pointer on returned height
 * return: void	
 */
void get_image_file_size(const char *img_filename, int *im_width, int *im_height){
	SDL_Surface *img_surface;
	int img_flags=IMG_INIT_PNG;
		
	if(!img_init){
		img_init=true;
  		if( !( IMG_Init( img_flags ) & img_flags )){
    	  	printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    	  	exit(1);
  		}
  	}
  	assert((img_surface = IMG_Load(img_filename))!=NULL);
	*im_width=img_surface->w;
	*im_height=img_surface->h;
  	SDL_FreeSurface(img_surface);
}

/* create a SDL texture from an image file for the specified renderer
 * args: renderer: pointer on the SDL renderer
 *	     img_filename: file name string
 *	     img_rect: pointer on the image dimmensions
 * return : SDL_Texture created from the image file
 */
SDL_Texture *create_texture_from_image_file(SDL_Renderer *renderer, const char *img_filename, SDL_Rect *img_rect){
	SDL_Surface *img_surface;
	SDL_Texture *texture;
	int img_flags=IMG_INIT_PNG;
		
	if (!img_init){
		img_init=true;
  		if( !( IMG_Init( img_flags ) & img_flags )){
    	  	printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    	  	exit(1);
  		}
  	}
  	img_surface = IMG_Load(img_filename);
  	SDL_GetClipRect(img_surface, img_rect);
	assert((texture = SDL_CreateTextureFromSurface(renderer, img_surface)) != NULL);
	SDL_FreeSurface(img_surface);
  	return texture;
}

/* wait for any key to be released (SDL based function)
 * arg: none
 * return: void
 */
void wait_key_release(){
	SDL_Event event;
	while(1){
		if (SDL_PollEvent(&event))
			if (event.type==SDL_KEYUP)
				break;
	}
}

/* passive waiting from a timestamp for a duration of offset_ms
 * args: time_start: start timestamp. Can be get at first with clock_gettime(CLOCK_MONOTONIC, &time_start)
 *	     offset_ms: duration of the passive waiting [ms]
 * return: the updated timespec that will be use if we call this function again
 */
struct timespec wait_until(struct timespec time_start, unsigned long offset_ms){
	struct timespec current_time, ret_time;
	LL end_ns, delay_ns;
	end_ns = (LL)time_start.tv_sec * (LL)1000000000 + (LL)time_start.tv_nsec + (LL)offset_ms * (LL)1000000;
	ret_time.tv_sec=end_ns/1000000000;
	ret_time.tv_nsec=end_ns-((LL)ret_time.tv_sec*(LL)1000000000);
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	delay_ns=end_ns-((LL)current_time.tv_sec*(LL)1000000000+(LL)current_time.tv_nsec);
	if (delay_ns>0){
		usleep((unsigned long)(delay_ns/1000));
	}
	return ret_time;
}
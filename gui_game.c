#include "gui_sdl_config.h"
#include "gui_game_func.h"

int main(){
    // init
	if (SDL_Init(SDL_INIT_VIDEO) != 0) { 
		printf("error initializing SDL: %s\n", SDL_GetError()); 
	} 

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // creates a window 
	SDL_Window* win = SDL_CreateWindow("Twisted_Fables", 
									SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, 
									WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN); 
    
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // load images
    SDL_Texture* character[CHARACTER_NUM] = {NULL};
    SDL_Texture* plate = NULL;
    SDL_Texture* token[4] = {NULL};
    SDL_Texture* sheet[CHARACTER_NUM] = {NULL};
    SDL_Texture* track = NULL;
    SDL_Texture* card[CARD_TYPE_NUM] = {NULL};
    img_init(win, ren, character, plate, token, sheet, track, card);

    // load title
    SDL_Texture* title = NULL;
    // opening title
    opening(ren, title, win);

    // choosing character
    int32_t selected = 0;
    bool running = true;
    SDL_Event event;
    choose_character(ren, character, running, selected, event);

    // game process

    destroy(title, character, plate, token, sheet, track, card, win, ren);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
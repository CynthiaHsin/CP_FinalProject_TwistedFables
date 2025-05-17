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
    SDL_Texture* title;
    SDL_Texture* character[CHARACTER_NUM];
    SDL_Texture* plate;
    SDL_Texture* token[4];
    SDL_Texture* sheet[CHARACTER_NUM];
    SDL_Texture* track;
    SDL_Texture* card[CARD_TYPE_NUM];
    img_init(win, ren, title, character, plate, token, sheet, track, card);

    // get the size of the image
    int32_t texW, texH = 0;
    SDL_QueryTexture(title, NULL, NULL, &texW, &texH);
    SDL_Rect dst = { WINDOW_WIDTH / 2 - texW / 2, WINDOW_HEIGHT / 2 - texH / 2, texW, texH };
    // opening title
    opening(ren, title, dst);

    // choosing character
    int32_t selected = 0;
    bool running = true;
    SDL_Event event;
    choose_character(ren, character, running, selected, event);

    destroy(title, character, plate, token, sheet, track, card, win, ren);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
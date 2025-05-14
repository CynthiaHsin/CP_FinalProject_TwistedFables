#include "gui_sdl_config.h"
#include "gui_img_data.h"
#include "gui_opening.h"
#include "gui_choose_character.h"

int main(){
    // retutns zero on success else non-zero 
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
    SDL_Texture* image = IMG_LoadTexture(ren, "assets/title.png");
    if (!image) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load charcter image for choose
    SDL_Texture* character[CHARACTER_NUM] = { 
        IMG_LoadTexture(ren, "assets/alice.jpg"),
        IMG_LoadTexture(ren, "assets/kaguya.jpg"),
        IMG_LoadTexture(ren, "assets/mulan.jpg"),
        IMG_LoadTexture(ren, "assets/red_riding_hood.jpg"),
        IMG_LoadTexture(ren, "assets/sleeping_beauty.jpg"),
        IMG_LoadTexture(ren, "assets/snow_white.jpg")
    };

    // get the size of the image
    int32_t texW, texH = 0;
    SDL_QueryTexture(image, NULL, NULL, &texW, &texH);
    SDL_Rect dst = { WINDOW_WIDTH / 2 - texW / 2, WINDOW_HEIGHT / 2 - texH / 2, texW, texH };

    // opening title
    opening(ren, image, dst);

    // choose the character
    int32_t selected = 0;
    bool running = true;
    SDL_Event event;

    // choosing character
    choose_character(ren, character, running, selected, event);

    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
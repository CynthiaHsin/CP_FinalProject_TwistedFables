# include "gui_game.h"

SDL_Window* win;
SDL_Renderer* ren;

// load images
SDL_Texture* title;
SDL_Texture* character[CHARACTER_NUM];
SDL_Texture* plate;
SDL_Texture* token[4];
SDL_Texture* sheet[CHARACTER_NUM];
SDL_Texture* track;
SDL_Texture* basic_card[CARD_TYPE_NUM];
SDL_Texture* card_back;

int32_t gui_game_start(int32_t characters[PLAYER_NUM], int32_t *pMode){
    *pMode= GAMEMODE_1V1;
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
	win = SDL_CreateWindow("Twisted_Fables", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN); 
    
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    img_init(win, ren, character, plate, token, sheet, track, basic_card, card_back);

    // load title
    SDL_Texture* title = NULL;
    // opening title
    opening(ren, title, win);

    // choosing character
    int32_t selected = 0;
    bool running = true;
    SDL_Event event;
    selected= choose_character(ren, character, running, selected, event);
    characters[PLAYER1]= selected;

    return 0;
}

int32_t gui_game_end(){
    destroy(title, character, plate, token, sheet, track, basic_card, card_back, win, ren);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
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
SDL_Texture* rrh_card[CARD_TYPE_NUM];
SDL_Texture* sw_card[CARD_TYPE_NUM];
SDL_Texture* mulan_card[CARD_TYPE_NUM];
SDL_Texture* kaguya_card[CARD_TYPE_NUM];
SDL_Texture* mg_card[CARD_TYPE_NUM];
SDL_Texture* dorothy_card[CARD_TYPE_NUM];

TTF_Font* font_main = NULL;

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

    // init font
    if (TTF_Init() != 0) {
        printf("TTF_Init error: %s\n", TTF_GetError());
        return 1;
    }

    font_main = TTF_OpenFont("assets/fonts/NotoSansTC-ExtraBold.ttf", 16);
    if (!font_main) {
        printf("Failed to load font: %s\n", TTF_GetError());
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
    
    img_init(win, ren, character, &plate, token, sheet, &track, basic_card, &card_back, 
             rrh_card, sw_card, mulan_card, kaguya_card, mg_card, dorothy_card);

    // load title
    SDL_Texture* title = NULL;
    // opening title
    opening(ren, title, win);

    // choosing character
    int32_t selected = 0;
    int32_t character_selected = 0;
    bool running = true;
    SDL_Event event;
    character_selected = choose_character(ren, character, running, selected, event);
    if(character_selected == 1){      characters[PLAYER1] = CHARACTER_RED_RIDING_HOOD; }
    else if(character_selected == 2){ characters[PLAYER1] = CHARACTER_SNOW_WHITE; }
    else if(character_selected == 3){ characters[PLAYER1] = CHARACTER_MULAN; }
    else if(character_selected == 4){ characters[PLAYER1] = CHARACTER_KAGUYA; }
    else if(character_selected == 5){ characters[PLAYER1] = CHARACTER_MATCH_GIRL; }
    else if(character_selected == 6){ characters[PLAYER1] = CHARACTER_DOROTHY; }

    // start game
    game_scene_loop(characters);

    return 0;
}

int32_t gui_game_end(){
    if (font_main) {
        TTF_CloseFont(font_main);
        font_main = NULL;
    }
    TTF_Quit();
    destroy(title, character, plate, token, sheet, track, basic_card, card_back, 
            rrh_card, sw_card, mulan_card, kaguya_card, mg_card, dorothy_card, win, ren);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
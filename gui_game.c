#include "gui_sdl_config.h"
#include "gui_img_data.h"
#include "gui_opening.h"
#include "gui_choose_character.h"
#include "gui_destroy.h"

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
    SDL_Texture* title = IMG_LoadTexture(ren, "assets/title&sheet/title.png");
    if (!title) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load charcter image for choose
    SDL_Texture* character[CHARACTER_NUM] = { 
        IMG_LoadTexture(ren, "assets/character/alice.jpg"),
        IMG_LoadTexture(ren, "assets/character/kaguya.jpg"),
        IMG_LoadTexture(ren, "assets/character/mulan.jpg"),
        IMG_LoadTexture(ren, "assets/character/red_riding_hood.jpg"),
        IMG_LoadTexture(ren, "assets/character/sleeping_beauty.jpg"),
        IMG_LoadTexture(ren, "assets/character/snow_white.jpg")
    };

    // load plate
    SDL_Texture* plate = IMG_LoadTexture(ren, "assets/plate&token&track/plate.png");

    // load tokens
    SDL_Texture* token[4] = {
        IMG_LoadTexture(ren, "assets/plate&token&track/defense_token.png"),
        IMG_LoadTexture(ren, "assets/plate&token&track/epic_token.png"),
        IMG_LoadTexture(ren, "assets/plate&token&track/hp_token.png"),
        IMG_LoadTexture(ren, "assets/plate&token&track/power_token.png")
    };

    // load sheets
    SDL_Texture* sheet[CHARACTER_NUM] = {
        IMG_LoadTexture(ren, "assets/title&sheet/alice_sheet.png"),
        IMG_LoadTexture(ren, "assets/title&sheet/kaguya_sheet.png"),
        IMG_LoadTexture(ren, "assets/title&sheet/mulan_sheet.png"),
        IMG_LoadTexture(ren, "assets/title&sheet/rrh_sheet.png"),
        IMG_LoadTexture(ren, "assets/title&sheet/sb_sheet.png"),
        IMG_LoadTexture(ren, "assets/title&sheet/sw_sheet.png")
    };

    // load track
    SDL_Texture* track = IMG_LoadTexture(ren, "assets/plate&token&track/fight_track.png");

    // load cards
    SDL_Texture* card[CARD_TYPE_NUM] = {
        IMG_LoadTexture(ren, "assets/card/attack1.png"),
        IMG_LoadTexture(ren, "assets/card/attack2.png"),
        IMG_LoadTexture(ren, "assets/card/attack3.png"),
        IMG_LoadTexture(ren, "assets/card/defense1.png"),
        IMG_LoadTexture(ren, "assets/card/defense2.png"),
        IMG_LoadTexture(ren, "assets/card/defense3.png"),
        IMG_LoadTexture(ren, "assets/card/move1.png"),
        IMG_LoadTexture(ren, "assets/card/move2.png"),
        IMG_LoadTexture(ren, "assets/card/move3.png"),
        IMG_LoadTexture(ren, "assets/card/wild.png")
    };

    // get the size of the image
    int32_t texW, texH = 0;
    SDL_QueryTexture(title, NULL, NULL, &texW, &texH);
    SDL_Rect dst = { WINDOW_WIDTH / 2 - texW / 2, WINDOW_HEIGHT / 2 - texH / 2, texW, texH };

    // opening title
    opening(ren, title, dst);

    // choose the character
    int32_t selected = 0;
    bool running = true;
    SDL_Event event;

    // choosing character
    choose_character(ren, character, running, selected, event);

    destroy(title, character, plate, token, sheet, track, card, win, ren);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
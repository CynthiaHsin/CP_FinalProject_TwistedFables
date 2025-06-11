#include "gui_sdl_config.h"

int32_t img_init(SDL_Window* win, SDL_Renderer* ren, SDL_Texture* character[], 
                SDL_Texture* plate, SDL_Texture* token[], SDL_Texture* sheet[], 
                SDL_Texture* track, SDL_Texture* basic_card[], SDL_Texture* card_back){

    // load character
    // character[0] = IMG_LoadTexture(ren, "assets/character/alice.jpg");
    // character[1] = IMG_LoadTexture(ren, "assets/character/kaguya.jpg");
    // character[2] = IMG_LoadTexture(ren, "assets/character/mulan.jpg");
    // character[3] = IMG_LoadTexture(ren, "assets/character/red_riding_hood.jpg");
    // character[4] = IMG_LoadTexture(ren, "assets/character/sleeping_beauty.jpg");
    // character[5] = IMG_LoadTexture(ren, "assets/character/snow_white.jpg");
    character[CHARACTER_RED_RIDING_HOOD] = IMG_LoadTexture(ren, "assets/character/red_riding_hood.png");
    character[CHARACTER_SNOW_WHITE] = IMG_LoadTexture(ren, "assets/character/snow_white.jpg");
    character[CHARACTER_MULAN] = IMG_LoadTexture(ren, "assets/character/mulan.jpg");
    character[CHARACTER_KAGUYA] = IMG_LoadTexture(ren, "assets/character/kaguya.jpg");
    character[CHARACTER_MATCH_GIRL] = IMG_LoadTexture(ren, "assets/character/match_girl.png");
    character[CHARACTER_DOROTHY] = IMG_LoadTexture(ren, "assets/character/dorothy.png");
    for (int i = 1; i < CHARACTER_NUM; i++) {
        if (!character[CHARACTER_RED_RIDING_HOOD] || !character[CHARACTER_SNOW_WHITE] || 
            !character[CHARACTER_MULAN] || !character[CHARACTER_KAGUYA] || 
            !character[CHARACTER_MATCH_GIRL] || !character[CHARACTER_DOROTHY]) {
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load plate
    plate = IMG_LoadTexture(ren, "assets/plate&token&track/plate.png");
    if (!plate) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load token
    token[0] = IMG_LoadTexture(ren, "assets/plate&token&track/defense_token.png");
    token[1] = IMG_LoadTexture(ren, "assets/plate&token&track/epic_token.png");
    token[2] = IMG_LoadTexture(ren, "assets/plate&token&track/hp_token.png");
    token[3] = IMG_LoadTexture(ren, "assets/plate&token&track/power_token.png");
    for (int i = 0; i < 4; i++) {
        if (!token[i]) {
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load sheet
    // sheet[0] = IMG_LoadTexture(ren, "assets/title&sheet/alice_sheet.png");
    // sheet[1] = IMG_LoadTexture(ren, "assets/title&sheet/kaguya_sheet.png");
    // sheet[2] = IMG_LoadTexture(ren, "assets/title&sheet/mulan_sheet.png");
    // sheet[3] = IMG_LoadTexture(ren, "assets/title&sheet/rrh_sheet.png");
    // sheet[4] = IMG_LoadTexture(ren, "assets/title&sheet/sb_sheet.png");
    // sheet[5] = IMG_LoadTexture(ren, "assets/title&sheet/sw_sheet.png");
    sheet[CHARACTER_RED_RIDING_HOOD] = IMG_LoadTexture(ren, "assets/title&sheet/rrh_sheet.png");
    sheet[CHARACTER_SNOW_WHITE] = IMG_LoadTexture(ren, "assets/title&sheet/sw_sheet.png");
    sheet[CHARACTER_MULAN] = IMG_LoadTexture(ren, "assets/title&sheet/mulan_sheet.png");
    sheet[CHARACTER_KAGUYA] = IMG_LoadTexture(ren, "assets/title&sheet/kaguya_sheet.png");
    sheet[CHARACTER_MATCH_GIRL] = IMG_LoadTexture(ren, "assets/title&sheet/match_girl.png");
    sheet[CHARACTER_DOROTHY] = IMG_LoadTexture(ren, "assets/title&sheet/dorothy.png");
    for (int i = 1; i < CHARACTER_NUM; i++) {
        if (!sheet[CHARACTER_RED_RIDING_HOOD] || !sheet[CHARACTER_SNOW_WHITE] || 
            !sheet[CHARACTER_MULAN] || !sheet[CHARACTER_KAGUYA] || 
            !sheet[CHARACTER_MATCH_GIRL] || !sheet[CHARACTER_DOROTHY]) {
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load track
    track = IMG_LoadTexture(ren, "assets/plate&token&track/fight_track.png");
    if (!track) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load card back
    card_back = IMG_LoadTexture(ren, "assets/card/card_back.png");
    if (!card_back) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load card
    basic_card[CARD_BASIC_ATTACK_L1] = IMG_LoadTexture(ren, "assets/card/attack1.png");
    basic_card[CARD_BASIC_ATTACK_L2] = IMG_LoadTexture(ren, "assets/card/attack2.png");
    basic_card[CARD_BASIC_ATTACK_L3] = IMG_LoadTexture(ren, "assets/card/attack3.png");
    basic_card[CARD_BASIC_DEFENSE_L1] = IMG_LoadTexture(ren, "assets/card/defense1.png");
    basic_card[CARD_BASIC_DEFENSE_L2] = IMG_LoadTexture(ren, "assets/card/defense2.png");
    basic_card[CARD_BASIC_DEFENSE_L3] = IMG_LoadTexture(ren, "assets/card/defense3.png");
    basic_card[CARD_BASIC_MOVEMENT_L1] = IMG_LoadTexture(ren, "assets/card/move1.png");
    basic_card[CARD_BASIC_MOVEMENT_L2] = IMG_LoadTexture(ren, "assets/card/move2.png");
    basic_card[CARD_BASIC_MOVEMENT_L3] = IMG_LoadTexture(ren, "assets/card/move3.png");
    basic_card[CARD_BASIC_COMMON] = IMG_LoadTexture(ren, "assets/card/wild.png");
    for (int i = 1; i < 10; i++) {
        if (!basic_card[i]) {
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    return 0;
}
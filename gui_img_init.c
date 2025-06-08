#include "gui_sdl_config.h"

int32_t img_init(SDL_Window* win, SDL_Renderer* ren, SDL_Texture* character[], 
                SDL_Texture* plate, SDL_Texture* token[], SDL_Texture* sheet[], 
                SDL_Texture* track, SDL_Texture* card[]){

    // load character
    character[0] = IMG_LoadTexture(ren, "assets/character/alice.jpg");
    character[1] = IMG_LoadTexture(ren, "assets/character/kaguya.jpg");
    character[2] = IMG_LoadTexture(ren, "assets/character/mulan.jpg");
    character[3] = IMG_LoadTexture(ren, "assets/character/red_riding_hood.jpg");
    character[4] = IMG_LoadTexture(ren, "assets/character/sleeping_beauty.jpg");
    character[5] = IMG_LoadTexture(ren, "assets/character/snow_white.jpg");
    for (int i = 0; i < 6; i++) {
        if (!character[i]) {
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
    sheet[0] = IMG_LoadTexture(ren, "assets/title&sheet/alice_sheet.png");
    sheet[1] = IMG_LoadTexture(ren, "assets/title&sheet/kaguya_sheet.png");
    sheet[2] = IMG_LoadTexture(ren, "assets/title&sheet/mulan_sheet.png");
    sheet[3] = IMG_LoadTexture(ren, "assets/title&sheet/rrh_sheet.png");
    sheet[4] = IMG_LoadTexture(ren, "assets/title&sheet/sb_sheet.png");
    sheet[5] = IMG_LoadTexture(ren, "assets/title&sheet/sw_sheet.png");
    for (int i = 0; i < 6; i++) {
        if (!sheet[i]) {
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

    // load card
    card[0] = IMG_LoadTexture(ren, "assets/card/attack1.png");
    card[1] = IMG_LoadTexture(ren, "assets/card/attack2.png");
    card[2] = IMG_LoadTexture(ren, "assets/card/attack3.png");
    card[3] = IMG_LoadTexture(ren, "assets/card/defense1.png");
    card[4] = IMG_LoadTexture(ren, "assets/card/defense2.png");
    card[5] = IMG_LoadTexture(ren, "assets/card/defense3.png");
    card[6] = IMG_LoadTexture(ren, "assets/card/move1.png");
    card[7] = IMG_LoadTexture(ren, "assets/card/move2.png");
    card[8] = IMG_LoadTexture(ren, "assets/card/move3.png");
    card[9] = IMG_LoadTexture(ren, "assets/card/wild.png");
    for (int i = 0; i < 10; i++) {
        if (!card[i]) {
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
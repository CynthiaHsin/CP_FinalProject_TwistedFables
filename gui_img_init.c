#include "gui_sdl_config.h"

int32_t img_init(SDL_Window* win, SDL_Renderer* ren, SDL_Texture* character[], 
                SDL_Texture* plate, SDL_Texture* token[], SDL_Texture* sheet[], 
                SDL_Texture* track, SDL_Texture* basic_card[], SDL_Texture* card_back, 
                SDL_Texture* rrh_card[], SDL_Texture* sw_card[], SDL_Texture* mulan_card[], 
                SDL_Texture* kaguya_card[], SDL_Texture* mg_card[], SDL_Texture* dorothy_card[]){

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

    // load basic cards
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
    for (int i = 1; i <= CARD_BASIC_COMMON; i++) {
        if (!basic_card[i]) {
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load red riding hood's fable cards
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        char path[64];
        int32_t j = 11; int32_t evo = 135;
        if(i == CARD_SKILL_ATTACK_EVOLUTION_L1 || i == CARD_SKILL_DEFENSE_EVOLUTION_L1 || 
           i == CARD_SKILL_MOVEMENT_EVOLUTION_L1){ 
            snprintf(path, sizeof(path), "assets/card/%d.png", evo);
            rrh_card[i] = IMG_LoadTexture(ren, path);
            evo++;
        }
        else if(i == CARD_SKILL_ATTACK_EVOLUTION_L2 || i == CARD_SKILL_DEFENSE_EVOLUTION_L2 || 
                i == CARD_SKILL_MOVEMENT_EVOLUTION_L2){
            rrh_card[i] = IMG_LoadTexture(ren, "assets/card/138.png");
        }
        else{
            snprintf(path, sizeof(path), "assets/card/%d.png", j);
            rrh_card[i] = IMG_LoadTexture(ren, path);
            j++;
        }
        memset(path, '\0', sizeof(path));
    }
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        if(!rrh_card[i]){
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load snow white's fable cards
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        char path[64];
        int32_t j = 23; int32_t evo = 139;
        if(i == CARD_SKILL_ATTACK_EVOLUTION_L1 || i == CARD_SKILL_DEFENSE_EVOLUTION_L1 || 
           i == CARD_SKILL_MOVEMENT_EVOLUTION_L1){ 
            snprintf(path, sizeof(path), "assets/card/%d.png", evo);
            sw_card[i] = IMG_LoadTexture(ren, path);
            evo++;
        }
        else if(i == CARD_SKILL_ATTACK_EVOLUTION_L2 || i == CARD_SKILL_DEFENSE_EVOLUTION_L2 || 
                i == CARD_SKILL_MOVEMENT_EVOLUTION_L2){
            sw_card[i] = IMG_LoadTexture(ren, "assets/card/142.png");
        }
        else{
            snprintf(path, sizeof(path), "assets/card/%d.png", j);
            sw_card[i] = IMG_LoadTexture(ren, path);
            j++;
        }
        memset(path, '\0', sizeof(path));
    }
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        if(!sw_card[i]){
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load mulan's fable cards
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        char path[64];
        int32_t j = 59; int32_t evo = 151;
        if(i == CARD_SKILL_ATTACK_EVOLUTION_L1 || i == CARD_SKILL_DEFENSE_EVOLUTION_L1 || 
           i == CARD_SKILL_MOVEMENT_EVOLUTION_L1){ 
            snprintf(path, sizeof(path), "assets/card/%d.png", evo);
            mulan_card[i] = IMG_LoadTexture(ren, path);
            evo++;
        }
        else if(i == CARD_SKILL_ATTACK_EVOLUTION_L2 || i == CARD_SKILL_DEFENSE_EVOLUTION_L2 || 
                i == CARD_SKILL_MOVEMENT_EVOLUTION_L2){
            mulan_card[i] = IMG_LoadTexture(ren, "assets/card/154.png");
        }
        else{
            snprintf(path, sizeof(path), "assets/card/%d.png", j);
            mulan_card[i] = IMG_LoadTexture(ren, path);
            j++;
        }
        memset(path, '\0', sizeof(path));
    }
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        if(!mulan_card[i]){
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load kaguya's fable cards
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        char path[64];
        int32_t j = 71; int32_t evo = 155;
        if(i == CARD_SKILL_ATTACK_EVOLUTION_L1 || i == CARD_SKILL_DEFENSE_EVOLUTION_L1 || 
           i == CARD_SKILL_MOVEMENT_EVOLUTION_L1){ 
            snprintf(path, sizeof(path), "assets/card/%d.png", evo);
            kaguya_card[i] = IMG_LoadTexture(ren, path);
            evo++;
        }
        else if(i == CARD_SKILL_ATTACK_EVOLUTION_L2 || i == CARD_SKILL_DEFENSE_EVOLUTION_L2 || 
                i == CARD_SKILL_MOVEMENT_EVOLUTION_L2){
            kaguya_card[i] = IMG_LoadTexture(ren, "assets/card/158.png");
        }
        else{
            snprintf(path, sizeof(path), "assets/card/%d.png", j);
            kaguya_card[i] = IMG_LoadTexture(ren, path);
            j++;
        }
        memset(path, '\0', sizeof(path));
    }
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        if(!kaguya_card[i]){
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // load match girl's fable cards
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        char path[64];
        int32_t j = 95; int32_t evo = 163; int32_t evo2 = 166;
        if(i == CARD_SKILL_ATTACK_EVOLUTION_L1 || i == CARD_SKILL_DEFENSE_EVOLUTION_L1 || 
           i == CARD_SKILL_MOVEMENT_EVOLUTION_L1){ 
            snprintf(path, sizeof(path), "assets/card/%d.png", evo);
            mg_card[i] = IMG_LoadTexture(ren, path);
            evo++;
        }
        else if(i == CARD_SKILL_ATTACK_EVOLUTION_L2 || i == CARD_SKILL_DEFENSE_EVOLUTION_L2 || 
                i == CARD_SKILL_MOVEMENT_EVOLUTION_L2){
            snprintf(path, sizeof(path), "assets/card/%d.png", evo2);
            mg_card[i] = IMG_LoadTexture(ren, path);
            evo2++;
        }
        else{
            snprintf(path, sizeof(path), "assets/card/%d.png", j);
            mg_card[i] = IMG_LoadTexture(ren, path);
            j++;
        }
        memset(path, '\0', sizeof(path));
    }
    mg_card[CARD_MATCH] = IMG_LoadTexture(ren, "assets/card/134.png");
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        if(!rrh_card[i]){
            printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }
    if(!mg_card[CARD_MATCH]){
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load dorothy's fable cards
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        char path[64];
        int32_t j = 107; int32_t evo = 169;
        if(i == CARD_SKILL_ATTACK_EVOLUTION_L1 || i == CARD_SKILL_DEFENSE_EVOLUTION_L1 || 
           i == CARD_SKILL_MOVEMENT_EVOLUTION_L1){ 
            snprintf(path, sizeof(path), "assets/card/%d.png", evo);
            dorothy_card[i] = IMG_LoadTexture(ren, path);
            evo++;
        }
        else if(i == CARD_SKILL_ATTACK_EVOLUTION_L2 || i == CARD_SKILL_DEFENSE_EVOLUTION_L2 || 
                i == CARD_SKILL_MOVEMENT_EVOLUTION_L2){
            dorothy_card[i] = IMG_LoadTexture(ren, "assets/card/172.png");
        }
        else{
            snprintf(path, sizeof(path), "assets/card/%d.png", j);
            dorothy_card[i] = IMG_LoadTexture(ren, path);
            j++;
        }
        memset(path, '\0', sizeof(path));
    }
    for(int i = CARD_SKILL_ATTACK_BASE_L1; i <= CARD_SKILL_FINISH3; i++){
        if(!dorothy_card[i]){
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
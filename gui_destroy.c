#include "gui_sdl_config.h"

int32_t  destroy(SDL_Texture* title, SDL_Texture* character[], SDL_Texture* plate, 
                SDL_Texture* token[], SDL_Texture* sheet[], 
                SDL_Texture* track, SDL_Texture* basic_card[], SDL_Texture* card_back, SDL_Window* win, SDL_Renderer* ren){

    SDL_DestroyTexture(title);

    for (int i = 1; i < CHARACTER_NUM; i++) {
        if (character != NULL) {
            SDL_DestroyTexture(character[i]);
            character[i] = NULL; 
        }
    }

    SDL_DestroyTexture(plate);

    for (int i = 0; i < 4; i++) {
        if (token != NULL) {
            SDL_DestroyTexture(token[i]);
            token[i] = NULL;
        }
    }

    for (int i = 1; i < CHARACTER_NUM; i++) {
        if (sheet != NULL) {
            SDL_DestroyTexture(sheet[i]);
            sheet[i] = NULL;
        }
    }

    SDL_DestroyTexture(track);

    SDL_DestroyTexture(card_back);

    for (int i = 1; i < CARD_TYPE_NUM; i++) {
        if (basic_card != NULL) {
            SDL_DestroyTexture(basic_card[i]);
            basic_card[i] = NULL;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    return 0;
}
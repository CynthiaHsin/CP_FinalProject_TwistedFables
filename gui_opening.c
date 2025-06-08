#include "gui_sdl_config.h"

int32_t opening(SDL_Renderer* ren, SDL_Texture* image, SDL_Rect dst){
    // fade in
    for (int alpha = 0; alpha <= 255; alpha += 5) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_SetTextureAlphaMod(image, alpha);
        SDL_RenderCopy(ren, image, NULL, &dst);
        SDL_RenderPresent(ren);
        SDL_Delay(10); // control the fade in speed
    }

    // stop for 2 seconds
    SDL_Delay(2000);

    // fade out
    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_SetTextureAlphaMod(image, alpha);
        SDL_RenderCopy(ren, image, NULL, &dst);
        SDL_RenderPresent(ren);
        SDL_Delay(10); // control the fade out speed
    }

    return 0;
}
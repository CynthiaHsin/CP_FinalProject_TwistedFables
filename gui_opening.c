#include "gui_sdl_config.h"
#include "gui_img_data.h"

int32_t opening(SDL_Renderer* ren, SDL_Texture* title, SDL_Window* win){
    // load title
    title = IMG_LoadTexture(ren, "assets/title&sheet/title.png");
    if (!title) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // get the size of the title image
    int32_t texW, texH = 0;
    SDL_QueryTexture(title, NULL, NULL, &texW, &texH);
    SDL_Rect dst = { WINDOW_WIDTH / 2 - texW / 2, WINDOW_HEIGHT / 2 - texH / 2, texW, texH };

    // fade in
    for (int alpha = 0; alpha <= 255; alpha += 5) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_SetTextureAlphaMod(title, alpha);
        SDL_RenderCopy(ren, title, NULL, &dst);
        SDL_RenderPresent(ren);
        SDL_Delay(10); // control the fade in speed
    }

    // stop for 2 seconds
    SDL_Delay(2000);

    // fade out
    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_SetTextureAlphaMod(title, alpha);
        SDL_RenderCopy(ren, title, NULL, &dst);
        SDL_RenderPresent(ren);
        SDL_Delay(10); // control the fade out speed
    }

    return 0;
}
#include "gui_sdl_config.h"
#include "gui_img_data.h"

int32_t choose_character(SDL_Renderer* ren, SDL_Texture* character[], bool running, int32_t selected, SDL_Event event){
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:  if (selected % 3 > 0) selected--; break;
                    case SDLK_RIGHT: if (selected % 3 < 2) selected++; break;
                    case SDLK_UP:    if (selected >= 3) selected -= 3; break;
                    case SDLK_DOWN:  if (selected < 3) selected += 3; break;
                    case SDLK_RETURN:
                        printf("You selected image #%d\n", selected + 1);
                        running = false;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        for (int i = 0; i < 6; i++) {
            int row = i / 3, col = i % 3;
            SDL_Rect dst = {
                150 + col * (WINDOW_WIDTH/3 + 40),
                100 + row * (WINDOW_HEIGHT/2 + 40),
                IMG_SIZE,
                IMG_SIZE
            };

            if (i == selected) {
                int scale = IMG_SIZE * SCALE;
                dst.x -= (scale - IMG_SIZE) / 2;
                dst.y -= (scale - IMG_SIZE) / 2;
                dst.w = dst.h = scale;
            }

            SDL_RenderCopy(ren, character[i], NULL, &dst);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    return 0;
}
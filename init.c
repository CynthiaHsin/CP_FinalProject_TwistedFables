#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define IMG_SIZE 150
#define SCALE 1.2

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

	SDL_Window* win = SDL_CreateWindow("Twisted_Fables", // creates a window 
									SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, 
									WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN); 
    
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* image = IMG_LoadTexture(ren, "assets/title.png");
    if (!image) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* character[6] = { // load charcter image for choose
        IMG_LoadTexture(ren, "assets/alice.jpg"),
        IMG_LoadTexture(ren, "assets/kaguya.jpg"),
        IMG_LoadTexture(ren, "assets/mulan.jpg"),
        IMG_LoadTexture(ren, "assets/red_riding_hood.jpg"),
        IMG_LoadTexture(ren, "assets/sleeping_beauty.jpg"),
        IMG_LoadTexture(ren, "assets/snow_white.jpg")
    };

    // get the size of the image
    int32_t texW, texH;
    SDL_QueryTexture(image, NULL, NULL, &texW, &texH);
    SDL_Rect dst = { WINDOW_WIDTH / 2 - texW / 2, WINDOW_HEIGHT / 2 - texH / 2, texW, texH };

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


    // choose the character
    int32_t selected = 0;
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
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
                150 + col * (IMG_SIZE + 40),
                100 + row * (IMG_SIZE + 40),
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


    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
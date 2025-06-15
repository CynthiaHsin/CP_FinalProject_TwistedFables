#include "gui_sdl_config.h"
#include "gui_img_data.h"
#include "game_data.h"
// return the chose character
int32_t choose_character(SDL_Renderer* ren, SDL_Texture* character[], bool running, int32_t selected, SDL_Event event, int32_t enemy_character){
    int32_t enemy = 0;
    if(enemy_character == 1){enemy = 0;}
    else if(enemy_character == 2){ enemy = 1;}
    else if(enemy_character == 5){ enemy = 2;}
    else if(enemy_character == 6){ enemy = 3;}
    else if(enemy_character == 8){ enemy = 4;}
    else if(enemy_character == 9){ enemy = 5;}

    int32_t backup = 0;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                running = false;
                return -1;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:  
                        // if (selected % 3 > 0) selected--; break;
                        backup = selected;
                        do {
                            if (selected % 3 > 0) selected--;
                            else break;
                        } while (selected == enemy && selected != backup);
                        break;
                    case SDLK_RIGHT: 
                        // if (selected % 3 < 2) selected++; break;
                        backup = selected;
                        do {
                            if (selected % 3 < 2) selected++;
                            else break;
                        } while (selected == enemy && selected != backup);
                        break;
                    case SDLK_UP:    
                        // if (selected >= 3) selected -= 3; break;
                        backup = selected;
                        do {
                            if (selected >= 3) selected -= 3;
                            else break;
                        } while (selected == enemy && selected != backup);
                        break;
                    case SDLK_DOWN:  
                        // if (selected < 3) selected += 3; break;
                        backup = selected;
                        do {
                            if (selected < 3) selected += 3;
                            else break;
                        } while (selected == enemy && selected != backup);
                        break;
                    case SDLK_RETURN:
                        if (selected == enemy) {
                            debug_print ("這個角色已被對手選擇，請選別的角色！\n");
                            break;
                        }
                        debug_print ("You selected image #%d\n", selected + 1);
                        running = false;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        int32_t x[3]= {200, WINDOW_WIDTH/2 - IMG_SIZE_X/2, WINDOW_WIDTH - IMG_SIZE_X - 200};
        int32_t y[2]= {(WINDOW_HEIGHT/2-IMG_SIZE_Y/2) - (IMG_SIZE_Y + 40), (WINDOW_HEIGHT/2-IMG_SIZE_Y/2) + (IMG_SIZE_Y + 40)};

        for (int i = 0; i < 6; i++) {
            int row = i / 3, col = i % 3;
            SDL_Rect dst = {
                x[col],
                y[row],
                IMG_SIZE_X,
                IMG_SIZE_Y
            };

            if (i == selected && i != enemy) {
                int scale_x = IMG_SIZE_X * SCALE;
                int scale_y = IMG_SIZE_Y * SCALE;
                dst.x -= (scale_x - IMG_SIZE_X) / 2;
                dst.y -= (scale_y - IMG_SIZE_Y) / 2;
                // dst.w = dst.h = scale;
                dst.w = scale_x;
                dst.h = scale_y;
            }

            if(i == 0){
                SDL_RenderCopy(ren, character[CHARACTER_RED_RIDING_HOOD], NULL, &dst);
                // 如果是敵方角色，加紅色邊框
                if (i == enemy) {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderDrawRect(ren, &dst);
                }
            }
            else if(i == 1){
                SDL_RenderCopy(ren, character[CHARACTER_SNOW_WHITE], NULL, &dst);
                // 如果是敵方角色，加紅色邊框
                if (i == enemy) {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderDrawRect(ren, &dst);
                }
            }
            else if(i == 2){
                SDL_RenderCopy(ren, character[CHARACTER_MULAN], NULL, &dst);
                // 如果是敵方角色，加紅色邊框
                if (i == enemy) {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderDrawRect(ren, &dst);
                }
            }
            else if(i == 3){
                SDL_RenderCopy(ren, character[CHARACTER_KAGUYA], NULL, &dst);
                // 如果是敵方角色，加紅色邊框
                if (i == enemy) {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderDrawRect(ren, &dst);
                }
            }
            else if(i == 4){
                SDL_RenderCopy(ren, character[CHARACTER_MATCH_GIRL], NULL, &dst);
                // 如果是敵方角色，加紅色邊框
                if (i == enemy) {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderDrawRect(ren, &dst);
                }
            }
            else if(i == 5){
                SDL_RenderCopy(ren, character[CHARACTER_DOROTHY], NULL, &dst);
                // 如果是敵方角色，加紅色邊框
                if (i == enemy) {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderDrawRect(ren, &dst);
                }
            }
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    return (selected+1);
}
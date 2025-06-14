# pragma once
# include "gui_sdl_config.h"
# include "gui_img_data.h"

void game_scene_loop(int32_t characters[]);
void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void draw_button_text(SDL_Rect rect, const char* text);
void popup(enum BtnId id, bool upper, int32_t characters[]);
void draw_token_row(SDL_Texture* tex, SDL_Rect rowStart, int tokenCnt, int tokenFilled);
void render_hand(SDL_Renderer* ren, int32_t player, SDL_Texture* card_back, int32_t characters[]);
SDL_Texture* card_data_get_texture(int32_t card_id, int32_t characters[], int32_t player);
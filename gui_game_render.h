# pragma once
# include "gui_sdl_config.h"
# include "gui_img_data.h"
# include "game_data_card.h"

void game_scene_loop(int32_t characters[]);
void draw_board(int32_t characters[]);
void draw_buttons(int32_t characters[]);
bool handle_button_click(SDL_Event* ev, SDL_Point p, int32_t characters[]);
void draw_button_text(SDL_Rect rect, const char* text);
void popup(SDL_Event* ev, enum BtnId id, bool upper, int32_t characters[]);
void render_hand(SDL_Renderer* ren, int32_t player, SDL_Texture* card_back, int32_t characters[]);
SDL_Texture* card_data_get_texture(int32_t card_id, int32_t player);

void draw_stat_text(int x, int y, const char *utf8);
int32_t detect_basic_stack(SDL_Point p);
int32_t detect_skill_stack(SDL_Point p, int32_t player);
bool detect_hand_card_click(SDL_Point p, int32_t player, int* outType);
int detect_discard_card_click(SDL_Point p, sCardData cards[], SDL_Rect rects[], int32_t card_num, int* outType);

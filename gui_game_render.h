# pragma once

void game_scene_loop(int32_t characters[]);
void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void popup(enum BtnId id, bool upper, int32_t characters[]);
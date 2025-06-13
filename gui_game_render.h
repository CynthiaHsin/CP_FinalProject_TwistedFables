# pragma once

void game_scene_loop(int32_t characters[]);
void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void draw_button_text(SDL_Rect rect, const char* text);
void popup(enum BtnId id, bool upper, int32_t characters[]);
void render_player_skills_only(SDL_Renderer* ren, int32_t player, int32_t characters[]);
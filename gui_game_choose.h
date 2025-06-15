# pragma once
# include "game_data_card.h"
# include "gui_sdl_config.h"

void draw_hint(const char *utf8);
int wait_event(SDL_Event *ev) ;

int32_t gui_choose_card (int32_t *pCard_type, sCardData cards[], int32_t card_num, char * text);
int32_t gui_choose_move_direction (char * text);
int32_t gui_choose_des_player (char * text);
int32_t gui_choose_token (int32_t token_use_max, int32_t player, char * text);
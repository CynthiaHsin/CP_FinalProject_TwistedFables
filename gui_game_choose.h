# pragma once
# include "game_data_card.h"

int32_t gui_choose_card (int32_t *pCard_type, sCardData cards[], int32_t card_num, char * text);
int32_t gui_choose_move_direction (char * text);
int32_t gui_choose_des_player (char * text);
int32_t gui_choose_token (int32_t token_use_max, int32_t player, char * text);
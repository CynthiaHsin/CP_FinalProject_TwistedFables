# pragma once
# include "main.h"
# include "game_data_status_dorothy.h"
# define DOROTHY_CARD_IDX_NUM 2

int32_t skill_dorothy (int32_t card_idx[DOROTHY_CARD_IDX_NUM], int32_t defense_throw_idx[3], int32_t defense_throw_num, 
    int32_t movement_evolution1_card_idx[], int32_t movement_evolution1_card_num, int32_t mevement_evolution1_des_direction,
    int32_t player_use, int32_t player_des);

int32_t skill_dorothy_finish (int32_t card_idx, int32_t token, int32_t player_use, int32_t player_des);
int32_t skill_dorothy_action (sGameDataDorothyAction action, int32_t player);
int32_t skill_dorothy_basic (int32_t value, int32_t type, int32_t player);
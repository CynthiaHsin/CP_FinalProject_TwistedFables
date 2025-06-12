# pragma once
# include "main.h"

# define KAGUYA_CARD_IDX_NUM 2

int32_t skill_kaguya (int32_t card_idx[KAGUYA_CARD_IDX_NUM], int32_t skill_move_use_hp_card_idx, int32_t skill_move_evolution_direction, int32_t player_use, int32_t player_des);

int32_t skill_kaguya_finish (int32_t card_idx, int32_t finish3_direction, int32_t player_use, int32_t player_des);
int32_t skill_kaguya_passive_attacked (int32_t delta, int32_t attack_type, int32_t player_attack, int32_t player_attacked);

int32_t skill_kaguya_round_start (int32_t player);
int32_t skill_kaguya_round_clear (int32_t player);
int32_t skill_kaguya_round_end (int32_t player);
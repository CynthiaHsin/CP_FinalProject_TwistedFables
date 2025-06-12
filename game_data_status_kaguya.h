# pragma once
# include "main.h"

int32_t status_kaguya_init();
int32_t status_kaguya_round_start();
int32_t status_kaguya_evolution1_on (int32_t player);
int32_t status_kaguya_use_defense_card_as_attack (int32_t card_idx, int32_t player);
int32_t status_kaguya_use_evolution1_movement (int32_t player);
int32_t status_kaguya_skill_finish1 (int32_t player);
int32_t status_kaguya_skill_finish1_is_on ();
int32_t status_kaguya_skill_finish3 (int32_t player_use, int32_t player_des);
int32_t status_kaguya_skill_finish3_des_get ();

int32_t status_kaguya_skill_area_set (int32_t card_idx, int32_t area);
int32_t status_kaguya_skill_area_get (int32_t card_idx);
# pragma once
# include "main.h"

int32_t evolution2_idx_get (int32_t evolution_type);
int32_t status_red_riding_hood_init();
int32_t status_red_riding_hood_next_round();
int32_t status_red_riding_hood_action (int32_t action[]);
int32_t status_red_riding_hood_get_action_used (int32_t **actions, int32_t *pAction_num);

int32_t status_red_riding_hood_evolution2_on (int32_t evolution_type);
int32_t status_red_riding_hood_evolution2_card_get (int32_t card_storege_idx[3]);
int32_t status_red_riding_hood_evolution2_on_get (int32_t evolution_idx[3]);
int32_t status_red_riding_hood_evolution2_card_set (int32_t card_storege_idx, int32_t evolution_type);
int32_t status_red_riding_hood_evolution2_card_move2hand (int32_t evolution_type);

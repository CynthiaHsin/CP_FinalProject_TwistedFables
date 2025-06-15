# pragma once
# include "game_data.h"

int32_t gui_action_get_card (sCardData cards[], int32_t *pNum, int32_t player, int32_t space, int32_t type_min, int32_t type_max);
int32_t gui_action_get_basic_card (sCardData cards[], int32_t *pNum, int32_t player, int32_t space);
int32_t gui_action_get_skill_card (sCardData cards[], int32_t *pNum, int32_t player, int32_t space);

int32_t gui_action_focus (int32_t player);
int32_t gui_action_use_basic (int32_t player);
int32_t gui_action_use_skill (int32_t player);

int32_t gui_skill_red_riding_hood (int32_t player, int32_t card_idx[], int32_t type[]);
int32_t gui_evolution2_red_riding_hood (int32_t player);
int32_t gui_skill_mulan (int32_t player, int32_t card_idx[], int32_t type[]);
int32_t gui_skill_kaguya (int32_t player, int32_t card_idx[], int32_t type[]);
int32_t gui_skill_dorothy (int32_t player, int32_t card_idx[], int32_t type[]);
int32_t gui_passive_dorothy (int32_t player);
int32_t gui_skill_snow_white (int32_t player, int32_t card_idx[], int32_t type[]);
int32_t gui_skill_match_girl (int32_t player, int32_t card_idx[], int32_t type[]);
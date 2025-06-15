# pragma once

# include "main.h"

# define ACTION_NO_AREA 20

int32_t action_attack (int32_t delta, int32_t area, int32_t player_use, int32_t player_des);
int32_t action_defense (int32_t delta, int32_t player);
int32_t action_move (int32_t delta, int32_t direction, int32_t player);
int32_t action_lose_hp (int32_t delta, int32_t area, int32_t player_use, int32_t player_des);

int32_t action_modefy_power (int32_t delta, int32_t player);
int32_t action_gain_finish (int32_t player);
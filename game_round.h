# pragma once

# include "main.h"
# include "game_data.h"
# include "game_action.h"

# define HAND_CARDS_INIT_FIRST 4
# define HAND_CARDS_ROUND 6

int32_t game_round();

int32_t game_round_start (int32_t mode, int32_t player);
int32_t game_round_clear (int32_t mode, int32_t player);
int32_t game_round_action (int32_t mode, int32_t player);
int32_t game_round_end (int32_t mode, int32_t player);
int32_t game_round_gameend_parse (int32_t mode);
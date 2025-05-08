# pragma once

# include "game_data_card.h"
# include "game_data_player.h"
# include "game_data_deck.h"

int32_t game_data_init (int32_t mode);
int32_t game_data_get_card (sCardData *pCard, int32_t idx);
# pragma once

# include "main.h"
# include "game_data.h"
# include "game_action_basic.h"


// 使用基本牌, cards_idx: 要使用的卡牌編號, card_type: 使用卡牌種類, token_num: 用幾個token（沒有就0）, move_direction: 1 or -1 or 0, player_use: 使用者, player_des: 目標，沒有目標的話就用 PLAYER_ORIGINAL
int32_t game_action_use_basic_card (int32_t cards_idx, int32_t card_type, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des);


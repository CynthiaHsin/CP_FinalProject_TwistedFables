# pragma once

# include "main.h"
# include "game_action_basic.h"
# include "game_action_skill_red_riding_hood.h"
# include "game_action_skill_mulan.h"

// allow 陣列索引值為eAction中的各個動作，陣列儲存值: 1 true(可以執行此動作), 0 flase(不可執行)，目前設計只檢查專注
int32_t game_action_actions_allow (int32_t allow[], int32_t player);

// 玩家 player 購買編號 card_idx 的牌，如果買到剛好能買蛻變牌，會直接自動買好
int32_t game_action_buy_card (int32_t card_idx, int32_t player);

// 玩家 player 執行專注，刪除：手牌中編號card_delete_hand、棄牌堆中編號card_delete_throw的牌
int32_t game_action_focus (int32_t card_delete_hand, int32_t card_delete_throw, int32_t player);

// 使用基本牌, card_idx: 要使用的卡牌編號, card_type: 使用卡牌種類, token_num: 用幾個token（沒有就0）, move_direction: 1 or -1 or 0, player_use: 使用者, player_des: 目標，沒有目標的話就用 PLAYER_ORIGINAL
int32_t game_action_use_basic_card (int32_t card_idx, int32_t card_type, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des);

// 玩家 player 使用技能，技能卡編號 card_idx, token_num: 用幾個token（沒有就0）, move_direction: 1 or -1 or 0, player_use: 使用者, player_des: 目標，沒有目標的話就用 PLAYER_ORIGINAL
int32_t game_action_use_skill_card (int32_t card_idx[], int32_t card_num, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des);
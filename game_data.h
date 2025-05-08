# pragma once

# include "game_data_card.h"
# include "game_data_player.h"
# include "game_data_deck.h"

int32_t game_data_init (int32_t mode);

// 取得「牌編號idx」的資料
int32_t game_data_get_card (sCardData *pCard, int32_t idx);
// 取得「玩家(player)的牌庫頂，第(idx)張牌」的資料
int32_t game_data_get_deck_card (sCardData *pCard, int32_t player, int32_t idx);
// 將「玩家(player)的牌庫頂，第(idx)張牌」移除
int32_t game_data_deck_card_delete (int32_t player, int32_t idx);
// 將「玩家(player)的牌庫頂，第(idx)張牌」抽進手牌
int32_t game_data_deck_card_take (int32_t player, int32_t idx);
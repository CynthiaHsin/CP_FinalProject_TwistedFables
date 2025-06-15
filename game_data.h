# pragma once

# include "game_data_card.h"
# include "game_data_player.h"
# include "game_data_deck.h"
# include "game_data_status.h"
# include "game_data_map.h"

int32_t game_data_init (int32_t mode, int32_t characters[]);

// basic
// 取得「牌編號idx」的資料
int32_t game_data_get_card (sCardData *pCard, int32_t idx);
// 查詢，所有符合條件的牌 (cost條件為小於，其餘為等於)，ORIGINAL or -1 代表不篩選此項，無錯誤回傳符合數量（=*pGet_num）
int32_t game_data_search_cards (sCardData cards[], int32_t *pGet_num, int32_t player, int32_t space, int32_t type, int32_t cost);

// deck
// 取得「玩家(player)的牌庫頂，第(idx)張牌」的資料
int32_t game_data_get_deck_card (sCardData *pCard, int32_t player, int32_t idx);
// 將「玩家(player)的牌庫頂，第(idx)張牌」移除
int32_t game_data_deck_card_delete (int32_t player, int32_t idx);
// 將「玩家(player)的牌庫頂，第(idx)張牌」抽進手牌
int32_t game_data_deck_card_take (int32_t player, int32_t idx);

// player
int32_t game_data_get_player (sPlayerData *pPlayer_data, int32_t player);
int32_t game_data_deck_card_fold (int32_t player, int32_t idx);
int32_t game_data_deck_card_deck (int32_t player, int32_t idx);
# pragma once 

# include "main.h"

typedef struct _sDeckData{
    int32_t cards[CARD_NUM];
    int32_t card_num;
    // cards[card_num-1] 為牌庫頂
} sDeckData;

int32_t deck_data_init (int32_t mode);

int32_t deck_data_refresh (int32_t player);
int32_t deck_data_shuffle (int32_t player);

int32_t deck_data_print (int32_t player);

int32_t deck_data_get_card (sCardData *pCard, int32_t player, int32_t idx);
int32_t deck_data_move_card (int32_t player, int32_t idx, int32_t space);
int32_t deck_data_draw_cards (int32_t player, int32_t num); // 抽 num 張牌進手牌
int32_t deck_data_card_put (int32_t card_idx, int32_t player); // 將牌加入player的牌庫頂
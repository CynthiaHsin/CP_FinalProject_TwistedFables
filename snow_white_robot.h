#pragma once
typedef struct _sSnow_White_Robot{
    int32_t damage;
    int32_t shell;
    int32_t distance;
    int32_t power;
    int32_t poison;
} sSnow_White_Robot;
int32_t snow_white_robot(int *arr, int32_t n, int *best_card,int *best_card_skill,int *best_card_defense,int32_t player_use,int32_t player_des);
int32_t snow_white_process(int *card_idx, int end,int *best_card,int *best_card_skill,int *best_card_defense, int32_t player_use,int32_t player_des);
int32_t snow_white_best_data_cpy (sSnow_White_Robot *best_status, sSnow_White_Robot *status,int32_t len,int32_t *best_card,int32_t *card,int32_t *best_card_defense,int32_t*card_defense,int32_t *best_card_skill,int32_t*card_skill);
int32_t snow_white_buy_card(int32_t player);
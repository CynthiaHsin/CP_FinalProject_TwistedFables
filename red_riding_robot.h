#pragma once
typedef struct _sRed_Riding_Robot{
    int32_t damage;
    int32_t shell;
    int32_t distance;
    int32_t power;
} sRed_Riding_Robot;
int32_t red_riding_robot(int *arr, int32_t n, int *best_card,int *best_card_skill,int *best_card_attack,int *best_card_movement,int32_t *best_card_keep,int32_t player_use,int32_t player_des);
int32_t red_riding_robot_process(int *card_idx, int end,int *best_card,int *best_card_skill,int *best_card_attack,int *best_card_movement,int *best_card_keep, int32_t player_use,int32_t player_des);
int32_t red_riding_best_data_cpy (sRed_Riding_Robot *best_status, sRed_Riding_Robot *status,int32_t len,int32_t *best_card,int32_t *card,int32_t *best_card_attack,int32_t*card_attack,int32_t *best_card_skill,int32_t*card_skill,int32_t *best_card_movement,int32_t*card_movement,int32_t *best_card_keep,int32_t*card_keep);
int32_t red_riding_buy_card(int32_t player);
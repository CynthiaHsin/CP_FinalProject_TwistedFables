# pragma once
# include "main.h"

typedef enum _eSnowWhiteCardIdx{
    Snow_White_CARD_IDX_SKILL= 0,              // 主要技能（用蛻變二也是這裡標蛻變二）
    Snow_White_CARD_IDX_POISON,                // 防禦蛻變二附帶的牌
    Snow_White_CARD_IDX_ATTACH,                // 技能附帶基本牌  
    Snow_White_CARD_IDX_FINISH1,               // 必殺技三的附帶牌，有的話填編號，沒的話-1;
    Snow_White_CARD_IDX_FINISH2,            
    Snow_White_CARD_IDX_FINISH3,
    Snow_White_CARD_IDX_NUM
} eSnowWhiteCardIdx;

typedef struct _sSnowWhite_Status{
    int32_t attack_twist;
    int32_t defense_twist;
    int32_t  movement_twist;
} sSnowWhite_Status;

typedef struct _sStatus{
    int32_t poison;
} sStatus;
int32_t skill_snow_white (int32_t card_idx[Snow_White_CARD_IDX_NUM], int32_t move_direction, int32_t player_use, int32_t player_des);
int32_t skill_snow_white_movement_evolution(int32_t player_use,int32_t move_direction,int32_t delta);
int32_t snow_white_poison ( int32_t player_des,int32_t idx );
int32_t snow_white_poison_count(int32_t *card, int32_t len, int32_t player_des);
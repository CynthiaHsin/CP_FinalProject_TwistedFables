# pragma once
# include "main.h"

typedef enum _eRedRidingHoodCardIdx{
    RED_RIDING_HOOD_CARD_IDX_SKILL= 0,              // 主要技能（用蛻變二也是這裡標蛻變二）
    RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION,      // 攻擊蛻變一效果附帶牌
    RED_RIDING_HOOD_CARD_IDX_MOVEMENT_EVOLUTION,    // 移動蛻變一效果附帶牌
    RED_RIDING_HOOD_CARD_IDX_EVOLUTION2,            // 任一蛻變二效果附帶牌
    RED_RIDING_HOOD_CARD_IDX_ATTACH,                // 技能附帶基本牌
    RED_RIDING_HOOD_CARD_IDX_NUM
} eRedRidingHoodCardIdx;

int32_t skill_red_riding_hood (int32_t card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t player_des);
int32_t skill_red_riding_hood_attack_evolution (int32_t card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t player_des, int32_t attack_area);
int32_t skill_red_riding_hood_movement_evolution (int32_t card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t token_num);
int32_t skill_red_riding_hood_evolution2 (int32_t evolution_type);
int32_t skill_red_riding_hood_finish (int32_t finish_card_idx, int32_t finish1_skill_type[2], int32_t finish2_card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t finish3_delta, int32_t player_use, int32_t player_des);
int32_t skill_red_riding_hood_finish1 (int32_t finish1_skill_type[2], int32_t player_use);
int32_t skill_red_riding_hood_finish2 (int32_t finish2_card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t player_des);
int32_t skill_red_riding_hood_finish3 (int32_t finish3_delta, int32_t player_use, int32_t player_des);

int32_t skill_red_riding_hood_round_start (int32_t player);
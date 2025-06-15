# pragma once
# include "main.h"

typedef enum _eMatchGirlCardIdx{
    Match_Girl_CARD_IDX_SKILL= 0,              // 主要技能（用蛻變二也是這裡標蛻變二）
    Match_Girl_POWER_NUM_ATTACK,                // 攻擊技能決定要帶多少能量，如果要加一攻擊就帶3
    Match_Girl_HP_NUM_DEFENSE,                  //防禦技能選擇失去多少血來抽牌，最高依牌的等級
    Match_Girl_CARD_IDX_ATTACH,                // 技能附帶基本牌  
    Match_Girl_CARD_IDX_NUM
} eMatchGirlCardIdx;



int32_t skill_match_girl (int32_t card_idx[Match_Girl_CARD_IDX_NUM],  int32_t player_use, int32_t player_des);
int32_t skill_match_girl_movement_evolution(int32_t damage,int32_t player_des,int32_t move_direction);
int32_t match_girl_match ( int32_t player_des,int32_t idx );
int32_t skill_match_girl_attack_evolution(int32_t player_des);
int32_t skill_match_girl_evolution2(int32_t player_des);

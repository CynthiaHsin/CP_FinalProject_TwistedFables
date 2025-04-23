# pragma once

# include <stdio.h>
# include <stdint.h>

typedef enum _eCard {
    // 基本牌 - 攻擊、防禦、移動 三種，每種分為 1、2、3 級
    CARD_BASIC_ATTACK_L1 = 0,       // 攻擊牌 - 一級
    CARD_BASIC_ATTACK_L2,           // 攻擊牌 - 二級
    CARD_BASIC_ATTACK_L3,           // 攻擊牌 - 三級
    CARD_BASIC_DEFENSE_L1,          // 防禦牌 - 一級
    CARD_BASIC_DEFENSE_L2,          // 防禦牌 - 二級
    CARD_BASIC_DEFENSE_L3,          // 防禦牌 - 三級
    CARD_BASIC_MOVEMENT_L1,         // 移動牌 - 一級
    CARD_BASIC_MOVEMENT_L2,         // 移動牌 - 二級
    CARD_BASIC_MOVEMENT_L3,         // 移動牌 - 三級

    // 通用牌 - 只有一種
    CARD_COMMON,                    // 通用牌

    // 技能牌 - 以之前的技能為基礎
    CARD_SKILL_ATTACK_BASE_L1,          // 攻擊 一級技能
    CARD_SKILL_ATTACK_BASE_L2,          // 攻擊 二級技能
    CARD_SKILL_ATTACK_EVOLUTION_L1,     // 攻擊 蛻變一
    CARD_SKILL_ATTACK_BASE_L3,          // 攻擊 三級技能
    CARD_SKILL_ATTACK_EVOLUTION_L2,     // 攻擊 蛻變二

    CARD_SKILL_DEFENSE_BASE_L1,         // 防禦 一級技能
    CARD_SKILL_DEFENSE_BASE_L2,         // 防禦 二級技能
    CARD_SKILL_DEFENSE_EVOLUTION_L1,    // 防禦 蛻變一
    CARD_SKILL_DEFENSE_BASE_L3,         // 防禦 三級技能
    CARD_SKILL_DEFENSE_EVOLUTION_L2,    // 防禦 蛻變二

    CARD_SKILL_MOVEMENT_BASE_L1,        // 移動 一級技能
    CARD_SKILL_MOVEMENT_BASE_L2,        // 移動 二級技能
    CARD_SKILL_MOVEMENT_EVOLUTION_L1,   // 移動 蛻變一
    CARD_SKILL_MOVEMENT_BASE_L3,        // 移動 三級技能
    CARD_SKILL_MOVEMENT_EVOLUTION_L2,   // 移動 蛻變二

    // 必殺技牌
    CARD_SKILL_FINISH1,          // 必殺技 1
    CARD_SKILL_FINISH2,          // 必殺技 2
    CARD_SKILL_FINISH3           // 必殺技 3
} eCard;

typedef enum _eCharacter {
    CHARACTER_RED_RIDING_HOOD = 0,      // 小紅帽
    CHARACTER_SNOW_WHITE,               // 白雪公主
    CHARACTER_SLEEPING_BEAUTY,          // 睡美人
    CHARACTER_ALICE,                    // 愛麗絲
    CHARACTER_MULAN,                    // 花木蘭
    CHARACTER_KAGUYA,                   // 輝夜姬
    CHARACTER_LITTLE_MERMAID,           // 美人魚
    CHARACTER_MATCH_GIRL,               // 火柴女孩
    CHARACTER_DOROTHY,                  // 桃樂絲
    CHARACTER_SCHEHERAZADE              // 山魯佐德
} eCharacter;

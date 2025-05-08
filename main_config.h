# pragma once

# include <stdio.h>
# include <stdint.h>

# define CARD_TYPE_NAME_MAX 60
typedef enum _eCardType {
    CARD_ORIGINAL = -1,
    CARD_UNDEFINED = 0,

    // 基本牌 - 攻擊、防禦、移動 三種，每種分為 1、2、3 級
    CARD_BASIC_ATTACK_L1,       // 攻擊牌 - 一級
    CARD_BASIC_ATTACK_L2,           // 攻擊牌 - 二級
    CARD_BASIC_ATTACK_L3,           // 攻擊牌 - 三級
    CARD_BASIC_DEFENSE_L1,          // 防禦牌 - 一級
    CARD_BASIC_DEFENSE_L2,          // 防禦牌 - 二級
    CARD_BASIC_DEFENSE_L3,          // 防禦牌 - 三級
    CARD_BASIC_MOVEMENT_L1,         // 移動牌 - 一級
    CARD_BASIC_MOVEMENT_L2,         // 移動牌 - 二級
    CARD_BASIC_MOVEMENT_L3,         // 移動牌 - 三級

    // 通用牌 - 只有一種
    CARD_BASIC_COMMON,              // 通用牌

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
    CARD_SKILL_FINISH3,          // 必殺技 3

    // 特殊牌
    CARD_POISON_L1,              // 白雪公主中毒牌 一級
    CARD_POISON_L2,              // 白雪公主中毒牌 二級
    CARD_POISON_L3,              // 白雪公主中毒牌 三級
    CARD_MATCH,                  // 火柴女孩火柴牌

    CARD_TYPE_NUM                // 標記不同卡的數量 
} eCardType;


# define CARD_SPACE_NAME_MAX 30
typedef enum _eCardSpace{

    CARD_SPACE_HAND,        // 手牌
    CARD_SPACE_DECK,        // 牌庫
    CARD_SPACE_DECK_MATCH,  // 牌庫：火柴
    CARD_SPACE_DECK_POISON, // 牌庫：毒
    CARD_SPACE_THROW,       // 棄牌堆
    CARD_SPACE_USE,         // 出牌堆
    CARD_SPACE_SHOP,        // 購牌區
    CARD_SPACE_DELETE       // 移除

} eCardSpace;

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

typedef enum _eGAMEMODE{
    GAMEMODE_1V1,
} eGAMEMODE;

typedef enum _ePlayer{
    PLAYER_ORIGINAL = -1,
    PLAYER_UNDEFINED = 0,
    PLAYER1, // A-1
    PLAYER2, // B-1
    PLAYER3, // A-2
    PLAYER4, // B-2
    PLAYER_NUM // will be 5 ()
} ePlayer;
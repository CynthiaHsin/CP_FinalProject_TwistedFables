# pragma once
# include "main.h"

# define MULAN_CARD_IDX_NUM 2

typedef enum _eMulanActionIdx{
    MULAN_ACTION_IDX_THROW_DES,
    MULAN_ACTION_IDX_ATTACK_MOVE,
    MULAN_ACTION_IDX_ATTACK_EVOLUTION_TOKEN,
    MULAN_ACTION_IDX_DEFENSE_PULL,
    MULAN_ACTION_IDX_NUM
} eMulanActionIdx;

int32_t skill_mulan_throw_des_card (int32_t player_des);
int32_t skill_mulan_token_use (int32_t card_type, int32_t token, int32_t player);

int32_t skill_mulan (int32_t card_idx[MULAN_CARD_IDX_NUM], int32_t mulan_action[MULAN_ACTION_IDX_NUM], int32_t player_use, int32_t player_des);
int32_t skill_mulan_evolution1 (int32_t token, int32_t player); // return max use token (used)

// finish2_direction: 移動到目標的 -1(左) or 1(右)
int32_t skill_mulan_finish (int32_t card_idx, int32_t finish2_direction, int32_t player_use, int32_t player_des);

// return 減少多少傷害(>=0)
int32_t skill_mulan_passive_attacked (int32_t attack_delta, int32_t player);

int32_t skill_mulan_round_start (int32_t player);
// 沒有用到：defense_pull_token<=0, card_idx=CARD_ORIGINAL
int32_t skill_mulan_round_end (int32_t defense_pull_token, int32_t defense_evolution1_card_idx_throw, int32_t player);

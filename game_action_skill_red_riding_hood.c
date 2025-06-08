# include "game_action_skill_red_riding_hood.h"
# include "game_data.h"
# include "game_action.h"

# define CARD_IDX_ATTACK_EVOLUTION 1
# define CARD_IDX_MOVEMENT_EVOLUTION 2
# define CARD_IDX_EVOLUTION2 3

// card0: main skill, card1: attack evolution, card2: movement evolution, card3: evolution 2, for no card use: -1
int32_t skill_red_riding_hood (int32_t card_idx[4],  int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des){
    sCardData card_data;
    card_data_get(&card_data, card_idx[0]);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    // eCardType
    int32_t attack_area = skill_red_riding_hood_movement_evolution(card_idx, player_use, 1);
    switch (card_data.type) {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
            int32_t level = card_data_get_level(card_data.type);
            attack_area += level;
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
            card_data_set (card_data.index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            if (skill_red_riding_hood_attack_evolution(card_idx, player_use, player_des, attack_area) < 0) {
                return -1;
            }
            break;
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
            card_data_set (card_data.index, 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
            // not yet
            break;
    }
}

int32_t skill_red_riding_hood_attack_evolution (int32_t card_idx[4], int32_t player_use, int32_t player_des, int32_t attack_area){
    if (card_idx[CARD_IDX_ATTACK_EVOLUTION] == -1) {
        return 0;
    }
    sCardData card_data;
    card_data_get(&card_data, card_idx[CARD_IDX_ATTACK_EVOLUTION]);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    if (player_data_use.card_on[card_data_get_index(player_use, CARD_SKILL_ATTACK_EVOLUTION_L1)] == 1) {
        if (card_data_is_skill(card_data.index)){
            int32_t level= card_data_get_level(card_data.type);
            if (card_data.space != CARD_SPACE_HAND){
                debug_print("error: card (%d) is not in hand\n", card_data.index);
                return -1;
            }
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
        }else{
            debug_print("error: card (%d) is not a skill card\n", card_data.index);
            return -1;
        }
    }else{
        debug_print("error: player (%d) does not have the skill card [CARD_SKILL_ATTACK_EVOLUTION_L1]\n", player_use);
        return -1;
    }
    return 0;
}

int32_t skill_red_riding_hood_movement_evolution (int32_t card_idx[4], int32_t player_use, int32_t attack_area){
    if (card_idx[CARD_IDX_MOVEMENT_EVOLUTION] == -1) {
        return 0;
    }
    sCardData card_data;
    card_data_get(&card_data, card_idx[CARD_IDX_MOVEMENT_EVOLUTION]);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    if (player_data_use.card_on[card_data_get_index(player_use, CARD_SKILL_MOVEMENT_EVOLUTION_L1)] == 1) {
        if (card_data_is_skill(card_data.index)){
            int32_t level= card_data_get_level(card_data.type);
            attack_area += level;
        }else{
            debug_print("error: card (%d) is not a skill card\n", card_data.index);
            return -1;
        }
    }else{
        debug_print("error: player (%d) does not have the skill card [CARD_SKILL_MOVEMENT_EVOLUTION_L1]\n", player_use);
        return -1;
    }
    return attack_area;
}
# include "game_data_status_red_riding_hood.h"
# include "game_data_card.h"
# include "game_action_skill_red_riding_hood.h"
# define EVOLUTION_MAX 3
# define ROUND_ACTION_MAX 100
int32_t evolution2_storege_card[EVOLUTION_MAX]= {0};
int32_t evolution2_storege_on[EVOLUTION_MAX]= {0};
int32_t round_skill[ROUND_ACTION_MAX][RED_RIDING_HOOD_CARD_IDX_NUM]= {0};
int32_t round_actions= 0;

int32_t evolution2_idx_get (int32_t evolution_type){
    if (evolution_type == CARD_SKILL_ATTACK_EVOLUTION_L2) return 0;
    if (evolution_type == CARD_SKILL_DEFENSE_EVOLUTION_L2) return 1;
    if (evolution_type == CARD_SKILL_MOVEMENT_EVOLUTION_L2) return 2;
    return -1;
}

int32_t status_red_riding_hood_init(){
    for (int32_t i=0; i<EVOLUTION_MAX; i++){
        evolution2_storege_card[i]= -1;
        evolution2_storege_on[i]= 0;
    }
    for (int32_t i=0; i<ROUND_ACTION_MAX; i++){
        for (int32_t j=0; j<RED_RIDING_HOOD_CARD_IDX_NUM; j++){
            round_skill[i][j]= -1;
        }
    }
}

int32_t status_red_riding_hood_next_round(){
    for (int32_t i=0; i<round_actions; i++){
        for (int32_t j=0; j<RED_RIDING_HOOD_CARD_IDX_NUM; j++){
            round_skill[i][j]= -1;
        }
    }
    round_actions= 0;
    return 0;
}

int32_t status_red_riding_hood_action (int32_t action[RED_RIDING_HOOD_CARD_IDX_NUM]){
    for (int32_t j=0; j<RED_RIDING_HOOD_CARD_IDX_NUM; j++) round_skill[round_actions][j]= action[j];
    round_actions++;
    return 0;
}

int32_t status_red_riding_hood_get_action_used (int32_t **actions, int32_t *pAction_num){
    *pAction_num= round_actions;
    for (int32_t i=0; i<round_actions; i++){
        for (int32_t j=0; j<RED_RIDING_HOOD_CARD_IDX_NUM; j++){
            actions[i][j]= round_skill[i][j];
        }
    }
    return 0;
}

int32_t status_red_riding_hood_evolution2_on (int32_t evolution_type){
    int32_t evo_idx= evolution2_idx_get(evolution_type);
    if (evo_idx<0) return -1;
    evolution2_storege_on[evo_idx]= 1;
    return 0;
}

int32_t status_red_riding_hood_evolution2_card_get (int32_t card_storege_idx[EVOLUTION_MAX]){
    for (int32_t i=0; i<EVOLUTION_MAX; i++){
        card_storege_idx[i]= evolution2_storege_card[i];
    }
    return 0;
}

int32_t status_red_riding_hood_evolution2_on_get (int32_t evolution_idx[EVOLUTION_MAX]){
    for (int32_t i=0; i<EVOLUTION_MAX; i++){
        evolution_idx[i]= evolution2_storege_on[i];
    }
    return 0;
}

int32_t status_red_riding_hood_evolution2_card_set (int32_t card_storege_idx, int32_t evolution_type){
    sCardData card_data;
    card_data_get(&card_data, card_storege_idx);
    if (card_data.space!=CARD_SPACE_HAND) return -1;
    int32_t evo_idx= evolution2_idx_get(evolution_type);
    if (evo_idx<0 || evolution2_storege_on[evo_idx]==0) return -1;
    evolution2_storege_card[evo_idx]= card_storege_idx;
    card_data_set (card_storege_idx, 1, CARD_SPACE_SKILL, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

int32_t status_red_riding_hood_evolution2_card_move2hand (int32_t evolution_type){
    int32_t evo_idx= evolution2_idx_get(evolution_type);
    if (evo_idx<0 || evolution2_storege_on[evo_idx]==0 || evolution2_storege_card[evo_idx]<0) return -1;
    card_data_set (evolution2_storege_card[evo_idx], 1, CARD_SPACE_HAND, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}
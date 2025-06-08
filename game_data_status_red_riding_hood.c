# include "game_data_status_red_riding_hood.h"
# include "game_data_card.h"
# define EVOLUTION_MAX 3

int32_t evolution2_storege_card[EVOLUTION_MAX]= {0};
int32_t evolution2_storege_on[EVOLUTION_MAX]= {0};

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
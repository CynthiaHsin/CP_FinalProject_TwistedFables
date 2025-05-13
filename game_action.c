# include "main.h"
# include "game_data.h"
# include "game_action.h"

// allow 陣列索引值為eAction中的各個動作，陣列儲存值: 1 true(可以執行此動作), 0 flase(不可執行)，目前設計只檢查專注
int32_t game_action_actions_allow (int32_t allow[], int32_t player){
    sStatusData status;
    status_data_get (&status);
    for (int32_t i=ACTION_UNDEFINED; i<ACTION_NUM; i++){
        allow[i]= 1;
    }

    // 檢查：專注
    if (status.actions_num[player]) allow[ACTION_FOCUS]= 0;
    
}

int32_t game_action_use_basic_card (int32_t cards_idx, int32_t card_type, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des){

    sCardData card;
    card_data_get (&card, cards_idx);
    if (card.type!=CARD_BASIC_COMMON && card.type!=card_type){
        debug_print ("error: diferent type of the card (%d), input: %d, real: %d", cards_idx, card_type, card.type);
        return -1;
    }
    int32_t level= 0;
    switch (card_type){
        case CARD_BASIC_ATTACK_L1:
        case CARD_BASIC_ATTACK_L2:
        case CARD_BASIC_ATTACK_L3:
            level= card_type - CARD_BASIC_ATTACK_L1 + 1;
            action_attack (level, 1, player_use, player_des);
            break;

        case CARD_BASIC_DEFENSE_L1:
        case CARD_BASIC_DEFENSE_L2:
        case CARD_BASIC_DEFENSE_L3:
            level= card_type - CARD_BASIC_DEFENSE_L1 + 1;
            action_defense (level, player_use);
            break;

        case CARD_BASIC_MOVEMENT_L1:
        case CARD_BASIC_MOVEMENT_L2:
        case CARD_BASIC_MOVEMENT_L3: 
            level= card_type - CARD_BASIC_MOVEMENT_L1 + 1;
            action_move(level, move_direction, player_use);
            break;
    }
    action_modefy_power (level, player_use);
    
    card_data_set (cards_idx, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

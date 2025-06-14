# include "main.h"
# include "game_data.h"
# include "game_action.h"

int32_t game_action_actions_allow (int32_t allow[], int32_t player){
    sStatusData status;
    status_data_get (&status);
    for (int32_t i=ACTION_UNDEFINED; i<ACTION_NUM; i++){
        allow[i]= 1;
    }

    // 檢查：專注
    if (status.actions_num[player]) allow[ACTION_FOCUS]= 0;
    
    // 檢查：買牌
    if (status.actions_num[player]) allow[ACTION_BUY] = 0;
}

int32_t game_action_buy_card (int32_t card_idx, int32_t player){
    
    sCardData card;
    card_data_get (&card, card_idx);
    sPlayerData player_data;
    player_data_get (&player_data, player);

    sStatusData st;  status_data_get(&st);
    if (st.actions_num[player]) {
        debug_print("already bought this turn\n");
        return -1;
    }
    
    // ensure correct card
    if (card.space==CARD_SPACE_DELETE){
        debug_print ("error: card (%d) has been deleted\n", card_idx);
    }
    
    // ensure enough power
    if (player_data.power < card.cost){
        debug_print ("error: power not enough: %d/%d\n", player_data.power, card.cost);
        return -1;
    }

    // ensure is the only finish card
    if (card.type>=CARD_SKILL_FINISH1 && card.type<=CARD_SKILL_FINISH3){
        sCardData cards[3];
        int32_t n= 0;
        game_data_search_cards (cards, &n, player, CARD_SPACE_ORIGINAL, CARD_SKILL_FINISH1, CARD_COST_ORIGINAL);
        game_data_search_cards (cards+1, &n, player, CARD_SPACE_ORIGINAL, CARD_SKILL_FINISH2, CARD_COST_ORIGINAL);
        game_data_search_cards (cards+2, &n, player, CARD_SPACE_ORIGINAL, CARD_SKILL_FINISH3, CARD_COST_ORIGINAL);
        for (int32_t i=0; i<3; i++){
            if (cards[i].index==card_idx) continue;
            if (cards[i].space != CARD_SPACE_SHOP) continue;
            card_data_set (cards[i].index, 1, CARD_SPACE_DELETE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        }
    }


    player_data.power-= card.cost;
    card_data_set (card.index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
    // player_data_set (player, player_data);
    player_data_write_back(player, player_data); 

    if (card_idx+1 >= CARD_NUM) return 0;
    if (card.type<CARD_SKILL_ATTACK_BASE_L1 || card.type>CARD_SKILL_MOVEMENT_EVOLUTION_L2) return 0;
    sCardData card_next;
    card_data_get (&card_next, card_idx+1);
    if (card_next.type==CARD_UNDEFINED) return 0;
    switch (card_next.type){
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
            if (player_data.character==CHARACTER_RED_RIDING_HOOD){
                card_data_set (card_next.index, 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
                status_red_riding_hood_evolution2_on (card_next.type);
                break;
            }
            card_data_set (card_next.index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
            break;
        default:
            break;
    }
    return 0;
}

int32_t game_action_focus (int32_t card_delete_hand, int32_t card_delete_throw, int32_t player){
    
    // type check
    int32_t allow[CARD_TYPE_NUM];
    game_action_actions_allow (allow, player);
    if (allow[ACTION_FOCUS]==0){
        debug_print ("error: not allow to do focus\n");
        return -1;
    }
    sCardData card;
    card_data_get (&card, card_delete_hand);
    if (card.space!=CARD_SPACE_HAND){
        debug_print ("error: card (%d) is not in hand\n", card.index);
        return -1;
    }
    card_data_get (&card, card_delete_hand);
    if (card.space!=CARD_SPACE_THROW){
        debug_print ("error: card (%d) is not in throw\n", card.index);
        return -1;
    }

    // delete
    card_data_set (card_delete_hand, 1, CARD_SPACE_DELETE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    card_data_set (card_delete_throw, 1, CARD_SPACE_DELETE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

int32_t game_action_use_basic_card (int32_t card_idx, int32_t card_type, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des){

    sCardData card;
    card_data_get (&card, card_idx);
    if (card.type!=CARD_BASIC_COMMON && card.type!=card_type){
        debug_print ("error: diferent type of the card (%d), input: %d, real: %d\n", card_idx, card_type, card.type);
        return -1;
    }
    sPlayerData player_data;
    player_data_get (&player_data, player_use);
    int32_t level= 0;
    switch (card_type){
        case CARD_BASIC_ATTACK_L1:
        case CARD_BASIC_ATTACK_L2:
        case CARD_BASIC_ATTACK_L3:
            level= card_type - CARD_BASIC_ATTACK_L1 + 1;
            action_attack (level, 1, player_use, player_des);
            if (player_data.character == CHARACTER_DOROTHY){
                skill_dorothy_basic (level, CARD_BASIC_ATTACK_L1, player_use);
            }
            break;

        case CARD_BASIC_DEFENSE_L1:
        case CARD_BASIC_DEFENSE_L2:
        case CARD_BASIC_DEFENSE_L3:
            level= card_type - CARD_BASIC_DEFENSE_L1 + 1;
            action_defense (level, player_use);
            if (player_data.character == CHARACTER_DOROTHY){
                skill_dorothy_basic (level, CARD_BASIC_DEFENSE_L1, player_use);
            }
            break;

        case CARD_BASIC_MOVEMENT_L1:
        case CARD_BASIC_MOVEMENT_L2:
        case CARD_BASIC_MOVEMENT_L3: 
            level= card_type - CARD_BASIC_MOVEMENT_L1 + 1;
            action_move(level, move_direction, player_use);
            if (player_data.character == CHARACTER_DOROTHY){
                skill_dorothy_basic (level, CARD_BASIC_MOVEMENT_L1, player_use);
            }
            break;
    }
    action_modefy_power (level, player_use);

    card_data_set (card_idx, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

int32_t game_action_use_skill_card (int32_t card_idx[], int32_t card_num, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des){
    
    sPlayerData player_data_use;
    player_data_get (&player_data_use, player_use);
    sPlayerData player_data_des;
    player_data_get (&player_data_des, player_des);

    switch (player_data_use.character){
        case CHARACTER_RED_RIDING_HOOD:
            // 小紅帽
            if (skill_red_riding_hood(card_idx, player_use, player_des) < 0) {
                debug_print ("error: skill_red_riding_hood failed\n");
                return -1;
            }
            break;
        case CHARACTER_SNOW_WHITE:
            // 白雪公主
            break;
        case CHARACTER_SLEEPING_BEAUTY:
            // 睡美人
            break;
        case CHARACTER_ALICE:
            // 愛麗絲
            break;
        case CHARACTER_MULAN:
            // 花木蘭
            break;
        case CHARACTER_KAGUYA:
            // 輝夜姬
            break;
        case CHARACTER_LITTLE_MERMAID:
            // 美人魚
            break;
        case CHARACTER_MATCH_GIRL:
            // 火柴女孩
            break;
        case CHARACTER_DOROTHY:
            // 桃樂絲
            break;
        case CHARACTER_SCHEHERAZADE:
            // 山魯佐德
            break;
        default:
            debug_print ("error: character (%d) not implemented\n", player_data_use.character);
            return -1;
    }
    
    return 0;
}

int32_t game_action_buy_basic(eCardType type, int32_t player){
    int32_t idx = game_data_get_shop_top(PLAYER_ORIGINAL, type);
    if (idx < 0) return -1;      // 該疊空了
    return game_action_buy_card(idx, player);
}

int32_t game_action_buy_skill(eCardType type, int32_t player){
    int32_t idx = game_data_get_shop_top(player, type);
    if (idx < 0) return -1;
    return game_action_buy_card(idx, player);
}

# include "main.h"
# include "game_data_card.h"
# include "game_data_player.h"
sCardData card_data[CARD_NUM];
int32_t card_index[PLAYER_NUM][CARD_TYPE_NUM];

int32_t card_data_init_basic (int32_t idx){
    // CARD_BASIC_ATTACK_L1
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_ATTACK_L1]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L1, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L1);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_ATTACK_L2
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_ATTACK_L2]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L2, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L2);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_ATTACK_L3
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L3, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L3);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_DEFENSE_L1
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_DEFENSE_L1]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L1, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L1);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_DEFENSE_L2
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_DEFENSE_L2]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L2, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L2);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_DEFENSE_L3
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_DEFENSE_L3]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L3, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L3);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_MOVEMENT_L1
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_MOVEMENT_L1]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L1, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L1);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_MOVEMENT_L2
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_MOVEMENT_L2]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L2, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L2);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_MOVEMENT_L3
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_MOVEMENT_L3]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L3, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_BASIC_L3);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_COMMON
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_COMMON]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_COMMON, PLAYER_UNDEFINED);
    card_data_set_cost (idx, CARD_BASIC_NUM, CARD_COST_COMMON);
    idx+= CARD_BASIC_NUM;
    return idx;
}

int32_t card_data_init_skill (int32_t idx, int32_t player){
    // CARD_SKILL_ATTACK_BASE_L1
    card_index[player][CARD_SKILL_ATTACK_BASE_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L1, CARD_COST_SKILL_L1);
    idx+= CARD_SKILL_NUM_BASE_L1;
    // CARD_SKILL_ATTACK_BASE_L2
    card_index[player][CARD_SKILL_ATTACK_BASE_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L2, CARD_COST_SKILL_L2);
    idx+= CARD_SKILL_NUM_BASE_L2;
    // CARD_SKILL_ATTACK_EVOLUTION_L1
    card_index[player][CARD_SKILL_ATTACK_EVOLUTION_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_EVOLUTION_L1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_COST_SKILL_EVOLUTION);
    idx+= CARD_SKILL_NUM_EVOLUTION_L1;
    // CARD_SKILL_ATTACK_BASE_L3
    card_index[player][CARD_SKILL_ATTACK_BASE_L3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L3, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L3, CARD_COST_SKILL_L3);
    idx+= CARD_SKILL_NUM_BASE_L3;
    // CARD_SKILL_ATTACK_EVOLUTION_L2
    card_index[player][CARD_SKILL_ATTACK_EVOLUTION_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_EVOLUTION_L2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_COST_SKILL_EVOLUTION);
    idx+= CARD_SKILL_NUM_EVOLUTION_L2;

    // CARD_SKILL_DEFENSE_BASE_L1
    card_index[player][CARD_SKILL_DEFENSE_BASE_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L1, CARD_COST_SKILL_L1);
    idx+= CARD_SKILL_NUM_BASE_L1;
    // CARD_SKILL_DEFENSE_BASE_L2
    card_index[player][CARD_SKILL_DEFENSE_BASE_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L2, CARD_COST_SKILL_L2);
    idx+= CARD_SKILL_NUM_BASE_L2;
    // CARD_SKILL_DEFENSE_EVOLUTION_L1
    card_index[player][CARD_SKILL_DEFENSE_EVOLUTION_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_EVOLUTION_L1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_COST_SKILL_EVOLUTION);
    idx+= CARD_SKILL_NUM_EVOLUTION_L1;
    // CARD_SKILL_DEFENSE_BASE_L3
    card_index[player][CARD_SKILL_DEFENSE_BASE_L3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L3, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L3, CARD_COST_SKILL_L3);
    idx+= CARD_SKILL_NUM_BASE_L3;
    // CARD_SKILL_DEFENSE_EVOLUTION_L2
    card_index[player][CARD_SKILL_DEFENSE_EVOLUTION_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_EVOLUTION_L2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_COST_SKILL_EVOLUTION);
    idx+= CARD_SKILL_NUM_EVOLUTION_L2;

    // CARD_SKILL_MOVEMENT_BASE_L1
    card_index[player][CARD_SKILL_MOVEMENT_BASE_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L1, CARD_COST_SKILL_L1);
    idx+= CARD_SKILL_NUM_BASE_L1;
    // CARD_SKILL_MOVEMENT_BASE_L2
    card_index[player][CARD_SKILL_MOVEMENT_BASE_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L2, CARD_COST_SKILL_L2);
    idx+= CARD_SKILL_NUM_BASE_L2;
    // CARD_SKILL_MOVEMENT_EVOLUTION_L1
    card_index[player][CARD_SKILL_MOVEMENT_EVOLUTION_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_EVOLUTION_L1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_COST_SKILL_EVOLUTION);
    idx+= CARD_SKILL_NUM_EVOLUTION_L1;
    // CARD_SKILL_MOVEMENT_BASE_L3
    card_index[player][CARD_SKILL_MOVEMENT_BASE_L3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L3, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_BASE_L3, CARD_COST_SKILL_L3);
    idx+= CARD_SKILL_NUM_BASE_L3;
    // CARD_SKILL_MOVEMENT_EVOLUTION_L2
    card_index[player][CARD_SKILL_MOVEMENT_EVOLUTION_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_EVOLUTION_L2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_COST_SKILL_EVOLUTION);
    idx+= CARD_SKILL_NUM_EVOLUTION_L2;

    // CARD_SKILL_FINISH1
    card_index[player][CARD_SKILL_FINISH1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_FINISH1, CARD_SPACE_SHOP, CARD_SKILL_FINISH1, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_FINISH1, CARD_COST_SKILL_FINISH);
    idx+= CARD_SKILL_NUM_FINISH1;
    // CARD_SKILL_FINISH2
    card_index[player][CARD_SKILL_FINISH2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_FINISH2, CARD_SPACE_SHOP, CARD_SKILL_FINISH2, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_FINISH2, CARD_COST_SKILL_FINISH);
    idx+= CARD_SKILL_NUM_FINISH2;
    // CARD_SKILL_FINISH3
    card_index[player][CARD_SKILL_FINISH3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_FINISH3, CARD_SPACE_SHOP, CARD_SKILL_FINISH3, player);
    card_data_set_cost (idx, CARD_SKILL_NUM_FINISH3, CARD_COST_SKILL_FINISH);
    idx+= CARD_SKILL_NUM_FINISH3;

    return idx;
}

int32_t card_data_init (int32_t mode){

    for (int32_t i=0; i<CARD_NUM; i++){
        card_data[i].index= i;
    }
    int32_t idx=0;
    int32_t player= PLAYER_UNDEFINED;
    int32_t player_max;
    if (mode==GAMEMODE_1V1) player_max= PLAYER2; 

    for (int32_t i=0; i<CARD_BASIC_NUM_SUM; i++){
        card_data[i].player= player;
    }
    // CARD_BASIC
    idx= card_data_init_basic(idx);


    // CARD_SKILL
    for (player=PLAYER1; player<=player_max; player++){
        idx= card_data_init_skill(idx, player);
    }

    // CARD_UNDEFINED
    card_data_set (idx, CARD_NUM-idx, CARD_SPACE_DELETE, CARD_UNDEFINED, PLAYER_UNDEFINED);

    // hand
    for (player=PLAYER1; player<=player_max; player++){
        card_data_set (card_index[player][CARD_BASIC_ATTACK_L1]+3*(player-PLAYER1), 3, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_BASIC_DEFENSE_L1]+3*(player-PLAYER1), 3, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_BASIC_MOVEMENT_L1]+3*(player-PLAYER1), 3, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_SKILL_ATTACK_BASE_L1], 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_SKILL_DEFENSE_BASE_L1], 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_SKILL_MOVEMENT_BASE_L1], 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
    }
    return 0;
}

void card_data_set(int32_t idx, int32_t num, int32_t space, int32_t type, int32_t player){
    for (int32_t i=0; i<num; i++, idx++){
        if (idx >= CARD_NUM){
            debug_print ("error: idx (%d) larger than card num max (%d)", idx, CARD_NUM);
        }
        card_data[idx].space= space;
        if (type!=CARD_ORIGINAL) card_data[idx].type= type;
        if (player!=PLAYER_ORIGINAL) card_data[idx].player= player;
        if (player!=PLAYER_ORIGINAL && space!=CARD_SPACE_SHOP) player_data_set_card (player, idx);
    }
}

void card_data_set_cost(int32_t idx, int32_t num, int32_t cost){
    for (int32_t i=0; i<num; i++, idx++){
        if (idx >= CARD_NUM){
            debug_print ("error: idx (%d) larger than card num max (%d)", idx, CARD_NUM);
        }
        card_data[idx].cost= cost;
    }

}

void card_add (int32_t num, int32_t space, int32_t type, int32_t player){
    int32_t idx= 0;
    while (card_data[idx].type) idx++;
    card_data_set (idx, num, space, type, player);
    card_index[player][type]= idx;
}

void card_data_print (int32_t idx, int32_t num){
    debug_print ("from id (%d) get %d datas\n", idx, num);
    for (int32_t i=0; i<num; i++, idx++){
        char card_type_name[CARD_TYPE_NAME_MAX]= {0};
        card_data_get_type_name (card_type_name, idx);
        char card_space_name[CARD_SPACE_NAME_MAX]= {0};
        card_data_get_space_name (card_space_name, idx);
        // if (strstr(card_space_name, "SHOP")) continue;
        // if (strstr(card_space_name, "DELETE")) continue;
        if (!strstr(card_space_name, "USE")) continue;
        // if (!strstr(card_space_name, "DECK")) continue;
        debug_print ("card %d (%s), \tspace: %s, \tplayer: %d, \tcost: %d\n",
             idx, card_type_name, card_space_name, card_data[idx].player, card_data[idx].cost);
    }
}

int32_t card_cpy (sCardData *pCard, sCardData src){
    pCard->index= src.index;
    pCard->player= src.player;
    pCard->type= src.type;
    pCard->space= src.space;
    return 0;
}

int32_t card_data_get (sCardData *pCard, int32_t idx){
    if (!pCard){
        debug_print ("error: null pointer pCard.\n");
        return -1;
    }
    pCard->index = idx;
    pCard->space = card_data[idx].space;
    pCard->type  = card_data[idx].type;
    pCard->player = card_data[idx].player;
    return 0;
}

int32_t card_data_get_type_name (char card_type_name[], int32_t idx){
    switch (card_data[idx].type){
        case CARD_UNDEFINED:
            strcpy (card_type_name, "CARD_UNDEFINED");
            break;
        case CARD_BASIC_ATTACK_L1:
            strcpy (card_type_name, "CARD_BASIC_ATTACK_L1");
            break;
        case CARD_BASIC_ATTACK_L2:
            strcpy (card_type_name, "CARD_BASIC_ATTACK_L2");
            break;
        case CARD_BASIC_ATTACK_L3:
            strcpy (card_type_name, "CARD_BASIC_ATTACK_L3");
            break;
        case CARD_BASIC_DEFENSE_L1:
            strcpy (card_type_name, "CARD_BASIC_DEFENSE_L1");
            break;
        case CARD_BASIC_DEFENSE_L2:
            strcpy (card_type_name, "CARD_BASIC_DEFENSE_L2");
            break;
        case CARD_BASIC_DEFENSE_L3:
            strcpy (card_type_name, "CARD_BASIC_DEFENSE_L3");
            break;
        case CARD_BASIC_MOVEMENT_L1:
            strcpy (card_type_name, "CARD_BASIC_MOVEMENT_L1");
            break;
        case CARD_BASIC_MOVEMENT_L2:
            strcpy (card_type_name, "CARD_BASIC_MOVEMENT_L2");
            break;
        case CARD_BASIC_MOVEMENT_L3:
            strcpy (card_type_name, "CARD_BASIC_MOVEMENT_L3");
            break;
        case CARD_BASIC_COMMON:
            strcpy (card_type_name, "CARD_BASIC_COMMON");
            break;
        case CARD_SKILL_ATTACK_BASE_L1:
            strcpy (card_type_name, "CARD_SKILL_ATTACK_BASE_L1");
            break;
        case CARD_SKILL_ATTACK_BASE_L2:
            strcpy (card_type_name, "CARD_SKILL_ATTACK_BASE_L2");
            break;
        case CARD_SKILL_ATTACK_BASE_L3:
            strcpy (card_type_name, "CARD_SKILL_ATTACK_BASE_L3");
            break;
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
            strcpy (card_type_name, "CARD_SKILL_ATTACK_EVOLUTION_L1");
            break;
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
            strcpy (card_type_name, "CARD_SKILL_ATTACK_EVOLUTION_L2");
            break;
        case CARD_SKILL_DEFENSE_BASE_L1:
            strcpy (card_type_name, "CARD_SKILL_DEFENSE_BASE_L1");
            break;
        case CARD_SKILL_DEFENSE_BASE_L2:
            strcpy (card_type_name, "CARD_SKILL_DEFENSE_BASE_L2");
            break;
        case CARD_SKILL_DEFENSE_BASE_L3:
            strcpy (card_type_name, "CARD_SKILL_DEFENSE_BASE_L3");
            break;
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
            strcpy (card_type_name, "CARD_SKILL_DEFENSE_EVOLUTION_L1");
            break;
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
            strcpy (card_type_name, "CARD_SKILL_DEFENSE_EVOLUTION_L2");
            break;
        case CARD_SKILL_MOVEMENT_BASE_L1:
            strcpy (card_type_name, "CARD_SKILL_MOVEMENT_BASE_L1");
            break;
        case CARD_SKILL_MOVEMENT_BASE_L2:
            strcpy (card_type_name, "CARD_SKILL_MOVEMENT_BASE_L2");
            break;
        case CARD_SKILL_MOVEMENT_BASE_L3:
            strcpy (card_type_name, "CARD_SKILL_MOVEMENT_BASE_L3");
            break;
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
            strcpy (card_type_name, "CARD_SKILL_MOVEMENT_EVOLUTION_L1");
            break;
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
            strcpy (card_type_name, "CARD_SKILL_MOVEMENT_EVOLUTION_L2");
            break;
        case CARD_SKILL_FINISH1:
            strcpy (card_type_name, "CARD_SKILL_FINISH1");
            break;
        case CARD_SKILL_FINISH2:
            strcpy (card_type_name, "CARD_SKILL_FINISH2");
            break;
        case CARD_SKILL_FINISH3:
            strcpy (card_type_name, "CARD_SKILL_FINISH3");
            break;
        case CARD_POISON_L1:
            strcpy (card_type_name, "CARD_POISON_L1");
            break;
        case CARD_POISON_L2:
            strcpy (card_type_name, "CARD_POISON_L2");
            break;
        case CARD_POISON_L3:
            strcpy (card_type_name, "CARD_POISON_L3");
            break;
        case CARD_MATCH:
            strcpy (card_type_name, "CARD_MATCH");
            break;
        default:
            strcpy (card_type_name, "ERROR");
            break;
    }
    return 0;
}

int32_t card_data_get_space_name (char card_space_name[], int32_t idx){
    switch (card_data[idx].space){
        case CARD_SPACE_HAND:
            strcpy (card_space_name, "HAND");
            break;
        case CARD_SPACE_THROW:
            strcpy (card_space_name, "THROW");
            break;
        case CARD_SPACE_DECK:
            strcpy (card_space_name, "DECK");
            break;
        case CARD_SPACE_DECK_MATCH:
            strcpy (card_space_name, "DECK_MATCH");
            break;
        case CARD_SPACE_DECK_POISON:
            strcpy (card_space_name, "DECK_POISON");
            break;
        case CARD_SPACE_USE:
            strcpy (card_space_name, "USE");
            break;
        case CARD_SPACE_USE_LASTING:
            strcpy (card_space_name, "USE_LASTING");
            break;
        case CARD_SPACE_SHOP:
            strcpy (card_space_name, "SHOP");
            break;
        case CARD_SPACE_DELETE:
            strcpy (card_space_name, "DELETE");
            break;
        default:
            strcpy (card_space_name, "ERROR");
            break;

    }
    
}

int32_t card_data_get_index (int32_t player, int32_t type){
    return card_index[player][type];
}

int32_t card_data_get_level (int32_t type){
    switch (type){
        case CARD_BASIC_ATTACK_L1:
        case CARD_BASIC_DEFENSE_L1:
        case CARD_BASIC_MOVEMENT_L1:
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L1:
            return 1;
        case CARD_BASIC_ATTACK_L2:
        case CARD_BASIC_DEFENSE_L2:
        case CARD_BASIC_MOVEMENT_L2:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L2:
            return 2;
        case CARD_BASIC_ATTACK_L3:
        case CARD_BASIC_DEFENSE_L3:
        case CARD_BASIC_MOVEMENT_L3:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_DEFENSE_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L3:
            return 3;
        default:
            return 0;
    }
}

int32_t card_data_is_skill (int32_t idx){
    if (card_data[idx].type >= CARD_SKILL_ATTACK_BASE_L1 && card_data[idx].type <= CARD_SKILL_MOVEMENT_EVOLUTION_L2) {
        return 1;
    }
    return 0;
}

int32_t card_data_is_evolution2 (int32_t idx){
    if (card_data[idx].type == CARD_SKILL_ATTACK_EVOLUTION_L2) return 1;
    if (card_data[idx].type == CARD_SKILL_DEFENSE_EVOLUTION_L2) return 1;
    if (card_data[idx].type == CARD_SKILL_MOVEMENT_EVOLUTION_L2) return 1;
    return 0;
}

int32_t card_attach_calculate (int32_t idx, int32_t action_type){
    if (idx==CARD_ORIGINAL) return 0;
    int32_t level= 0;
    level= card_data_get_level(card_data[idx].type);
    switch (action_type){
        case ACTION_ATTACK:
            if (card_data[idx].type>=CARD_BASIC_ATTACK_L1 && card_data[idx].type<=CARD_BASIC_ATTACK_L3) return level;
            if (card_data[idx].type==CARD_BASIC_COMMON) return 1;
            break;
        case ACTION_DEFENSE:
            if (card_data[idx].type>=CARD_BASIC_DEFENSE_L1 && card_data[idx].type<=CARD_BASIC_DEFENSE_L3) return level;
            if (card_data[idx].type==CARD_BASIC_COMMON) return 1;
            break;
        case ACTION_MOVE:
            if (card_data[idx].type>=CARD_BASIC_MOVEMENT_L1 && card_data[idx].type<=CARD_BASIC_MOVEMENT_L3) return level;
            if (card_data[idx].type==CARD_BASIC_COMMON) return 1;
            break;
        default:
            debug_print ("error: undefined action\n");
            return -1;
            break;
    }
    debug_print ("error: wrong match for card and action\n");
    return -1;
}
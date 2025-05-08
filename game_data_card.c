# include "main.h"
# include "game_data_card.h"

sCardData card_data[CARD_NUM];
int32_t card_index[PLAYER_NUM][CARD_TYPE_NUM];

void card_data_set(int32_t idx, int32_t num, int32_t space, int32_t type, int32_t player){
    for (int32_t i=0; i<num; i++, idx++){
        if (idx >= CARD_NUM){
            debug_print ("error: idx (%d) larger than card num max (%d)", idx, CARD_NUM);
        }
        card_data[idx].space= space;
        if (type!=CARD_ORIGINAL) card_data[idx].type= type;
        if (player!=PLAYER_ORIGINAL) card_data[idx].player= player;
    }
}

int32_t card_data_init_basic (int32_t idx){
    // CARD_BASIC_ATTACK_L1
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_ATTACK_L1]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L1, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_ATTACK_L2
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_ATTACK_L2]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L2, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_ATTACK_L3
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L3, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_DEFENSE_L1
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_DEFENSE_L1]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L1, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_DEFENSE_L2
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_DEFENSE_L2]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L2, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_DEFENSE_L3
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_DEFENSE_L3]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L3, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_MOVEMENT_L1
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_MOVEMENT_L1]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L1, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_MOVEMENT_L2
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_MOVEMENT_L2]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L2, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_MOVEMENT_L3
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_MOVEMENT_L3]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L3, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    // CARD_BASIC_COMMON
    for (int32_t i=PLAYER1; i<PLAYER_NUM; i++) card_index[i][CARD_BASIC_COMMON]= idx;
    card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_COMMON, PLAYER_UNDEFINED);
    idx+= CARD_BASIC_NUM;
    return idx;
}

int32_t card_data_init_skill (int32_t idx, int32_t player){
    // CARD_SKILL_ATTACK_BASE_L1
    card_index[player][CARD_SKILL_ATTACK_BASE_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L1, player);
    idx+= CARD_SKILL_NUM_BASE_L1;
    // CARD_SKILL_ATTACK_BASE_L2
    card_index[player][CARD_SKILL_ATTACK_BASE_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L2, player);
    idx+= CARD_SKILL_NUM_BASE_L2;
    // CARD_SKILL_ATTACK_EVOLUTION_L1
    card_index[player][CARD_SKILL_ATTACK_EVOLUTION_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_EVOLUTION_L1, player);
    idx+= CARD_SKILL_NUM_EVOLUTION_L1;
    // CARD_SKILL_ATTACK_BASE_L3
    card_index[player][CARD_SKILL_ATTACK_BASE_L3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L3, player);
    idx+= CARD_SKILL_NUM_BASE_L3;
    // CARD_SKILL_ATTACK_EVOLUTION_L2
    card_index[player][CARD_SKILL_ATTACK_EVOLUTION_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_EVOLUTION_L2, player);
    idx+= CARD_SKILL_NUM_EVOLUTION_L2;

    // CARD_SKILL_DEFENSE_BASE_L1
    card_index[player][CARD_SKILL_DEFENSE_BASE_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L1, player);
    idx+= CARD_SKILL_NUM_BASE_L1;
    // CARD_SKILL_DEFENSE_BASE_L2
    card_index[player][CARD_SKILL_DEFENSE_BASE_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L2, player);
    idx+= CARD_SKILL_NUM_BASE_L2;
    // CARD_SKILL_DEFENSE_EVOLUTION_L1
    card_index[player][CARD_SKILL_DEFENSE_EVOLUTION_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_EVOLUTION_L1, player);
    idx+= CARD_SKILL_NUM_EVOLUTION_L1;
    // CARD_SKILL_DEFENSE_BASE_L3
    card_index[player][CARD_SKILL_DEFENSE_BASE_L3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L3, player);
    idx+= CARD_SKILL_NUM_BASE_L3;
    // CARD_SKILL_DEFENSE_EVOLUTION_L2
    card_index[player][CARD_SKILL_DEFENSE_EVOLUTION_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_EVOLUTION_L2, player);
    idx+= CARD_SKILL_NUM_EVOLUTION_L2;

    // CARD_SKILL_MOVEMENT_BASE_L1
    card_index[player][CARD_SKILL_MOVEMENT_BASE_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L1, player);
    idx+= CARD_SKILL_NUM_BASE_L1;
    // CARD_SKILL_MOVEMENT_BASE_L2
    card_index[player][CARD_SKILL_MOVEMENT_BASE_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L2, player);
    idx+= CARD_SKILL_NUM_BASE_L2;
    // CARD_SKILL_MOVEMENT_EVOLUTION_L1
    card_index[player][CARD_SKILL_MOVEMENT_EVOLUTION_L1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_EVOLUTION_L1, player);
    idx+= CARD_SKILL_NUM_EVOLUTION_L1;
    // CARD_SKILL_MOVEMENT_BASE_L3
    card_index[player][CARD_SKILL_MOVEMENT_BASE_L3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L3, player);
    idx+= CARD_SKILL_NUM_BASE_L3;
    // CARD_SKILL_MOVEMENT_EVOLUTION_L2
    card_index[player][CARD_SKILL_MOVEMENT_EVOLUTION_L2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_EVOLUTION_L2, player);
    idx+= CARD_SKILL_NUM_EVOLUTION_L2;

    // CARD_SKILL_FINISH1
    card_index[player][CARD_SKILL_FINISH1]= idx;
    card_data_set (idx, CARD_SKILL_NUM_FINISH1, CARD_SPACE_SHOP, CARD_SKILL_FINISH1, player);
    idx+= CARD_SKILL_NUM_FINISH1;
    // CARD_SKILL_FINISH2
    card_index[player][CARD_SKILL_FINISH2]= idx;
    card_data_set (idx, CARD_SKILL_NUM_FINISH2, CARD_SPACE_SHOP, CARD_SKILL_FINISH2, player);
    idx+= CARD_SKILL_NUM_FINISH2;
    // CARD_SKILL_FINISH3
    card_index[player][CARD_SKILL_FINISH3]= idx;
    card_data_set (idx, CARD_SKILL_NUM_FINISH3, CARD_SPACE_SHOP, CARD_SKILL_FINISH3, player);
    idx+= CARD_SKILL_NUM_FINISH3;

    return idx;
}

int32_t card_data_init(){

    for (int32_t i=0; i<CARD_NUM; i++){
        card_data[i].index= i;
    }
    int32_t idx=0;
    int32_t player= PLAYER_UNDEFINED;
    for (int32_t i=0; i<CARD_BASIC_NUM_SUM; i++){
        card_data[i].player= player;
    }
    // CARD_BASIC
    idx= card_data_init_basic(idx);


    // CARD_SKILL
    for (player=PLAYER1; player<=PLAYER4; player++){
        idx= card_data_init_skill(idx, player);
    }

    // CARD_UNDEFINED
    card_data_set (idx, CARD_NUM-idx, CARD_SPACE_DELETE, CARD_UNDEFINED, PLAYER_UNDEFINED);

    // hand
    for (player=PLAYER1; player<=PLAYER4; player++){
        card_data_set (card_index[player][CARD_BASIC_ATTACK_L1]+3*(player-PLAYER1), 3, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_BASIC_DEFENSE_L1]+3*(player-PLAYER1), 3, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_BASIC_MOVEMENT_L1]+3*(player-PLAYER1), 3, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_SKILL_ATTACK_BASE_L1], 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_SKILL_DEFENSE_BASE_L1], 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
        card_data_set (card_index[player][CARD_SKILL_MOVEMENT_BASE_L1], 1, CARD_SPACE_THROW, CARD_ORIGINAL, player);
    }
    return 0;
}

void card_data_print (int32_t idx, int32_t num){
    debug_print ("from id: (%d) to (%d)\n", idx, num);
    for (int32_t i=0; i<num; i++, idx++){
        char card_type_name[100]= {0};
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
            default:
                strcpy (card_type_name, "ERROR");
                break;
        }
        char card_space_name[100]= {0};
        switch (card_data[idx].space){
            case CARD_SPACE_HAND:
                strcpy (card_space_name, "HAND");
                break;
            case CARD_SPACE_THROW:
                strcpy (card_space_name, "THROW");
                break;
            case CARD_SPACE_USE:
                strcpy (card_space_name, "USE");
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
        if (!strstr(card_space_name, "THROW")) continue;
        debug_print ("card %d (%s), \tspace: %s, \tplayer: %d\n", idx, card_type_name, card_space_name, card_data[idx].player);
    }
}

int32_t card_data_get (sCardData *pCard, int32_t idx){
    if (!pCard){
        debug_print ("error: null pointer pCard.\n");
        return -1;
    }
    pCard->index = idx;
    pCard->space = card_data[idx].space;
    pCard->type  = card_data[idx].type;
    return 0;
}
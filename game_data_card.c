# include "main.h"
# include "game_data_card.h"

sCardData card_data[CARD_NUM];
int32_t card_index[CARD_TYPE_NUM];

void card_data_set(int32_t idx, int32_t num, int32_t space, int32_t type){
    for (int32_t i=0; i<num; i++){
        if (idx+i >= CARD_NUM){
            debug_print ("error: idx (%d) larger than card num max (%d)", idx+i, CARD_NUM);
        }
        card_data[idx+i].space= space;
        if (type!=CARD_ORIGINAL) card_data[idx+i].type= type;
    }
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
        // if (!strstr(card_space_name, "HAND")) continue;
        debug_print ("card %d (%s), \tspace: %s\n", idx, card_type_name, card_space_name);
    }
}

int32_t card_data_init(){
    int32_t idx=0;

    // CARD_BASIC
    {
        // CARD_BASIC_ATTACK_L1
        card_index[CARD_BASIC_ATTACK_L1]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L1);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_ATTACK_L2
        card_index[CARD_BASIC_ATTACK_L2]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L2);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_ATTACK_L3
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_ATTACK_L3);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_DEFENSE_L1
        card_index[CARD_BASIC_DEFENSE_L1]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L1);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_DEFENSE_L2
        card_index[CARD_BASIC_DEFENSE_L2]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L2);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_DEFENSE_L3
        card_index[CARD_BASIC_DEFENSE_L3]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_DEFENSE_L3);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_MOVEMENT_L1
        card_index[CARD_BASIC_MOVEMENT_L1]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L1);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_MOVEMENT_L2
        card_index[CARD_BASIC_MOVEMENT_L2]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L2);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_MOVEMENT_L3
        card_index[CARD_BASIC_MOVEMENT_L3]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_MOVEMENT_L3);
        idx+= CARD_BASIC_NUM;
        // CARD_BASIC_COMMON
        card_index[CARD_BASIC_COMMON]= idx;
        card_data_set (idx, CARD_BASIC_NUM, CARD_SPACE_SHOP, CARD_BASIC_COMMON);
        idx+= CARD_BASIC_NUM;
    }

    // CARD_SKILL
    {
        // CARD_SKILL_ATTACK_BASE_L1
        card_index[CARD_SKILL_ATTACK_BASE_L1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L1);
        idx+= CARD_SKILL_NUM_BASE_L1;
        // CARD_SKILL_ATTACK_BASE_L2
        card_index[CARD_SKILL_ATTACK_BASE_L2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L2);
        idx+= CARD_SKILL_NUM_BASE_L2;
        // CARD_SKILL_ATTACK_EVOLUTION_L1
        card_index[CARD_SKILL_ATTACK_EVOLUTION_L1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_EVOLUTION_L1);
        idx+= CARD_SKILL_NUM_EVOLUTION_L1;
        // CARD_SKILL_ATTACK_BASE_L3
        card_index[CARD_SKILL_ATTACK_BASE_L3]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_BASE_L3);
        idx+= CARD_SKILL_NUM_BASE_L3;
        // CARD_SKILL_ATTACK_EVOLUTION_L2
        card_index[CARD_SKILL_ATTACK_EVOLUTION_L2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_ATTACK_EVOLUTION_L2);
        idx+= CARD_SKILL_NUM_EVOLUTION_L2;

        // CARD_SKILL_DEFENSE_BASE_L1
        card_index[CARD_SKILL_DEFENSE_BASE_L1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L1);
        idx+= CARD_SKILL_NUM_BASE_L1;
        // CARD_SKILL_DEFENSE_BASE_L2
        card_index[CARD_SKILL_DEFENSE_BASE_L2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L2);
        idx+= CARD_SKILL_NUM_BASE_L2;
        // CARD_SKILL_DEFENSE_EVOLUTION_L1
        card_index[CARD_SKILL_DEFENSE_EVOLUTION_L1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_EVOLUTION_L1);
        idx+= CARD_SKILL_NUM_EVOLUTION_L1;
        // CARD_SKILL_DEFENSE_BASE_L3
        card_index[CARD_SKILL_DEFENSE_BASE_L3]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_BASE_L3);
        idx+= CARD_SKILL_NUM_BASE_L3;
        // CARD_SKILL_DEFENSE_EVOLUTION_L2
        card_index[CARD_SKILL_DEFENSE_EVOLUTION_L2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_DEFENSE_EVOLUTION_L2);
        idx+= CARD_SKILL_NUM_EVOLUTION_L2;

        // CARD_SKILL_MOVEMENT_BASE_L1
        card_index[CARD_SKILL_MOVEMENT_BASE_L1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L1, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L1);
        idx+= CARD_SKILL_NUM_BASE_L1;
        // CARD_SKILL_MOVEMENT_BASE_L2
        card_index[CARD_SKILL_MOVEMENT_BASE_L2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L2, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L2);
        idx+= CARD_SKILL_NUM_BASE_L2;
        // CARD_SKILL_MOVEMENT_EVOLUTION_L1
        card_index[CARD_SKILL_MOVEMENT_EVOLUTION_L1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L1, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_EVOLUTION_L1);
        idx+= CARD_SKILL_NUM_EVOLUTION_L1;
        // CARD_SKILL_MOVEMENT_BASE_L3
        card_index[CARD_SKILL_MOVEMENT_BASE_L3]= idx;
        card_data_set (idx, CARD_SKILL_NUM_BASE_L3, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_BASE_L3);
        idx+= CARD_SKILL_NUM_BASE_L3;
        // CARD_SKILL_MOVEMENT_EVOLUTION_L2
        card_index[CARD_SKILL_MOVEMENT_EVOLUTION_L2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_EVOLUTION_L2, CARD_SPACE_SHOP, CARD_SKILL_MOVEMENT_EVOLUTION_L2);
        idx+= CARD_SKILL_NUM_EVOLUTION_L2;

        // CARD_SKILL_FINISH1
        card_index[CARD_SKILL_FINISH1]= idx;
        card_data_set (idx, CARD_SKILL_NUM_FINISH1, CARD_SPACE_SHOP, CARD_SKILL_FINISH1);
        idx+= CARD_SKILL_NUM_FINISH1;
        // CARD_SKILL_FINISH2
        card_index[CARD_SKILL_FINISH2]= idx;
        card_data_set (idx, CARD_SKILL_NUM_FINISH2, CARD_SPACE_SHOP, CARD_SKILL_FINISH2);
        idx+= CARD_SKILL_NUM_FINISH2;
        // CARD_SKILL_FINISH3
        card_index[CARD_SKILL_FINISH3]= idx;
        card_data_set (idx, CARD_SKILL_NUM_FINISH3, CARD_SPACE_SHOP, CARD_SKILL_FINISH3);
        idx+= CARD_SKILL_NUM_FINISH3;
    }

    // CARD_UNDEFINED
    card_data_set (idx, CARD_NUM-idx, CARD_SPACE_DELETE, CARD_UNDEFINED);

    // hand
    card_data_set (card_index[CARD_BASIC_ATTACK_L1], 3, CARD_SPACE_HAND, CARD_ORIGINAL);
    card_data_set (card_index[CARD_BASIC_DEFENSE_L1], 3, CARD_SPACE_HAND, CARD_ORIGINAL);
    card_data_set (card_index[CARD_BASIC_MOVEMENT_L1], 3, CARD_SPACE_HAND, CARD_ORIGINAL);
    card_data_set (card_index[CARD_SKILL_ATTACK_BASE_L1], 1, CARD_SPACE_HAND, CARD_ORIGINAL);
    card_data_set (card_index[CARD_SKILL_DEFENSE_BASE_L1], 1, CARD_SPACE_HAND, CARD_ORIGINAL);
    card_data_set (card_index[CARD_SKILL_MOVEMENT_BASE_L1], 1, CARD_SPACE_HAND, CARD_ORIGINAL);
    return 0;
}
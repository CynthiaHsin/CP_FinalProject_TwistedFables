# include "main.h"
# include "game_data.h"
# include "game_action.h"

int32_t game_action_use_basic_card (int32_t cards_idx, int32_t card_type, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des){
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    if (player_data_get (&player_data_use, player_use)<0) return -1;
    if (player_data_get (&player_data_des, player_des)<0) return -1;

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
            if (abs(player_data_use.pos - player_data_des.pos) > 1){
                debug_print ("error: too long destination: use at %d, des at %d", player_data_use.pos, player_data_des.pos);
                return -1;
            }
            player_data_des.defense-= level;
            if (player_data_des.defense<0){
                player_data_des.hp+= player_data_des.defense;
                player_data_des.defense= 0;
            }
            break;

        case CARD_BASIC_DEFENSE_L1:
        case CARD_BASIC_DEFENSE_L2:
        case CARD_BASIC_DEFENSE_L3:
            level= card_type - CARD_BASIC_DEFENSE_L1 + 1;
            player_data_use.defense+= level;
            player_data_use.defense= MIN (player_data_use.defense, player_data_use.defense_max);
            break;

        case CARD_BASIC_MOVEMENT_L1:
        case CARD_BASIC_MOVEMENT_L2:
        case CARD_BASIC_MOVEMENT_L3: 
            level= card_type - CARD_BASIC_MOVEMENT_L1 + 1;
            int32_t des= player_data_des.pos + move_direction*level;
            if (des==player_data_des.pos){
                int32_t stay= player_data_use.pos - player_data_des.pos;
                stay/= abs(stay);
                des= player_data_des.pos + stay;
            }
            // not yet: 場地邊緣處理
            player_data_des.pos= des;
            break;
    }
    player_data_use.power+= level;
    player_data_use.power= MIN (player_data_use.power, player_data_use.power_max);
    
    player_data_set (player_use, player_data_use);
    player_data_set (player_des, player_data_des);
    return 0;
}
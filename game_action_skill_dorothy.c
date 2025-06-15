# include "main.h"
# include "game_action_skill_dorothy.h"
# include "game_action_basic.h"
# include "game_data.h"
# include "gui_game_action.h"

int32_t skill_dorothy (int32_t card_idx[DOROTHY_CARD_IDX_NUM], int32_t defense_throw_idx[3], int32_t defense_throw_num, 
                       int32_t movement_evolution1_card_idx[], int32_t movement_evolution1_card_num, int32_t mevement_evolution1_des_direction,
                       int32_t player_use, int32_t player_des){
    sCardData card_data;
    card_data_get (&card_data, card_idx[0]);
    int32_t level_skill= card_data_get_level (card_data.type);
    card_data_get (&card_data, card_idx[1]);
    int32_t level_attach= card_data_get_level (card_data.type);
    card_data_get (&card_data, card_idx[0]);
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    player_data_get (&player_data_use, player_use);
    player_data_get (&player_data_des, player_des);
    sGameDataDorothyAction action;
    int32_t dis= player_data_des.pos - player_data_use.pos;
    dis= abs(dis);
    switch (card_data.type) {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
            if (dis>1) return -1;
            dis= player_data_des.pos;
            action_move (level_attach, player_data_use.pos-player_data_des.pos, player_des);
            player_data_get (&player_data_des, player_des);
            dis-= player_data_des.pos;
            dis= abs(dis);
            if (dis>level_attach) return -1;
            level_attach += (level_attach-dis);
            action_attack (level_attach + level_skill, ACTION_NO_AREA, player_use, player_des);
            action.attack_value= level_attach + level_skill;
            action.card_type= CARD_SKILL_ATTACK_BASE_L1;
            action.level= level_skill;
            card_data_set (card_idx[0], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[1], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            skill_dorothy_action (action, player_use);
            break;
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
            action_attack (level_attach, 5+level_skill, player_use, player_des);
            card_data_set (card_idx[0], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[1], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            int32_t pull= 1;
            for (int32_t i=0; i<defense_throw_num; i++){
                card_data_set (defense_throw_idx[i], 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
                pull++;
            }
            deck_data_draw_cards (player_use, pull);
            action.attack_value= level_attach + level_skill;
            action.card_type= CARD_SKILL_DEFENSE_BASE_L1;
            action.level= level_skill;
            skill_dorothy_action (action, player_use);
            break;
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
            int32_t attack_value= 1+dis;
            action_attack (attack_value, level_attach + level_skill, player_use, player_des);
            card_data_set (card_idx[0], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[1], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            action.attack_value= attack_value;
            action.card_type= CARD_SKILL_MOVEMENT_BASE_L1;
            action.level= level_skill;
            skill_dorothy_action (action, player_use);
            break;
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
            int32_t value= 0;
            for (int32_t i=0; i<movement_evolution1_card_num; i++){
                card_data_get (&card_data, movement_evolution1_card_idx[i]);
                value+= card_data_get_level (card_data.type);
                card_data_set (movement_evolution1_card_idx[i], 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
            }
            action_move (value, mevement_evolution1_des_direction, player_des);
            break;
        default:
            return -1;
    }

    // passive
    int32_t passive_card_idx[2]= {CARD_ORIGINAL, CARD_ORIGINAL};
    // -----
    passive_card_idx[0]= gui_passive_dorothy (player_use);
    // -----
    if (passive_card_idx[0]<0) return 0;
    card_data_get (&card_data, card_idx[0]);
    level_skill= card_data_get_level (card_data.type);
    card_data_get (&card_data, passive_card_idx[0]);
    int32_t level_passive= card_data_get_level (card_data.type);
    // skill_dorothy_action ()
    // status_dorothy_batter (level_passive-level_skill, player_use);
    int32_t null_array[3]= {0};
    skill_dorothy (passive_card_idx, null_array, 0, null_array, 0, 0, player_use, player_des);
    return 0;
}

int32_t skill_dorothy_finish (int32_t card_idx, int32_t token, int32_t player_use, int32_t player_des){
    sCardData card_data;
    card_data_get (&card_data, card_idx);
    int32_t token_use= -1* status_dorothy_token_add (-1*token, player_use);
    sGameDataDorothyAction action;
    action.card_type= card_data.type;
    action.level= 1;
    action.attack_value= 0;
    sPlayerData player_data;
    switch (card_data.type){
        case CARD_SKILL_FINISH1:
            action_attack (token_use, 1, player_use, player_des);
            action_modefy_power (token_use, player_use);
            action.attack_value= token_use;
            break;
        case CARD_SKILL_FINISH2:
            player_data_get (&player_data, player_use);
            player_data.hp+= token_use;
            player_data.hp= MIN (player_data.hp, player_data.hp_max);
            break;
        case CARD_SKILL_FINISH3:
            int32_t pull= (token_use+1)/2;
            deck_data_draw_cards (player_use, pull);
            break;
        default:
            return -1;
    }
    card_data_set (card_idx, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    skill_dorothy_action (action, player_use);
    return 0;
}

int32_t skill_dorothy_action (sGameDataDorothyAction action, int32_t player){
    sGameDataDorothyAction last_action;
    status_dorothy_last_action (&last_action);
    if (last_action.card_type==CARD_BASIC_ATTACK_L1 && action.card_type==CARD_BASIC_ATTACK_L1){
        if (last_action.attack_value < action.attack_value){
            status_dorothy_batter(0, player);
        }
    }
    if (card_data_is_skill(card_data_get_index(player, last_action.card_type)) 
     && card_data_is_skill(card_data_get_index(player, action.card_type))){
        status_dorothy_batter(action.level - last_action.level, player);
    }
    status_dorothy_do_action (action);
    return 0;
}

int32_t skill_dorothy_basic (int32_t value, int32_t type, int32_t player){
    sGameDataDorothyAction action;
    action.attack_value= value;
    action.card_type= type;
    action.level= value;
    skill_dorothy_action (action, player);
}
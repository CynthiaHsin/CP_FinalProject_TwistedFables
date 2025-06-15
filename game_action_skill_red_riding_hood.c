# include "game_action_skill_red_riding_hood.h"
# include "game_data.h"
# include "game_action_basic.h"
# include "gui_game_choose.h"

// card0: main skill, card1: attack evolution, card2: movement evolution, card3: evolution 2, for no card use: -1
int32_t skill_red_riding_hood (int32_t card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t player_des){
    sCardData card_data;
    card_data_get(&card_data, card_idx[RED_RIDING_HOOD_CARD_IDX_SKILL]);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    sPlayerData player_data_des;
    player_data_get(&player_data_use, player_des);
    // eCardType
    int32_t attack_area = skill_red_riding_hood_movement_evolution(card_idx, player_use, 1);
    int32_t level = card_data_get_level(card_data.type);
    int32_t attach_level= 0;
    switch (card_data.type) {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:{
            attack_area += level;
            attach_level= card_attach_calculate(card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACH], ACTION_ATTACK);
            if (attach_level<0){
                return -1;
            }else{
                level+= attach_level;
            }
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
            card_data_set (card_data.index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            if (skill_red_riding_hood_attack_evolution(card_idx, player_use, player_des, attack_area) < 0) {
                return -1;
            }
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:{
            attach_level= card_attach_calculate(card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACH], ACTION_DEFENSE);
            if (attach_level<0){
                return -1;
            }
            if (action_defense (attach_level, player_use)<0){
                return -1;
            }
            action_attack (level, level, player_use, player_des);
            card_data_set (card_data.index, 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:{
            int32_t attacked= 0;
            int32_t attach_level= card_attach_calculate(card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACH], ACTION_MOVE);
            if (attach_level<0){
                return -1;
            }
            int32_t level = card_data_get_level(card_data.type);
            attack_area += level;
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }else{
                attacked= 1;
            }
            card_data_set (card_data.index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            if (skill_red_riding_hood_attack_evolution(card_idx, player_use, player_des, attack_area) < 0) {
                return -1;
            }
            if (attacked){
                int32_t attack_direction= player_data_des.pos - player_data_use.pos;
                action_move (attach_level, attack_direction, player_des);
            }
            break;
        }
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:{
            if (status_red_riding_hood_evolution2_card_set(card_idx[RED_RIDING_HOOD_CARD_IDX_EVOLUTION2], card_data.type)<0){
                debug_print ("error: you cannot set this card to evolution deck\n");
                return -1;
            }
            break;
        }
    }
    for (int32_t i=0; i<RED_RIDING_HOOD_CARD_IDX_NUM; i++){
        card_data_get(&card_data, card_idx[i]);
        if (card_data.space == CARD_SPACE_HAND){
            card_data_set (card_data.index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        }
    }
}

int32_t skill_red_riding_hood_attack_evolution (int32_t card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t player_des, int32_t attack_area){
    if (card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION] == -1) {
        return 0;
    }
    sCardData card_data;
    card_data_get(&card_data, card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION]);
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
    card_data_set (card_data.index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

int32_t skill_red_riding_hood_movement_evolution (int32_t card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t attack_area){
    if (card_idx[RED_RIDING_HOOD_CARD_IDX_MOVEMENT_EVOLUTION] == -1) {
        return 0;
    }
    sCardData card_data;
    card_data_get(&card_data, card_idx[RED_RIDING_HOOD_CARD_IDX_MOVEMENT_EVOLUTION]);
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
    card_data_set (card_data.index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return attack_area;
}

int32_t skill_red_riding_hood_evolution2 (int32_t evolution_type){
    return status_red_riding_hood_evolution2_card_move2hand(evolution_type);
}

// finish*_*: things you need to do by these information. finish1 ex: CARD_SKILL_ATTACK_BASE_L1 (只放各種類的L1). finish3_delta: 擊退距離
int32_t skill_red_riding_hood_finish (int32_t finish_card_idx, int32_t finish1_skill_type[2], int32_t finish2_card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t finish3_delta, int32_t player_use, int32_t player_des){
    sCardData finish_card_data;
    card_data_get (&finish_card_data, finish_card_idx);
    if (finish_card_data.space!=CARD_SPACE_HAND) {
        debug_print ("error: wrong finish card\n");
        return -1;
    }
    sCardData card_datas[CARD_NUM];
    sCardData card_data;
    int32_t card_num= 0;
    int32_t card_idx= 0;

    switch (finish_card_data.type){
        case CARD_SKILL_FINISH1:
            skill_red_riding_hood_finish1 (finish1_skill_type, player_use);
            break;
        case CARD_SKILL_FINISH2:
            skill_red_riding_hood_finish2 (finish2_card_idx, player_use, player_des);
            break;
        case CARD_SKILL_FINISH3:
            skill_red_riding_hood_finish3 (finish3_delta, player_use, player_des);
            break;
        default:
            debug_print ("error: wrong finish card\n");
            return -1;
    }
    card_data_set (finish_card_idx, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
}

int32_t skill_red_riding_hood_finish1 (int32_t finish1_skill_type[2], int32_t player_use){
    sCardData card_data;
    int32_t card_num= 0;
    int32_t card_idx= 0;
    card_num= 1;
    if (finish1_skill_type[0]==finish1_skill_type[1]) card_num= 2;
    card_idx= card_data_get_index(player_use, finish1_skill_type[0]);
    while (1){
        if (!card_data_is_skill(card_idx)) return -1;
        card_data_get (&card_data, card_idx);
        if (card_data.space==CARD_SPACE_SHOP){
            card_data_set (card_idx, card_num, CARD_SPACE_HAND, CARD_ORIGINAL, player_use);
            break;
        }
        if (card_data_is_evolution2(card_idx)) break;
        card_idx++;
    }
    if (card_num==2) return 0;
    while (1){
        if (!card_data_is_skill(card_idx)) return -1;
        card_data_get (&card_data, card_idx);
        if (card_data.space==CARD_SPACE_SHOP){
            card_data_set (card_idx, card_num, CARD_SPACE_HAND, CARD_ORIGINAL, player_use);
            break;
        }
        if (card_data_is_evolution2(card_idx)) break;
        card_idx++;
    }
    return 0;
}

int32_t skill_red_riding_hood_finish2 (int32_t finish2_card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], int32_t player_use, int32_t player_des){
    for (int32_t i=0; i<RED_RIDING_HOOD_CARD_IDX_NUM; i++){
        if (finish2_card_idx[i]<0) continue;
        card_data_set (finish2_card_idx[i], 1, CARD_SPACE_HAND, CARD_ORIGINAL, PLAYER_ORIGINAL);
    }
    skill_red_riding_hood (finish2_card_idx, player_use, player_des);
}

int32_t skill_red_riding_hood_finish3 (int32_t finish3_delta, int32_t player_use, int32_t player_des){
    if (action_attack (3, 3, player_use, player_des)<0) return -1;
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    player_data_get (&player_data_use, player_use);
    player_data_get (&player_data_des, player_des);

    int32_t direction= player_data_des.pos - player_data_use.pos;
    action_move (finish3_delta, direction, player_des);
    // highlight call ui for throw card
    int32_t card_throw_idx= -1;
    // ---------
    sCardData cards[CARD_NUM];
    for (int32_t i=0; i<3; i++){
        int32_t t;
        int32_t cnt;
        game_data_search_cards (cards, &cnt, player_des, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
        while (card_throw_idx<0) {
            card_throw_idx= gui_choose_card (&t, cards, cnt, "Choose the card that you have to throw.");
        }
        card_data_set (card_throw_idx, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
    }
    // ---------
    return 0;
}

int32_t skill_red_riding_hood_round_start (int32_t player){
    sCardData card_datas[CARD_NUM];
    int32_t card_num= 0;
    game_data_search_cards (card_datas, &card_num, player, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, -1);
    
    sPlayerData player_data;
    player_data_get (&player_data, player);

    // int32_t mode= GAMEMODE_1V1;
    int32_t player_max= PLAYER2;
    if (player_data.defense){
        for (int32_t i=0; i<card_num; i++){
            if (card_data_is_evolution (card_datas[i].index)) continue;
            card_data_set (card_datas[i].index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            if (!card_data_is_skill (card_datas[i].index)) continue;
            int32_t level = card_data_get_level (card_datas[i].type);
            for (int32_t p=PLAYER1; p<=PLAYER2; p++){
                if (p==player) continue;
                action_attack(level*2, level, player, p);
            }
        }
    }
    return 0;
}
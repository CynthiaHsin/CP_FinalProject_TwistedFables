# include "main.h"
# include "game_action_skill_kaguya.h"
# include "game_action_basic.h"
# include "game_data.h"
# include "gui_game_action.h"
# include "gui_game_choose.h"

// skill_move_use_hp_card_idx: 要使用一點生命值移除牌，輸入牌編號，否則輸入CARD_ORIGINAL
int32_t skill_kaguya (int32_t card_idx[KAGUYA_CARD_IDX_NUM], int32_t skill_move_use_hp_card_idx, int32_t skill_move_evolution_direction, int32_t player_use, int32_t player_des){
    sCardData card_data;
    card_data_get (&card_data, card_idx[0]);
    sCardData card_data_attach;
    card_data_get (&card_data_attach, card_idx[1]);
    int32_t level_skill= card_data_get_level (card_idx[0]);
    int32_t level_attach= card_data_get_level (card_idx[1]);
    sPlayerData player_data;
    player_data_get (&player_data, player_use);
    switch (card_data.type) {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:{
            level_attach= status_kaguya_use_defense_card_as_attack (level_attach, player_use);
            if (level_attach==0) return -1;
            if (player_data.defense>=3){
                level_attach++;
            }
            if (action_attack (level_attach + level_skill, 1, player_use, player_des));
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:{
            action_defense (level_attach + level_skill, player_use);
            sCardData cards[3];
            int32_t choose[3]= {0}; // 0: return, -1: throw, 1: defense
            for (int32_t i=0; i<level_skill; i++){
                game_data_get_deck_card (&card_data, player_use, i);
                card_data_get (cards+i, card_data.index);
                if (card_data.type>=CARD_BASIC_DEFENSE_L1 && card_data.type<=CARD_BASIC_DEFENSE_L3){
                    choose[i]= 1;
                }
            }
            //------
            gui_show_card (cards, level_skill, "Card in DECK:");
            //------
            for (int32_t i=level_skill; i>=0; i--){
                if (choose[i]==1){
                    deck_data_draw_cards (player_use, 1);
                }else if (choose[i]==-1){
                    deck_data_move_card (player_use, i, CARD_SPACE_THROW);
                }
            }
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:{
            status_kaguya_skill_area_set (card_idx[0], 4-level_attach);
            card_data_set (card_idx[0], 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[1], 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:{
            action_attack (level_skill, level_attach, player_use, player_des);
            if (skill_move_use_hp_card_idx != CARD_ORIGINAL){
                action_lose_hp (1, -1, player_des, player_use);
            }
            break;
        }
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:{
            int32_t def= player_data.defense;
            player_data_get (&player_data, player_des);
            def-= player_data.defense;
            if (def<=0) break;
            int32_t area= status_kaguya_use_evolution1_movement (player_use);
            action_move (area, skill_move_evolution_direction, player_des);
            break;
        }
        default:
            break;
    }
    card_data_get (&card_data, card_idx[0]);
    card_data_get (&card_data_attach, card_idx[1]);
    if (card_data.space == CARD_SPACE_HAND) card_data_set (card_idx[0], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    if (card_data_attach.space == CARD_SPACE_HAND) card_data_set (card_idx[1], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
}

// finish3_direction: 移動到使用者的-1 or 1
int32_t skill_kaguya_finish (int32_t card_idx, int32_t finish3_direction, int32_t player_use, int32_t player_des){
    if (finish3_direction) finish3_direction/= abs(finish3_direction);
    sCardData card_data;
    card_data_get (&card_data, card_idx);
    sPlayerData player_data;
    switch (card_data.type){
        case CARD_SKILL_FINISH1:{
            status_kaguya_skill_finish1 (player_use);
            card_data_set (card_idx, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        case CARD_SKILL_FINISH2:{
            action_defense (6, player_use);
            card_data_set (card_idx, 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        case CARD_SKILL_FINISH3:{
            player_data_get (&player_data, player_use);
            int32_t delta= player_data.pos + finish3_direction;
            player_data_get (&player_data, player_des);
            delta-= player_data.pos;
            action_move (abs(delta), delta, player_des);
            action_attack (3, 1, player_use, player_des);
            card_data_set (card_idx, 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER_ORIGINAL);
            status_kaguya_skill_finish3 (player_use, player_des);
            break;
        }
        default:
            return -1;
    }
}

// attack_type: 0(attacked), 1(lose hp)
int32_t skill_kaguya_passive_attacked (int32_t delta, int32_t attack_type, int32_t player_attack, int32_t player_attacked){
    if (status_kaguya_skill_finish1_is_on()) return 0; // finish skill first
    if (attack_type==1) return delta;
    int32_t card_idx= -1;
    // -------
    sCardData cards[CARD_NUM];
    int32_t card_num;
    gui_action_get_card (cards, &card_num, player_attacked, CARD_SPACE_HAND, CARD_BASIC_ATTACK_L1, CARD_BASIC_ATTACK_L3);
    int32_t cnt;
    game_data_search_cards (cards+card_num, &cnt, player_attacked, CARD_SPACE_HAND, CARD_COST_COMMON, -1);
    card_num+= cnt;
    int32_t type;
    card_idx= gui_choose_card(&type, cards, card_num, "ATTACKED. Throw a card to attack and pull another.");
    // -------
    if (card_idx<0) return delta;
    int32_t level= status_kaguya_use_defense_card_as_attack (card_idx, player_attacked);
    action_attack (level, ACTION_NO_AREA, player_attacked, player_attack);
    card_data_set (card_idx, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
    deck_data_draw_cards (player_attacked, 1);
    return delta;
}

int32_t skill_kaguya_round_start (int32_t player){
    sCardData card_datas[CARD_NUM];
    int32_t card_num= 0;
    game_data_search_cards (card_datas, &card_num, player, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, -1);
    sPlayerData player_data;
    player_data_get (&player_data, player);

    // int32_t mode= GAMEMODE_1V1;
    int32_t player_max= PLAYER2;
    int32_t level= 0;
    for (int32_t i=0; i<card_num; i++){
        if (card_data_is_evolution (card_datas[i].index)) continue;
        card_data_set (card_datas[i].index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        level= card_data_get_level (card_datas[i].index);
        switch (card_datas[i].type){
            case CARD_SKILL_MOVEMENT_BASE_L2:
            case CARD_SKILL_MOVEMENT_BASE_L3:{
                int32_t area= status_kaguya_skill_area_get (card_datas[i].index);
                for (int32_t p=PLAYER1; p<=PLAYER2; p++){
                    if (p==player) continue;
                    int32_t pos= player_data.pos;
                    player_data_get (&player_data, p);
                    pos-= player_data.pos;
                    pos= abs(pos);
                    if (pos > area) action_attack (level*2, ACTION_NO_AREA, player, p);
                }
                break;
            }
            case CARD_SKILL_FINISH2:{
                for (int32_t p=PLAYER1; p<=PLAYER2; p++){
                    if (p==player) continue;
                    int32_t def= player_data.defense;
                    player_data_get (&player_data, p);
                    def-= player_data.defense;
                    if (def>0) action_lose_hp (def, -1, player, p);    
                }
            }
            case CARD_SKILL_FINISH3:{
                int32_t des= status_kaguya_skill_finish3_des_get();
                int32_t direction= player_data.pos;
                player_data_get (&player_data, des);
                direction-= player_data.pos;
                direction/= abs(direction);
                // -----
                direction= gui_choose_move_direction ("Choose the direction you want the opponent move to. (count from your position) (SKILL FINISH3)");
                // ------
                player_data_get (&player_data, player);
                direction= direction + player_data.pos;
                player_data_get (&player_data, des);
                direction-= player_data.pos;
                action_move (abs(direction), direction, des);
                action_attack (3, 1, player, des);
                break;
            }
            default:
                break;
        }
        card_data_set (card_datas[i].index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    }
    status_kaguya_round_start();
    return 0;
}


int32_t skill_kaguya_round_clear (int32_t player){
    if (!player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_DEFENSE_EVOLUTION_L1, player)) return 0;
    sPlayerData player_data;
    player_data_get (&player_data, player);
    int32_t pull= player_data.defense / 3;
    if (pull) deck_data_draw_cards (player, pull);
    return 0;
}


int32_t skill_kaguya_round_end (int32_t player){
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_ATTACK_EVOLUTION_L2, player)) action_defense (2, player);
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_DEFENSE_EVOLUTION_L2, player)) action_defense (2, player);
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_MOVEMENT_EVOLUTION_L2, player)) action_defense (2, player);
    return 0;
}
# include "main.h"
# include "game_action_skill_mulan.h"
# include "game_action_basic.h"
# include "game_data.h"
# include "gui_game_choose.h"

int32_t skill_mulan (int32_t card_idx[MULAN_CARD_IDX_NUM], int32_t mulan_action[MULAN_ACTION_IDX_NUM], int32_t player_use, int32_t player_des){
    sCardData card_data;
    sCardData card_data_attach;
    card_data_get (&card_data, card_idx[0]);
    card_data_get (&card_data_attach, card_idx[1]);
    int32_t level_skill= card_data_get_level (card_data.index);
    int32_t level_attach= card_data_get_level (card_data_attach.index);
    if (level_attach && card_data_is_skill(card_data_attach.index)){
        debug_print ("error: wrong attach card\n");
        return -1;
    }
    if (!card_data_is_skill (level_skill)){
        debug_print ("error: wrong skill card\n");
        return -1;
    }
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    player_data_get (&player_data_use, player_use);
    player_data_get (&player_data_des, player_des);
    int32_t token= 0;
    int32_t direction= 0;
    switch (card_data.type) {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
            token= skill_mulan_evolution1 (mulan_action[MULAN_ACTION_IDX_ATTACK_EVOLUTION_TOKEN], player_use);
            if (action_attack(level_skill+level_attach+token, 1, player_use, player_des)<0) return -1;
            direction= player_data_use.pos - player_data_des.pos;
            if (mulan_action[MULAN_ACTION_IDX_ATTACK_MOVE]){
                action_move (2, direction, player_des);
            }
            if (map_data_is_at_edge(player_des)){
                if (mulan_action[MULAN_ACTION_IDX_THROW_DES]) skill_mulan_throw_des_card(player_des);
            }
            break;
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
            action_defense(level_attach, player_use);
            status_mulan_defense_token_accept_add (level_skill);
            break;
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
            if (action_attack(level_skill, 1, player_use, player_des)<0) return -1;
            // token= skill_mulan_evolution1_attack (CARD_SKILL_MOVEMENT_EVOLUTION_L1, mulan_action[MULAN_ACTION_IDX_ATTACK_EVOLUTION_TOKEN], player_use);
            direction= player_data_des.pos - player_data_use.pos;
            action_move (level_attach, direction, player_des);
            direction= player_data_des.pos - player_data_use.pos;
            if (direction>0) direction++;
            else direction--;
            action_move (direction, direction, player_use);
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        default:
            debug_print ("error: wrong card\n");
            return -1;
    }
}

int32_t skill_mulan_throw_des_card (int32_t player_des){
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    game_data_search_cards (cards, &card_num, player_des, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    int32_t r= rand()%card_num;
    card_data_set (cards[r].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

int32_t skill_mulan_token_use (int32_t card_type, int32_t token, int32_t player){
    int32_t token_use= 0;
    sPlayerData player_data;
    player_data_get (&player_data, player);
    int32_t card_type_idx= card_data_get_index (player, card_type);
    if (card_type==CARD_ORIGINAL || player_data.card_on[card_type_idx]){
        token_use= MIN (token, 3);
        token_use= MIN (token_use, player_data.token);
    }
    // 花掉
    player_data.token-= token_use;
    return token_use;
}

int32_t skill_mulan_evolution1 (int32_t token, int32_t player){
    return status_mulan_token_add (-1*token, player);
}

int32_t skill_mulan_finish (int32_t card_idx, int32_t finish2_direction, int32_t player_use, int32_t player_des){
    if (finish2_direction) finish2_direction/= abs(finish2_direction);
    sPlayerData player_data;
    sCardData card_data;
    card_data_get (&card_data, card_idx);
    switch (card_data.type){
        case CARD_SKILL_FINISH1:
            status_mulan_finish1_on();
            break;
        case CARD_SKILL_FINISH2:
            player_data_get (&player_data, player_des);
            int32_t pos= player_data.pos + finish2_direction;
            player_data_get (&player_data, player_use);
            int32_t direction= pos - player_data.pos;
            if (action_move (direction, direction, player_use)<0) return -1;
            status_mulan_token_add (3, player_use);
            break;
        case CARD_SKILL_FINISH3:
            player_data_get (&player_data, player_use);
            status_mulan_token_add (-1*player_data.token, player_use);
            break;
        default:
            debug_print ("error: wrong card\n");
            return -1;
    }
    card_data_set (card_idx, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
    return 0;
}

int32_t skill_mulan_passive_attacked (int32_t attack_delta, int32_t player){
    int32_t card_throw= CARD_ORIGINAL;
    // -----
    sCardData cards[CARD_NUM];
    int32_t cnt;
    int32_t type;
    game_data_search_cards (cards, &cnt, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    char mes[100]= "Choose the card you want to throw to reduse the damage.";
    sprintf (mes, " (max damage: %d)", attack_delta);
    card_throw= gui_choose_card (&type, cards, cnt, mes);
    // -----
    int32_t level= card_data_get_level(card_throw);
    if (level<0) return 0;
    card_data_set (card_throw, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
    status_mulan_token_add (level, player);
    return level;
}

int32_t skill_mulan_round_start (int32_t player){
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_ATTACK_EVOLUTION_L2, player)) status_mulan_token_add (1, player);
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_DEFENSE_EVOLUTION_L2, player)) status_mulan_token_add (1, player);
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_MOVEMENT_EVOLUTION_L2, player)) status_mulan_token_add (1, player);
    return 0;
}

int32_t skill_mulan_round_end (int32_t player){
    sPlayerData player_data;
    player_data_get (&player_data, player);
    int32_t pull= status_mulan_use_finish1() * 4;

    int32_t defense_pull_token= 0;
    if (status_mulan_defense_token_accept_get ()) {
        defense_pull_token= gui_choose_token (MIN(status_mulan_defense_token_accept_get (), player_data.token), player, 
                                            "How much token you want to use for pulling cards.");
    }
    int32_t defense_evolution1_card_idx_throw= -1;
    if (player_data_card_is_on(-1, CARD_SKILL_DEFENSE_EVOLUTION_L1, player)){
        int32_t choose= gui_choose_move_yes_or_no("Dotou want to throw a card for pulling another?");
        if (choose){
            sCardData cards[CARD_NUM];
            int32_t cnt;
            int32_t type;
            game_data_search_cards (cards, &cnt, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
            defense_evolution1_card_idx_throw= gui_choose_card (&type, cards, cnt, "Choose the card to throw.");
        }
    }
    if (defense_pull_token>0){
        pull+= status_mulan_token_add (-1*defense_pull_token, player);
    }
    int32_t card_type_idx= card_data_get_index (player, CARD_SKILL_DEFENSE_EVOLUTION_L1);
    if (defense_evolution1_card_idx_throw!=CARD_ORIGINAL){
        if (!player_data.card_on[card_type_idx]){
            debug_print ("error: player %d do not have CARD_SKILL_DEFENSE_EVOLUTION_L1\n", player);
            return -1;
        }

    }
    deck_data_draw_cards (player, pull);
}
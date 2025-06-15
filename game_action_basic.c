# include "main.h"
# include "game_action_basic.h"
# include "game_data.h"
# include "game_action_skill_kaguya.h"
# include "gui_game_choose.h"
# include "game_action_skill_snow_white.h"
# include "game_action_skill_match_girl.h"

int32_t action_attack (int32_t delta, int32_t area, int32_t player_use, int32_t player_des){
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    if (player_data_get (&player_data_use, player_use)<0) return -1;
    if (player_data_get (&player_data_des, player_des)<0) return -1;
    
    if (abs(player_data_use.pos - player_data_des.pos) > area){
        debug_print ("error: too long destination: use at %d, des at %d. attack area %d\n", player_data_use.pos, player_data_des.pos, area);
        return -1;
    }
    switch (player_data_des.character){
        case CHARACTER_KAGUYA:
            delta= skill_kaguya_passive_attacked (delta, 0, player_use, player_des);
            break;

        case CHARACTER_MATCH_GIRL: {
            int32_t move_direction=0;
            if(delta>player_data_des.defense)move_direction=gui_choose_move_direction ("輸入你想要移動的方向：");
            skill_match_girl_movement_evolution(delta, player_des,move_direction);
        }
        default:
            break;
    }
    player_data_des.defense-= delta;
    if (player_data_des.defense<0){
        player_data_des.hp+= player_data_des.defense;
        player_data_des.defense= 0;
    }
    player_data_set (player_des, player_data_des);
}

int32_t action_defense (int32_t delta, int32_t player){
    sPlayerData player_data;
    if (player_data_get (&player_data, player)<0) return -1;
    player_data.defense+= delta;
    player_data.defense= MIN (player_data.defense, player_data.defense_max);

    player_data_set (player, player_data);
    return 0;
}

int32_t action_move (int32_t delta, int32_t direction, int32_t player){
    sPlayerData player_data[PLAYER_NUM];
    for (int32_t i=PLAYER1; i<=PLAYER2; i++){
        player_data_get (&(player_data[i]), i);
    }
    direction/= abs(direction);
    int32_t des= player_data[player].pos + direction*delta;
    skill_snow_white_movement_evolution(player,direction, delta);
    while (map_data_cannot_move(0, des, player)){
        int32_t stay= player_data[player].pos - des;
        stay/= abs(stay);
        des+= stay;
    }

    player_data[player].pos= des;
    player_data_set (player, player_data[player]);
    map_data_refresh ();
    return 0;
}

// area= -1: no area
int32_t action_lose_hp (int32_t delta, int32_t area, int32_t player_use, int32_t player_des){
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    if (player_data_get (&player_data_use, player_use)<0) return -1;
    if (player_data_get (&player_data_des, player_des)<0) return -1;

    if (area!=-1 && abs(player_data_use.pos - player_data_des.pos) > area){
        debug_print ("error: too long destination: use at %d, des at %d. attack area %d\n", player_data_use.pos, player_data_des.pos, area);
        return -1;
    }

    switch (player_data_des.character){
        case CHARACTER_KAGUYA:
            delta= skill_kaguya_passive_attacked (delta, 1, player_use, player_des);
            break;
        default:
            break;
    }

    player_data_des.hp-= delta;
    player_data_set (player_des, player_data_des);
}

int32_t action_modefy_power (int32_t delta, int32_t player){
    sPlayerData player_data;
    if (player_data_get (&player_data, player)<0) return -1;
    player_data.power+= delta;
    if (player_data.power<0) return -1;
    player_data.power= MIN (player_data.power, player_data.power_max);

    player_data_set (player, player_data);
    return 0;
}

int32_t action_gain_finish (int32_t player){
    sPlayerData player_data;
    player_data_get (&player_data, player);
    if (player_data.hp > player_data.hp_finish) return 0;
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_FINISH1, player)) return 0;
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_FINISH2, player)) return 0;
    if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_FINISH3, player)) return 0;
    int32_t finish_card_idx= card_data_get_index (player, CARD_SKILL_FINISH1);
    // ------
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    int32_t cnt;
    game_data_search_cards (cards + card_num, &cnt, player, CARD_SPACE_SHOP, CARD_SKILL_FINISH1, -1);
    card_num+= cnt;
    game_data_search_cards (cards + card_num, &cnt, player, CARD_SPACE_SHOP, CARD_SKILL_FINISH2, -1);
    card_num+= cnt;
    game_data_search_cards (cards + card_num, &cnt, player, CARD_SPACE_SHOP, CARD_SKILL_FINISH3, -1);
    card_num+= cnt;
    int32_t type;
    finish_card_idx= gui_choose_card (&type, cards, card_num, "Choose your finish skill.");
    // ------   
    card_data_set (finish_card_idx, 1 , CARD_SPACE_HAND, CARD_ORIGINAL, player);
    return 0;
}
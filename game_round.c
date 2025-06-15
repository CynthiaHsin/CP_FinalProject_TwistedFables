# include "game_round.h"
# include "game_action.h"
# include "game_data.h"
# include "gui_game_render.h"
# include "red_riding_robot.h"
# include "snow_white_robot.h"
# include "game_action_skill_match_girl.h"

extern int32_t gCharacters[];

int32_t game_round(){
    sStatusData status;
    status_data_get (&status);

    int32_t mode= status.mode;
    if (mode != GAMEMODE_1V1) return -1; // not yet
    int32_t winner= game_round_gameend_parse (mode);
    debug_print ("winner: %d\n", winner);
    if (winner!=PLAYER_UNDEFINED){
        return winner;
    }
    for (int32_t i=0; i<2; i++){
        // debug_print ("player_order %d: %d\n", i, status.player_order[i]);
        int32_t player= status.player_order[i];
        // 回合開始階段
        game_round_start (mode, player);
        // 判斷是否結束
        winner= game_round_gameend_parse (mode);
        if (winner!=PLAYER_UNDEFINED){
            return winner;
        }
        // 清理階段
        game_round_clear (mode, player);
        // 判斷是否結束
        winner= game_round_gameend_parse (mode);
        if (winner!=PLAYER_UNDEFINED){
            return winner;
        }
        // 行動階段
        game_round_action (mode, player);
        // 判斷是否結束
        winner= game_round_gameend_parse (mode);
        if (winner!=PLAYER_UNDEFINED){
            return winner;
        }
        // 結束階段
        game_round_end (mode, player);
        // 判斷是否結束
        winner= game_round_gameend_parse (mode);
        if (winner!=PLAYER_UNDEFINED){
            return winner;
        }
    }
    status_data_next_round();
}

int32_t game_round_start (int32_t mode, int32_t player){
    sCardData cards[CARD_NUM];
    int32_t cards_num= 0;
    sPlayerData player_data;
    player_data_get (&player_data, player);
    switch (player_data.character){
        case CHARACTER_RED_RIDING_HOOD:
            skill_red_riding_hood_round_start (player);
            break;
        case CHARACTER_MULAN:
            skill_mulan_round_start (player);
            break;
        case CHARACTER_KAGUYA:
            skill_kaguya_round_start (player);
            break;
        default:
            // debug_print ("mark: undefined round start character: %d\n", player_data.character);
            break;
    }
    game_data_search_cards (cards, &cards_num, player, CARD_SPACE_USE, CARD_ORIGINAL, CARD_COST_ORIGINAL);
    for (int32_t i=0; i<cards_num; i++){
        card_data_print (cards[i].index, 1);
        // not yet : cause because skill
    }
    return 0;
}

int32_t game_round_clear (int32_t mode, int32_t player){
    
    // 特別規則
    sPlayerData player_data;
    player_data_get (&player_data, player);
    switch (player_data.character){
        case CHARACTER_KAGUYA:
            skill_kaguya_round_clear (player);
            break;
        default:
            break;
    }

    // 棄掉所有出牌區的牌
    sCardData cards[CARD_NUM];
    int32_t cards_num= 0;
    game_data_search_cards (cards, &cards_num, player, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, CARD_COST_ORIGINAL);
    for (int32_t i=0; i<cards_num; i++){
        card_data_set (cards[i].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
        debug_print ("throw: (%d)\n", cards[i].index);
    }

    // defense = 0
    player_data_get (&player_data, player);
    player_data.defense= 0;
    player_data_set (player, player_data);

    return 0;
}

int32_t game_round_action (int32_t mode, int32_t player){
    // int32_t ui_round (int32_t player);
    if (player==PLAYER1) game_scene_loop(gCharacters);
    else{
        int32_t arr[CARD_NUM];
        int32_t n;
        sCardData hand_card[CARD_NUM];
        game_data_search_cards (hand_card, &n, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
        for (int32_t i=0; i<n; i++) arr[i]= hand_card[i].index;
        int32_t best_card[n];
        int32_t best_card_skill[n];
        int32_t best_card_defense[n];
        int32_t player_use= PLAYER2;
        int32_t player_des= PLAYER1;
        snow_white_robot (arr, n, best_card, best_card_skill, best_card_defense, player_use, player_des);
        int32_t skill_cards[Snow_White_CARD_IDX_NUM]= {-1, -1, -1, -1, -1, -1};
        sCardData card_data;

        int32_t direction;
        sPlayerData pd;
        player_data_get (&pd, player_use);
        direction= pd.pos;
        player_data_get (&pd, player_des);
        direction-= pd.pos;
        if (map_data_is_at_edge(player)) direction*= -1;

        for (int32_t i=0; i<n; i++){
            card_data_get (&card_data, best_card[i]);
            if (card_data.type>= CARD_BASIC_ATTACK_L1 && card_data.type <= CARD_BASIC_MOVEMENT_L3){
                game_action_use_basic_card (card_data.index, card_data.type, 0, direction, player_use, player_des);
            }else if (card_data.type== CARD_BASIC_COMMON){
                game_action_use_basic_card (card_data.index, CARD_BASIC_DEFENSE_L1, 0, 0, player_use, player_des);
            }else{
                skill_cards[Snow_White_CARD_IDX_SKILL]= best_card[i];
                skill_cards[Snow_White_CARD_IDX_ATTACH]= best_card_skill[i];
                skill_cards[Snow_White_CARD_IDX_POISON]= best_card_defense[i];
                skill_snow_white (skill_cards, direction, player_use, player_des);
            }
        }
        snow_white_buy_card (player);
    }
    return 0;
}

int32_t game_round_end (int32_t mode, int32_t player){

    // 特別規則
    sPlayerData player_data;
    player_data_get (&player_data, player);
    switch (player_data.character){
        case CHARACTER_KAGUYA:
            skill_kaguya_round_end (player);
            break;
        default:
            break;
    }

    // 能量重置為0
    player_data_get (&player_data, player);
    player_data.power= 0;
    player_data_set (player, player_data);

    // 棄掉所有手牌
    sCardData cards[CARD_NUM];
    int32_t cards_num= 0;
    game_data_search_cards (cards, &cards_num, player, CARD_SPACE_HAND, CARD_ORIGINAL, CARD_COST_ORIGINAL);

    int32_t card_idx[CARD_NUM];
    for (int32_t i=0; i<cards_num; i++) card_idx[i]= cards[i].index;
    switch (player_data.character)
    {
        case CHARACTER_SNOW_WHITE:
        if(PLAYER1==player)snow_white_poison_count(card_idx, cards_num, PLAYER2);
        else snow_white_poison_count(card_idx, cards_num, PLAYER1);
        break;
        case CHARACTER_MATCH_GIRL:
        if(PLAYER1==player)skill_match_girl_evolution2(PLAYER2);
        else skill_match_girl_evolution2(PLAYER1);
        break;
    }

    for (int32_t i=0; i<cards_num; i++){
        card_data_set (cards[i].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
        debug_print ("throw: (%d)\n", cards[i].index);
    }

    // 棄掉所有出牌區域內除了有持續效果的牌(如果為技能牌，其搭配的基本牌也不用棄掉)
    cards_num= 0;
    game_data_search_cards (cards, &cards_num, player, CARD_SPACE_USE, CARD_ORIGINAL, CARD_COST_ORIGINAL);
    switch (player_data.character)
    {
        case CHARACTER_SNOW_WHITE:
        {
            int32_t *card_snow_white;
            card_snow_white=malloc(cards_num*sizeof(int32_t));
            for(int32_t i=0;i<cards_num;i++)card_snow_white[i]=cards[i].index;
            if(PLAYER1==player)snow_white_poison_count(card_snow_white, cards_num, PLAYER2);
            else snow_white_poison_count(card_snow_white, cards_num, PLAYER1);
        }
        break;
        case CHARACTER_MATCH_GIRL:
        if(PLAYER1==player)skill_match_girl_evolution2(PLAYER2);
        else skill_match_girl_evolution2(PLAYER1);
        break;
    }
    for (int32_t i=0; i<cards_num; i++){
        card_data_set (cards[i].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
        debug_print ("throw: (%d)\n", cards[i].index);
    }

    // 抽出六張牌
    deck_data_draw_cards (player, HAND_CARDS_ROUND);
    
    // 木蘭的被動要最後用
    switch (player_data.character){
        case CHARACTER_MULAN:
            skill_mulan_round_end (player);
            break;
        default: break;
    }
    return 0;
}

// game_end: -1;  true: winner;  false: PLAYER_UNDEFINED
int32_t game_round_gameend_parse (int32_t mode){
    sPlayerData player_data;
    int32_t winner= PLAYER_UNDEFINED;
    sStatusData status_data;
    status_data_get (&status_data);
    if (status_data.game_end) return -1;
    // int32_t player= PLAYER1;
    // int32_t player_max= PLAYER2;
    if (mode==GAMEMODE_1V1){
        player_data_get (&player_data, PLAYER1);
        if (player_data.hp<=0){
            winner= PLAYER2;
            debug_print ("GAME END!! winner is %d", winner);
        }
        player_data_get (&player_data, PLAYER2);
        if (player_data.hp<=0){
            winner= PLAYER1;
            debug_print ("GAME END!! winner is %d", winner);
        }
    }else{
        return -1;
    }
    return winner;
}

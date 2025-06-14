# include "game_round.h"
# include "game_action.h"
# include "game_data.h"
# include "gui_game_render.h"

extern int32_t gCharacters[];

int32_t game_round(){
    sStatusData status;
    status_data_get (&status);

    int32_t mode= status.mode;
    if (mode != GAMEMODE_1V1) return -1; // not yet
    for (int32_t i=0; i<2; i++){
        int32_t player= status.player_order[i];
        // 回合開始階段
        game_round_start (mode, player);
        // 清理階段
        game_round_clear (mode, player);
        // 行動階段
        game_round_action (mode, player);
        // 結束階段
        game_round_end (mode, player);
        // 判斷是否結束
        int32_t winner= game_round_gameend_parse (mode);
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
    game_scene_loop(gCharacters);
    return 0;
}

int32_t game_round_end (int32_t mode, int32_t player){

    // 特別規則
    sPlayerData player_data;
    player_data_get (&player_data, player);
    switch (player_data.character){
        case CHARACTER_MULAN:
            // ------
            printf ("木蘭決定要不要用技能");
            // ------
            // skill_mulan_round_end (player, );
            break;
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
    if (player_data.character == CHARACTER_SNOW_WHITE) 
    snow_white_poison_count (card_idx, cards_num, player);

    for (int32_t i=0; i<cards_num; i++){
        card_data_set (cards[i].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
        debug_print ("throw: (%d)\n", cards[i].index);
    }

    // 棄掉所有出牌區域內除了有持續效果的牌(如果為技能牌，其搭配的基本牌也不用棄掉)
    cards_num= 0;
    game_data_search_cards (cards, &cards_num, player, CARD_SPACE_USE, CARD_ORIGINAL, CARD_COST_ORIGINAL);
    for (int32_t i=0; i<cards_num; i++){
        card_data_set (cards[i].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
        debug_print ("throw: (%d)\n", cards[i].index);
    }

    // 抽出六張牌
    deck_data_draw_cards (player, HAND_CARDS_ROUND);
    
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

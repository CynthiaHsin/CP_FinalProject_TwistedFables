# include "main.h"
# include "game_data.h"
# include "game_action.h"
# include "gui_sdl_config.h"
# include "gui_img_data.h"
# include "gui_game_render.h"
# include "gui_game_choose.h"


int32_t gui_action_focus (int32_t player){
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    int32_t card_type= CARD_UNDEFINED;

    // 手牌丟一張
    game_data_search_cards (cards, &card_num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    int32_t card_delete_hand= gui_action_choose_card (&card_type, NULL, NULL, cards, card_num, "Choose the card you wand to delete.");
    
    // 棄牌丟一張
    game_data_search_cards (cards, &card_num, player, CARD_SPACE_THROW, CARD_ORIGINAL, -1);
    int32_t card_delete_throw= gui_action_choose_card (&card_type,  NULL, NULL, cards, card_num, "Choose the card you wand to delete.");
    
    return game_action_focus (card_delete_hand, card_delete_throw, player);
}

int32_t gui_action_use_basic (int32_t player){
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    int32_t cnt= 0;
    int32_t card_type= CARD_BASIC_ATTACK_L1;

    while (card_type <= CARD_BASIC_COMMON){
        game_data_search_cards (cards+card_num, &cnt, player, CARD_SPACE_HAND, card_type, -1);
        card_num += cnt;
        card_type++;
    }

    card_type= CARD_UNDEFINED;
    int32_t move_direction, player_des;
    int32_t choose= gui_action_choose_card (&card_type, &move_direction, &player_des, cards, card_num, "Choose the basic card you want to use.\n");
    
    int32_t token= 0;


}
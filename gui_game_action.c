# include "main.h"
# include "game_data.h"
# include "game_action.h"
# include "gui_sdl_config.h"
# include "gui_img_data.h"
# include "gui_game_render.h"

// return i meaning cards[i]
int32_t gui_action_choose_card (int32_t *pCard_type, sCardData cards[], int32_t card_num, char * text){

    // int gap = 20, w = 105, h = 160;
    // int base_x = 50;
    // int base_y = 50;

    // for (int i = 0; i < num; ++i) {
    //     int32_t card_id = cards[i].index;
    //     SDL_Rect d = { base_x + i * (w + gap), base_y, w, h };
    //     SDL_Texture* tex = card_data_get_texture(cards[i].type, cards[i].player);
    //     if (tex != NULL) SDL_RenderCopy(ren, tex, NULL, &d);
    // }
}

int32_t gui_action_choose_token (int32_t token_use_max, int32_t player){
    
}

int32_t gui_action_focus (int32_t player){
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    int32_t card_type= CARD_UNDEFINED;

    // 手牌丟一張
    game_data_search_cards (cards, &card_num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    int32_t card_delete_hand= gui_action_choose_card (&card_type, cards, card_num, "Choose the card you wand to delete.");
    
    // 棄牌丟一張
    game_data_search_cards (cards, &card_num, player, CARD_SPACE_THROW, CARD_ORIGINAL, -1);
    int32_t card_delete_throw= gui_action_choose_card (&card_type, cards, card_num, "Choose the card you wand to delete.");
    
    return game_action_focus (card_delete_hand, card_delete_throw, player);
}

int32_t gui_action_use_basic (int32_t player){
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    int32_t cnt= 0;

    game_data_search_cards (cards, &cnt, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    int32_t choose= -1;
    int32_t card_type= CARD_UNDEFINED;

}
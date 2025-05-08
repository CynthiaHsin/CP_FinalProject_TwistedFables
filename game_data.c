# include "main.h"
# include "game_data.h"

int32_t game_data_init (int32_t mode){
    card_data_init (mode);
    deck_data_init (mode);
    return 0;
}

int32_t game_data_get_card (sCardData *pCard, int32_t idx){
    return card_data_get (pCard, idx);
}

int32_t game_data_get_deck_card (sCardData *pCard, int32_t player, int32_t idx){
    return deck_data_get_card (pCard, player, idx);
}

int32_t game_data_deck_card_delete (int32_t player, int32_t idx){
    return deck_data_move_card (player, idx, CARD_SPACE_DELETE);
}

int32_t game_data_deck_card_take (int32_t player, int32_t idx){
    return deck_data_move_card (player, idx, CARD_SPACE_HAND);
}
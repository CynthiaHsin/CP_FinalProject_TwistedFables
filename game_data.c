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
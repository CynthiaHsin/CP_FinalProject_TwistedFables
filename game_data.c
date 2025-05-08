# include "main.h"
# include "game_data.h"

int32_t game_data_init(){
    card_data_init();
    return 0;
}

int32_t game_data_get_card (sCardData *pCard, int32_t idx){
    return card_data_get (pCard, idx);
}
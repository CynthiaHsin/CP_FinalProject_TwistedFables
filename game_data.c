# include "main.h"
# include "game_data.h"

int32_t game_data_init (int32_t mode, int32_t characters[]){

    // status init
    status_data_init (mode);
    
    // card init
    card_data_init (mode);

    // player init (special cards and tokens)
    int32_t player= PLAYER1;
    int32_t player_max= PLAYER2;
    if (mode != GAMEMODE_1V1) return -1; // not yet
    for (int32_t i=player; i<=player_max; i++){
        player_data_set_character (i, characters[i]);
    }
    player_data_init (mode);
    // deck init
    deck_data_init (mode);
    
    map_data_init (mode);
    return 0;
}

int32_t game_data_get_card (sCardData *pCard, int32_t idx){
    return card_data_get (pCard, idx);
}

int32_t game_data_search_cards (sCardData cards[], int32_t *pGet_num, int32_t player, int32_t space, int32_t type, int32_t cost){
    int32_t cnt= 0;
    sCardData card;

    for (int32_t i=0; i<CARD_NUM; i++){
        if (card_data_get (&card, i)<0) return -1;
        if (player!=PLAYER_ORIGINAL && card.player!=player) continue;
        if (space!=CARD_SPACE_ORIGINAL && card.space!=space) continue;
        if (type!=CARD_ORIGINAL && card.type!=type) continue;
        if (cost!=-1 && card.cost>cost) continue;
        card_cpy (&(cards[cnt]), card);
        cnt++;
    }
    *pGet_num= cnt;
    
    return cnt;
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

int32_t game_data_get_player (sPlayerData *pPlayer_data, int32_t player){
    return player_data_get (pPlayer_data, player);
}

int32_t game_data_deck_card_fold (int32_t player, int32_t idx){
    return deck_data_move_card (player, idx,CARD_SPACE_THROW);
}

int32_t game_data_deck_card_deck (int32_t player, int32_t idx){
    return deck_data_move_card (player, idx,CARD_SPACE_DECK);
}
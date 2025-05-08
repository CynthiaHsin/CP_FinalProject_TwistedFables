# include "main.h"
# include "game_data.h"

sDeckData deck_data[PLAYER_NUM];

int32_t deck_data_init (int32_t mode){
    
    int32_t player= PLAYER1;
    int32_t player_max;
    if (mode==GAMEMODE_1V1) player_max= PLAYER2; 

    for (int32_t i=player; i<=player_max; i++){
        deck_data_refresh (i);
    }
    
    return 0;
}

int32_t deck_data_refresh (int32_t player){
    debug_print ("deck_data_refresh called.\n");
    sCardData card;
    int32_t card_num= deck_data[player].card_num;
    for (int32_t i=0; i<CARD_NUM; i++){
        card_data_get (&card, i);
        if (card.type==CARD_UNDEFINED) break;
        if (card.player==player && card.space==CARD_SPACE_THROW){
            card_data_set (i, 1, CARD_SPACE_DECK, CARD_ORIGINAL, PLAYER_ORIGINAL);
            deck_data[player].cards[card_num]= i;
            card_num++;
            continue;
        }
    }
    deck_data[player].card_num= card_num;
    deck_data_shuffle (player);
}

int32_t deck_data_shuffle (int32_t player){

    int32_t card_num= deck_data[player].card_num;
    int32_t shuffle_tmp[card_num];
    for (int32_t i=0; i<card_num; i++){
        shuffle_tmp[i]= -1;
    }

    // shuffle
    
    for (int32_t i=0; i<card_num; i++){
        int32_t r= rand()%card_num;
        while (shuffle_tmp[r]!=-1){
            r++;
            r%= card_num;
        }
        shuffle_tmp[r]= deck_data[player].cards[i];
    }

    // tmp
    for (int32_t i=0; i<card_num; i++){
        deck_data[player].cards[i]= shuffle_tmp[i];
    }

    return 0;
}

int32_t deck_data_print (int32_t player){
    int32_t card_num= deck_data[player].card_num;
    char card_type_name[CARD_TYPE_NAME_MAX]= {0};
    debug_print ("player %d, deck card num: %d\n", player, card_num);
    for (int32_t i=card_num-1; i>=0; i--){
        card_data_get_type_name (card_type_name, deck_data[player].cards[i]);
        debug_print ("player %d: (%d) %s\n", player, deck_data[player].cards[i], card_type_name);
    }
}

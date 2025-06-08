# include "main.h"
# include "game_data_card.h"
# include "game_data_deck.h"

# define DECK_TOP(player, i) (deck_data[player].card_num -1 -i)

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

// 刷新
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

// 洗牌
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
    for (int32_t i=0; i<card_num; i++){
        card_data_get_type_name (card_type_name, deck_data[player].cards[DECK_TOP(player, i)]);
        debug_print ("player %d: (%d) %s\n", player, deck_data[player].cards[DECK_TOP(player, i)], card_type_name);
    }
}

int32_t deck_data_get_card (sCardData *pCard, int32_t player, int32_t idx){
    return card_data_get (pCard, deck_data[player].cards[DECK_TOP(player, idx)]);
}

int32_t deck_data_move_card (int32_t player, int32_t idx, int32_t space){
    if (deck_data[player].card_num==0){ 
        debug_print ("error: no card to move, player (%d), idx (%d)\n", player, idx);
        return -1;
    }
    int32_t card_idx= deck_data[player].cards[DECK_TOP(player, idx)];
    card_data_set (card_idx, 1, space, CARD_ORIGINAL, CARD_ORIGINAL);
    deck_data[player].cards[DECK_TOP(player, idx)]= -1;
    deck_data[player].card_num--;
    if (idx){
        for (int32_t i=DECK_TOP(player, idx); i<deck_data[player].card_num; i++){
            deck_data[player].cards[i]= deck_data[player].cards[i+1];
        }
    }
    return 0;
}

int32_t deck_data_draw_cards (int32_t player, int32_t num){
    if (deck_data[player].card_num < num){
        deck_data_refresh (player);
    }

    for (int32_t i=0; i<num; i++){
        deck_data_move_card (player, 0, CARD_SPACE_HAND);
    }

    return 0;
}

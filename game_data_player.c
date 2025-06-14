# include "main.h"
# include "game_data_player.h"
# include "game_data_card.h"
# include "game_action_basic.h"

sPlayerData player_data[PLAYER_NUM];

int32_t player_data_write_back(int32_t player, sPlayerData src) {
    return player_data_cpy(&(player_data[player]), src);
}

int32_t player_data_set_character (int32_t player, int32_t character){
    player_data[player].character= character;
}

int32_t player_data_set_card (int32_t player, int32_t card_idx){
    player_data[player].card_on[card_idx]= 1;
    return 0;
}

int32_t player_data_set (int32_t player, sPlayerData src){
    int32_t re= player_data_cpy (&(player_data[player]), src);
    if (player_data[player].hp <= player_data[player].hp_finish){
        // player_data_print (player);
        // debug_print ("111111\n");
        action_gain_finish (player);
    }
    return re;
}


int32_t player_data_init (int32_t mode){

    int32_t player= PLAYER1;
    int32_t player_max;
    if (mode==GAMEMODE_1V1) player_max= PLAYER2;
    for (int32_t i=0; i<CARD_NUM; i++){
        player_data[PLAYER1].card_on[i]= 0;
        player_data[PLAYER2].card_on[i]= 0;
    }

    for (int32_t i=player; i<=player_max; i++){
        player_data[i].player= i;
        player_data[i].token= 0;
        player_data[i].defense= 0;
        player_data[i].power= 0;
        player_data[i].power_max= POWER_MAX;
        switch (player_data[i].character){
            case CHARACTER_RED_RIDING_HOOD:
                player_data[i].hp_max= 30;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 15;
                player_data[i].token_max= 0;
                break;
            case CHARACTER_SNOW_WHITE:
                player_data[i].hp_max= 34;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 17;
                player_data[i].token_max= 0;
                // 中毒牌
                card_add (CARD_POISON_NUM, CARD_SPACE_DECK_POISON, CARD_POISON_L1, i);
                card_add (CARD_POISON_NUM, CARD_SPACE_DECK_POISON, CARD_POISON_L2, i);
                card_add (CARD_POISON_NUM, CARD_SPACE_DECK_POISON, CARD_POISON_L3, i);
                break;
            case CHARACTER_SLEEPING_BEAUTY:
                player_data[i].hp_max= 42;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 21;
                player_data[i].token_max= 9;
                break;
            case CHARACTER_ALICE:
                player_data[i].hp_max= 32;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 16;
                player_data[i].token_max= 0;
                break;
            case CHARACTER_MULAN:
                player_data[i].hp_max= 34;
                player_data[i].defense_max= 3;
                player_data[i].hp_finish= 17;
                player_data[i].token_max= 12;
                break;
            case CHARACTER_KAGUYA:
                player_data[i].hp_max= 32;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 16;
                player_data[i].token_max= 0;
                break;
            case CHARACTER_LITTLE_MERMAID:
                player_data[i].hp_max= 36;
                player_data[i].defense_max= 3;
                player_data[i].hp_finish= 18;
                player_data[i].token_max= 4;
                break;
            case CHARACTER_MATCH_GIRL:
                player_data[i].hp_max= 36;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 18;
                player_data[i].token_max= 0;
                // 火柴牌
                card_add (CARD_MATCH_NUM, CARD_SPACE_DECK_MATCH, CARD_MATCH, i);
                break;
            case CHARACTER_DOROTHY:
                player_data[i].hp_max= 40;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 20;
                player_data[i].token_max= 12;
                break;
            case CHARACTER_SCHEHERAZADE:
                player_data[i].hp_max= 36;
                player_data[i].defense_max= 6;
                player_data[i].hp_finish= 18;
                player_data[i].token_max= 6;
                break;
            default:
                debug_print ("error: undefined character (%d)\n", player_data[i].character);
                break;
        }
        player_data[i].hp= player_data[i].hp_max;
        // 兩隊分邊站
        if (i%2) player_data[i].pos= -1;
        else player_data[i].pos= 1;
    }
}

int32_t player_data_print (int32_t player){
    debug_print ("---\n");
    debug_print ("player:\t%d\n",       player_data[player].player);
    debug_print ("character:\t%d\n",    player_data[player].character);
    debug_print ("token:\t%d\n",        player_data[player].token);
    debug_print ("token_max:\t%d\n",    player_data[player].token_max);
    debug_print ("hp:\t%d\n",           player_data[player].hp);
    debug_print ("hp_finish\t%d\n",     player_data[player].hp_finish);
    debug_print ("hp_max:\t%d\n",       player_data[player].hp_max);
    debug_print ("defense:\t%d\n",      player_data[player].defense);
    debug_print ("defense_max:\t%d\n",  player_data[player].defense_max);
    debug_print ("power:\t%d\n",        player_data[player].power);
    debug_print ("power_ma:\t%d\n",     player_data[player].power_max);
    debug_print ("pos:\t%d\n",          player_data[player].pos);
}

int32_t player_data_print_cardon (int32_t player){
    debug_print ("player %d card_on:\n", player);
    for (int32_t i=0; i<CARD_NUM; i++){
        if (player_data[player].card_on[i]){
            char card_type_name[CARD_TYPE_NAME_MAX]= {0};
            card_data_get_type_name (card_type_name, i);
            debug_print ("\t%s(%d)\n", card_type_name, i);
        }
    }
    debug_print ("\n");
}

int32_t player_data_cpy (sPlayerData *pPlayerData, sPlayerData src){
    int8_t *pA= (int8_t*)pPlayerData;
    int8_t *pB= (int8_t*)(&src);
    for (int32_t i=0; i<sizeof(sPlayerData); i++){
        pA[i]= pB[i];
    }
    return 0;
}

int32_t player_data_get (sPlayerData *pPlayerData, int32_t player){
    if (player>=PLAYER_NUM) return -1;
    return player_data_cpy (pPlayerData, player_data[player]);
}

int32_t player_data_card_is_on (int32_t card_idx, int32_t card_type, int32_t player){
    if (card_idx==CARD_ORIGINAL){
        card_idx= card_data_get_index (player, card_type);
    }
    return player_data[player].card_on[card_idx];
}

int32_t player_data_search_character (int32_t character){
    int32_t player= PLAYER1;
    int32_t player_max= PLAYER2;
    for (int32_t p=player; p<=player_max; p++){
        if (player_data[p].character==character) return p;
    }
    return PLAYER_UNDEFINED;
}
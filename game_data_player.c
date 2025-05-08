# include "main.h"
# include "game_data.h"

sPlayer player_data[PLAYER_NUM];

int32_t player_data_set_character (int32_t player, int32_t character){
    player_data[player].character= character;
}

int32_t player_data_init (int32_t mode){

    int32_t player= PLAYER1;
    int32_t player_max;
    if (mode==GAMEMODE_1V1) player_max= PLAYER2;

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
    }
}
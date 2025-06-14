# include "game.h"


int main(){
    srand(time(NULL));

    int32_t characters[PLAYER_NUM]= {0};
    int32_t mode;

    // basic datas, ask ui to return;= GAMEMODE_1V1;
    mode= GAMEMODE_1V1;
    characters[PLAYER1]= CHARACTER_RED_RIDING_HOOD;
    characters[PLAYER2]= CHARACTER_SNOW_WHITE;

    // gui_game_start (characters, &mode);

    // UI CALL
    // ui_init
    // ui_start_settings (int32_t *pMode, int32_t characters[]);

    // int32_t player= PLAYER1;
    // int32_t player_max;
    // if (mode==GAMEMODE_1V1) player_max= PLAYER2; 
    
    if (gui_game_start (characters, &mode)==-1) return -1;
    // game init
    game_data_init (mode, characters);


    debug_print ("player1: %d\n", characters[PLAYER1]);
    debug_print ("player2: %d\n", characters[PLAYER2]);
    int32_t cards[4]= {0};

    int32_t winner= PLAYER_UNDEFINED;
    while (winner==PLAYER_UNDEFINED){
        winner= game_round();
    }
    debug_print ("Game End. The winner is: %d\n", winner);
    // card_data_set (card_data_get_index(PLAYER1, CARD_SKILL_MOVEMENT_EVOLUTION_L1), 1, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, PLAYER1);
    // player_data_print_cardon (PLAYER1);
    // cards[0]= card_data_get_index (PLAYER1, CARD_SKILL_ATTACK_BASE_L1);
    // cards[2]= card_data_get_index (PLAYER1, CARD_SKILL_MOVEMENT_BASE_L1);
    // cards[1]= -1;
    // cards[3]= -1;
    // game_action_use_skill_card (cards, CARD_SKILL_ATTACK_BASE_L1, 0, 0, PLAYER1, PLAYER2);

    gui_game_end();
    // game start
}
# include "game.h"

int main(){
    srand(time(NULL));

    // basic datas, ask ui to return;
    int32_t mode= GAMEMODE_1V1;
    int32_t characters[PLAYER_NUM]= {0};
    characters[PLAYER1]= CHARACTER_MATCH_GIRL;
    characters[PLAYER2]= CHARACTER_SNOW_WHITE;

    // UI CALL
    // ui_start_settings (int32_t *pMode, int32_t characters[]);

    // int32_t player= PLAYER1;
    // int32_t player_max;
    // if (mode==GAMEMODE_1V1) player_max= PLAYER2; 
    
    // game init
    game_data_init (mode, characters);

    // game start
}
# include "main.h"
# include "game_data.h"

int main(){
    srand(time(NULL));
    int32_t mode= GAMEMODE_1V1;
    game_data_init (mode);
}
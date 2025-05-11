# include "main.h"
# include "game_data.h"

sStatusData status_data;

# define ORDER_PLAYERS 4

int32_t status_player_order_2v2[4][ORDER_PLAYERS]={
    {PLAYER1, PLAYER2, PLAYER3, PLAYER4},
    {PLAYER2, PLAYER3, PLAYER4, PLAYER1},
    {PLAYER3, PLAYER4, PLAYER1, PLAYER2},
    {PLAYER4, PLAYER1, PLAYER2, PLAYER3}
};

int32_t status_player_order_1v1[2][ORDER_PLAYERS]={
    {PLAYER1, PLAYER2, PLAYER_UNDEFINED, PLAYER_UNDEFINED},
    {PLAYER2, PLAYER1, PLAYER_UNDEFINED, PLAYER_UNDEFINED},
};

int32_t status_data_init (int32_t mode){
    status_data.mode= mode;
    status_data.round= 0;
    return 0;
}

int32_t status_data_next_round(){
    status_data.round++;
    if (status_data.mode==GAMEMODE_1V1){
        int32_t order= status_data.round % 2;
        for (int32_t i=0; i<ORDER_PLAYERS; i++){
            status_data.player_order[i]= status_player_order_1v1[order][i];
        }
    }
    return 0;
}

int32_t status_data_cpy (sStatusData *pStatusData, sStatusData src){
    int8_t *pA= (int8_t*)pStatusData;
    int8_t *pB= (int8_t*)(&src);
    for (int32_t i=0; i<sizeof(sPlayerData); i++){
        pA[i]= pB[i];
    }
    return 0;
}

int32_t status_data_get (sStatusData *pStatusData){
    return status_data_cpy (pStatusData, status_data);
}

int32_t status_data_get_mode (int32_t *pMode){
    *pMode= status_data.mode;
    return 0;
}
# include "main.h"
# include "game_data_status_mulan.h"
# include "game_data_player.h"

int32_t mulan_defense_token_accept;
int32_t mulan_finish1;

int32_t status_mulan_init(){
    mulan_defense_token_accept= 0;
    mulan_finish1= 0;
}

int32_t status_mulan_defense_token_accept_add (int32_t delta){
    mulan_defense_token_accept+= delta;
    return 0;
}

// return | delta token |
int32_t status_mulan_token_add (int32_t token, int32_t player){
    sPlayerData player_data;
    player_data_get (&player_data, player);
    int32_t token_ori= player_data.token;
    player_data.token += token;
    player_data.token= MAX (0, player_data.token);
    player_data.token= MIN (player_data.token, player_data.token_max);
    player_data_set (player, player_data);
    return abs(player_data.token-token_ori);
}

int32_t status_mulan_finish1_on(){
    mulan_finish1= 1;
    return 0;
}

int32_t status_mulan_use_finish1(){
    int32_t re= mulan_finish1;
    if (re) mulan_finish1= 0;
    return re;
}
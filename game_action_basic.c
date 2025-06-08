# include "main.h"
# include "game_data.h"
# include "game_action_basic.h"

int32_t action_attack (int32_t delta, int32_t area, int32_t player_use, int32_t player_des){
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    if (player_data_get (&player_data_use, player_use)<0) return -1;
    if (player_data_get (&player_data_des, player_des)<0) return -1;

    if (abs(player_data_use.pos - player_data_des.pos) > area){
        debug_print ("error: too long destination: use at %d, des at %d. attack area %d\n", player_data_use.pos, player_data_des.pos, area);
        return -1;
    }
    player_data_des.defense-= delta;
    if (player_data_des.defense<0){
        player_data_des.hp+= player_data_des.defense;
        player_data_des.defense= 0;
    }
    player_data_set (player_des, player_data_des);
}

int32_t action_defense (int32_t delta, int32_t player){
    sPlayerData player_data;
    if (player_data_get (&player_data, player)<0) return -1;
    player_data.defense+= delta;
    player_data.defense= MIN (player_data.defense, player_data.defense_max);

    player_data_set (player, player_data);
    return 0;
}

int32_t action_move (int32_t delta, int32_t direction, int32_t player){
    sPlayerData player_data[PLAYER_NUM];
    for (int32_t i=PLAYER1; i<=PLAYER2; i++){
        player_data_get (&(player_data[i]), i);
    }
    int32_t des= player_data[player].pos + direction*delta;

    while (map_data_cannot_move(0, des, player)){
        int32_t stay= player_data[player].pos - des;
        stay/= abs(stay);
        des+= stay;
    }

    player_data[player].pos= des;
    player_data_set (player, player_data[player]);
    return 0;
}

int32_t action_modefy_power (int32_t delta, int32_t player){
    sPlayerData player_data;
    if (player_data_get (&player_data, player)<0) return -1;
    player_data.power+= delta;
    if (player_data.power<0) return -1;
    player_data.power= MIN (player_data.power, player_data.power_max);

    player_data_set (player, player_data);
    return 0;
}

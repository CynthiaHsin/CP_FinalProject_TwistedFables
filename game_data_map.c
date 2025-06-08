# include "main.h"
# include "game_data.h"

# define POS_CALCULATE(mid, pos) (mid+pos)
# define MAP_POS(data, r, x) (data.map[r][POS_CALCULATE(data.block_mid, x)])

sMapData map_data;

int32_t map_data_init (int32_t mode){
    if (mode==GAMEMODE_1V1){
        map_data.block_mid= BLOCK_1V1;
        map_data.wall[WALL_LEFT]= -1;
        map_data.wall[WALL_RIGHT]= map_data.block_mid + BLOCK_1V1 + 1;
        map_data.wall[WALL_UP]= -1;
        map_data.wall[WALL_BOTTOM]= ROAD_1V1;
    }
    for (int32_t i=map_data.wall[WALL_UP]+1; i<map_data.wall[WALL_BOTTOM]; i++){
        for (int32_t j=map_data.wall[WALL_LEFT]+1; j<map_data.wall[WALL_RIGHT]; j++){
            map_data.map[i][j].player= PLAYER_UNDEFINED;
        }
    }
    int32_t player= PLAYER1;
    int32_t player_max= PLAYER2;
    for (int32_t i=player; i<=player_max; i++){
        sPlayerData player_data;
        player_data_get (&player_data, i);
        MAP_POS(map_data, 0, player_data.pos).player= i;
    }
    return 0;
}

int32_t map_data_cannot_move (int32_t road, int32_t pos, int32_t player){
    int32_t is_out= 0;
    debug_print ("check move: road %d, pos %d, player %d\n", road, POS_CALCULATE(map_data.block_mid, pos), player);
    if (POS_CALCULATE(map_data.block_mid, pos) <= map_data.wall[WALL_LEFT]) is_out= 1;
    if (POS_CALCULATE(map_data.block_mid, pos) >= map_data.wall[WALL_RIGHT]) is_out= 1;
    if (road <= map_data.wall[WALL_UP]) is_out= 1;
    if (road >= map_data.wall[WALL_BOTTOM]) is_out= 1;
    if (is_out){
        debug_print ("error: the block (%d, %d) is out of range\n", road, pos);
        return -1;
    }
    if (MAP_POS(map_data, road, pos).player==player) return 0;
    if (MAP_POS(map_data, road, pos).player!=PLAYER_UNDEFINED){
        debug_print ("error: the block (%d, %d) already have player (%d)\n", road, pos, MAP_POS(map_data, road, pos).player);
        return -1;
    }
    return 0;
}
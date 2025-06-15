# pragma once
# include "main.h"

# define ROAD_MAX 2
# define BLOCK_MAX 11

# define ROAD_1V1 1
# define BLOCK_1V1 4

typedef enum _eWall{
    WALL_LEFT,
    WALL_RIGHT,
    WALL_UP,
    WALL_BOTTOM,
    WALL_NUM
} eWall;

typedef struct _sBlockData{
    int32_t player;
} sBlockData;

typedef struct _sMapData{
    sBlockData map[ROAD_MAX][BLOCK_MAX];
    int32_t wall[WALL_NUM];
    int32_t block_mid;
} sMapData;

int32_t map_data_init (int32_t mode);
int32_t map_data_refresh ();

// -1: false, 0: true
int32_t map_data_cannot_move (int32_t road, int32_t pos, int32_t player);

int32_t map_data_is_at_edge (int32_t player);

const sMapData* map_data_get(void); 
int32_t map_data_get_player(int32_t road, int32_t pos);
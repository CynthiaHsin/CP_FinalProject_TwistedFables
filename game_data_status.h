# pragma once
# include "main.h"
# include "game_data.h"

typedef struct _sStatusData{
    int32_t mode;
    int32_t round;
    int32_t player_order[4];
} sStatusData;


// must be init first, before other datas
int32_t status_data_init (int32_t mode);
int32_t status_data_next_round();

int32_t status_data_cpy (sStatusData *pStatusData, sStatusData src);
int32_t status_data_get (sStatusData *pStatusData);
int32_t status_data_get_mode (int32_t *pMode);
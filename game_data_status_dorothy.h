# pragma once
# include "main.h"

typedef struct _sGameDataDorothyAction
{
    int32_t card_type;
    int32_t attack_value;
    int32_t level;
}sGameDataDorothyAction;

int32_t status_dorothy_init ();
int32_t status_dorothy_action_cpy (sGameDataDorothyAction *des, sGameDataDorothyAction src);
int32_t status_dorothy_do_action (sGameDataDorothyAction src);
int32_t status_dorothy_last_action (sGameDataDorothyAction *des);
int32_t status_dorothy_batter (int32_t level_delta, int32_t player);
int32_t status_dorothy_token_add (int32_t token, int32_t player);
# include "main.h"
# include "game_data_status_dorothy.h"
# include "game_data_player.h"
# include "game_data_card.h"

sGameDataDorothyAction dorothy_last_action;

int32_t status_dorothy_init (){
    dorothy_last_action.level= 0;
    dorothy_last_action.attack_value= 0;
    dorothy_last_action.card_type= CARD_UNDEFINED;
    return 0;
}

int32_t status_dorothy_action_cpy (sGameDataDorothyAction *des, sGameDataDorothyAction src){
    des->attack_value= src.attack_value;
    des->card_type= src.card_type;
    des->level= src.level;
    return 0;
}

int32_t status_dorothy_do_action (sGameDataDorothyAction src){
    return status_dorothy_action_cpy (&dorothy_last_action, src);
}

int32_t status_dorothy_last_action (sGameDataDorothyAction *des){
    return status_dorothy_action_cpy (des, dorothy_last_action);
}

int32_t status_dorothy_batter (int32_t level_delta, int32_t player){
    int32_t token= 1;
    if (player_data_card_is_on(-1, CARD_SKILL_ATTACK_EVOLUTION_L2, player)) token++;
    if (player_data_card_is_on(-1, CARD_SKILL_DEFENSE_EVOLUTION_L1, player) && level_delta>0) token++;
    if (player_data_card_is_on(-1, CARD_SKILL_DEFENSE_EVOLUTION_L2, player)) token++;
    if (player_data_card_is_on(-1, CARD_SKILL_MOVEMENT_EVOLUTION_L2, player)) token++;
    status_dorothy_token_add (token, player);
    return 0;
}

int32_t status_dorothy_token_add (int32_t token, int32_t player){
    sPlayerData player_data;
    player_data_get (&player_data, player);
    int32_t delta= player_data.token;
    player_data.token+= token;
    player_data.token= MIN (player_data.token, player_data.token_max);
    player_data.token= MAX (player_data.token, 0);
    delta= player_data.token - delta;
    return delta;
}
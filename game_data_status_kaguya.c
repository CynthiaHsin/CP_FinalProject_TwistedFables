# include "main.h"
# include "game_data_status_kaguya.h"
# include "game_data_player.h"
# include "game_data_card.h"
# include "game_action_basic.h"

int32_t used_defense_as_attack;
int32_t kaguya_evolution1_movement_used;
int32_t lasting_skill_area[CARD_NUM];
int32_t kaguya_finish1_on;
int32_t kaguya_finish3_des;

int32_t status_kaguya_init(){
    status_kaguya_round_start();
    return 0;
}

int32_t status_kaguya_round_start(){
    used_defense_as_attack= 0;
    kaguya_evolution1_movement_used= 0;
    for (int32_t i=0; i<CARD_NUM; i++) lasting_skill_area[i]= 0;
    kaguya_finish1_on= 0;
    kaguya_finish3_des= PLAYER_ORIGINAL;
    return 0;
}

int32_t status_kaguya_evolution1_on (int32_t player){
    sPlayerData player_data;
    player_data_get (&player_data, player);
    player_data.defense_max++;
    player_data_set (player, player_data);
    return 0;
}

int32_t status_kaguya_use_defense_card_as_attack (int32_t card_idx, int32_t player){
    sCardData card_data;
    card_data_get (&card_data, card_idx);
    if (card_data.type >= CARD_BASIC_ATTACK_L1 && card_data.type <= CARD_BASIC_ATTACK_L3) return card_data_get_level(card_data.type);
    sPlayerData player_data;
    player_data_get (&player_data, player);
    if (!player_data_card_is_on(CARD_ORIGINAL, CARD_SKILL_ATTACK_EVOLUTION_L1, player)) return 0;
    if (used_defense_as_attack) return 0;
    used_defense_as_attack= 1;
    return card_data_get_level(card_data.type);
}

int32_t status_kaguya_use_evolution1_movement (int32_t player){
    if (!player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_MOVEMENT_EVOLUTION_L1, player)) return 0;
    if (kaguya_evolution1_movement_used) return 0;
    else return 1;
}

int32_t status_kaguya_skill_area_set (int32_t card_idx, int32_t area){
    lasting_skill_area[card_idx]= area;
    return 0;
}

int32_t status_kaguya_skill_area_get (int32_t card_idx){
    return lasting_skill_area[card_idx];
}

int32_t status_kaguya_skill_finish1 (int32_t player){
    if (!player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_FINISH1, player)) return 0;
    kaguya_finish1_on= 1;
    return 0;
}

int32_t status_kaguya_skill_finish1_is_on (){
    return kaguya_finish1_on;
}

int32_t status_kaguya_skill_finish3 (int32_t player_use, int32_t player_des){
    if (!player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_FINISH3, player_use)) return 0;
    kaguya_finish3_des= player_des;
    return 0;
}

int32_t status_kaguya_skill_finish3_des_get (){
    return kaguya_finish3_des;
}
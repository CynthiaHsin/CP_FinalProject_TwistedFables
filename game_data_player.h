# pragma once
# include "main.h"

# define POWER_MAX 25
# define CARD_NUM 318

typedef struct _sPlayerData{
    int32_t player;     // enum ePlayer
    int32_t character;  // enum eCharacter
    int32_t token;
    int32_t token_max;
    int32_t hp;
    int32_t hp_finish;  // 必殺閾值
    int32_t hp_max;
    int32_t defense;
    int32_t defense_max;
    int32_t power;
    int32_t power_max;
    int32_t pos;
    int32_t card_on[CARD_NUM];
} sPlayerData;

int32_t player_data_write_back(int32_t player, sPlayerData src);

int32_t player_data_set_character (int32_t player, int32_t character);
int32_t player_data_set_card (int32_t player, int32_t card_idx);
int32_t player_data_set (int32_t player, sPlayerData src);
int32_t player_data_init (int32_t mode);

int32_t player_data_cpy (sPlayerData *pPlayerData, sPlayerData src);
int32_t player_data_print (int32_t player);
int32_t player_data_print_cardon (int32_t player);

int32_t player_data_get (sPlayerData *pPlayerData, int32_t player);
int32_t player_data_card_is_on (int32_t card_idx, int32_t card_type, int32_t player);
int32_t player_data_search_character (int32_t character);
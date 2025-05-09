# pragma once
# include "main.h"
# include "game_data.h"

// 54*3 + 18
# define CARD_BASIC_NUM_SUM 180
// 27
# define CARD_SKILL_NUM_SUM 27
# define CARD_POISON_NUM_SUM 18
# define CARD_MATCH_NUM_SUM 12
// BASIC + SKILL*4 +18 +12
# define CARD_NUM 318

# define CARD_BASIC_NUM 18
# define CARD_BASIC_NUM_1V1 12
// # define CARD_BASIC_NUM_2V2 18
# define CARD_SKILL_NUM_BASE_L1 1
# define CARD_SKILL_NUM_BASE_L2 2
# define CARD_SKILL_NUM_EVOLUTION_L1 1
# define CARD_SKILL_NUM_BASE_L3 3
# define CARD_SKILL_NUM_EVOLUTION_L2 1
# define CARD_SKILL_NUM_FINISH1 1
# define CARD_SKILL_NUM_FINISH2 1
# define CARD_SKILL_NUM_FINISH3 1
# define CARD_POISON_NUM 6
# define CARD_MATCH_NUM 12

typedef struct _sCardData{
    int32_t index;
    int32_t player; // 屬於誰的卡： bisic 預設 undefined，購買後屬於某玩家；skill預設屬於該玩家
    int32_t space;
    int32_t type;
} sCardData;

int32_t card_data_init (int32_t mode);
int32_t card_data_init_basic (int32_t idx);
int32_t card_data_init_skill (int32_t idx, int32_t player);

void card_data_set(int32_t idx, int32_t num, int32_t space, int32_t type, int32_t player);
void card_add (int32_t num, int32_t space, int32_t type, int32_t player);

void card_data_print (int32_t idx, int32_t num);

int32_t card_data_get (sCardData *pCard, int32_t idx);
int32_t card_data_get_type_name (char card_type_name[], int32_t idx);
int32_t card_data_get_space_name (char card_space_name[], int32_t idx);

int32_t card_cpy (sCardData *pCard, sCardData src);

# pragma once
# include "main.h"

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

# define CARD_COST_BASIC_L1 1
# define CARD_COST_BASIC_L2 3
# define CARD_COST_BASIC_L3 6
# define CARD_COST_COMMON 2
# define CARD_COST_SKILL_L1 0
# define CARD_COST_SKILL_L2 2
# define CARD_COST_SKILL_L3 4
# define CARD_COST_SKILL_EVOLUTION 0
# define CARD_COST_SKILL_FINISH 0

typedef struct _sCardData{
    int32_t index;
    int32_t player; // 屬於誰的卡： bisic 預設 undefined，購買後屬於某玩家；skill預設屬於該玩家
    int32_t space;
    int32_t type;
    int32_t cost; // 購買花費
} sCardData;

int32_t card_data_init (int32_t mode);
int32_t card_data_init_basic (int32_t idx);
int32_t card_data_init_skill (int32_t idx, int32_t player);

void card_data_set(int32_t idx, int32_t num, int32_t space, int32_t type, int32_t player);
void card_data_set_cost(int32_t idx, int32_t num, int32_t cost);
void card_add (int32_t num, int32_t space, int32_t type, int32_t player);

void card_data_print (int32_t idx, int32_t num);

int32_t card_cpy (sCardData *pCard, sCardData src);

int32_t card_data_get (sCardData *pCard, int32_t idx);
int32_t card_data_get_type_name (char card_type_name[], int32_t idx);
int32_t card_data_get_space_name (char card_space_name[], int32_t idx);
int32_t card_data_get_index (int32_t player, int32_t type);
int32_t card_data_get_level (int32_t type);

int32_t card_data_is_skill (int32_t idx);
int32_t card_data_is_evolution (int32_t idx);
int32_t card_data_is_evolution1 (int32_t idx);
int32_t card_data_is_evolution2 (int32_t idx);
int32_t card_attach_calculate (int32_t idx, int32_t action_type);
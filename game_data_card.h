# pragma once
# include "main.h"

// 54*3 + 18 + 27 + max(12, 18) = 225
# define CARD_NUM 225

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
typedef enum _eCardSpace{
    CARD_SPACE_HAND,
    CARD_SPACE_THROW,
    CARD_SPACE_USE,
    CARD_SPACE_SHOP,
    CARD_SPACE_DELETE
} eCardSpace;

typedef struct _sCardData{
    int32_t space;
    int32_t type;
} sCardData;

void card_data_set(int32_t idx, int32_t num, int32_t space, int32_t type);
void card_data_print (int32_t idx, int32_t num);
int32_t card_data_init();
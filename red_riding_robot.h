typedef struct _sRed_Riding_Robot{
    int32_t damage=0;
    int32_t shell=0;
    int32_t distance=0;
    int32_t power=0;
} sRed_Riding_Robot;
int32_t permute(int *card_idx, int32_t *card_use,int32_t start,int32_t end,int32_t player_use,int32_t player_des);
void swap(int *a, int *b);
int32_t red_riding_best_data_cpy (sRed_Riding_Robot *pStatusData, sRed_Riding_Robot src,int32_t *best_cards,int32_t *cards);
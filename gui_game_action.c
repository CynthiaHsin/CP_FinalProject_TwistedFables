# include "main.h"
# include "gui_sdl_config.h"
# include "gui_img_data.h"
# include "game_data.h"
# include "gui_game_render.h"

// return i meaning cards[i]
int32_t gui_action_choose_card (sCardData cards[], int32_t card_num){

    sCardData cards[CARD_NUM];  // 預設最多不會超過手牌上限
    int32_t num = 0;

    int gap = 20, w = 105, h = 160;
    int base_x = 50;
    int base_y = 50;

    for (int i = 0; i < num; ++i) {
        int32_t card_id = cards[i].index;
        SDL_Rect d = { base_x + i * (w + gap), base_y, w, h };
        SDL_Texture* tex = card_data_get_texture(cards[i].type, cards[i].player);
        if (tex != NULL) SDL_RenderCopy(ren, tex, NULL, &d);
    }
}
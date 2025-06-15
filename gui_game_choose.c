# include "main.h"
# include "game_data.h"
# include "gui_game_choose.h"
# include "gui_img_data.h"

extern SDL_Renderer *ren;
extern TTF_Font     *font_main;

void draw_hint(const char *utf8, int line)
{
    SDL_Color white = {255,255,255,255};
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font_main, utf8, white);
    if (!surf) return;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);
    int line_delta = 50;
    SDL_Rect dst = { 220, 100+line*line_delta, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}

int wait_event(SDL_Event *ev) 
{
    while (SDL_WaitEvent(ev)) {
        if (ev->type == SDL_QUIT)      return -2;
        if (ev->type == SDL_KEYDOWN &&
            ev->key.keysym.sym == SDLK_ESCAPE) return -1;
        return 0;
    }
    return -2;
}


// return card index
int32_t gui_choose_card (int32_t *pCard_type, sCardData cards[], int32_t card_num, char * text){
    if (card_num <= 0) return -1;

    const int gap = 20, w = 105, h = 160, base_x = 50, base_y = 500;
    SDL_Event ev;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
        SDL_RenderFillRect(ren, NULL);
        draw_hint(text, 0);

        for (int i = 0; i < card_num; ++i) {
            SDL_Rect d = { base_x + i*(w+gap), base_y, w, h };
            SDL_Texture **t;
            gui_imd_data_texture_get(&t, cards[i].type, PLAYER1);
            SDL_RenderCopy(ren, t[cards[i].type], NULL, &d);
        }
        SDL_RenderPresent(ren);

        if (wait_event(&ev) != 0) return -1;

        if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
            SDL_Point p = { ev.button.x, ev.button.y };
            for (int i = 0; i < card_num; ++i) {
                SDL_Rect d = { base_x + i*(w+gap), base_y, w, h };
                if (SDL_PointInRect(&p, &d)) {
                    if (pCard_type) *pCard_type = cards[i].type;
                    return cards[i].index;
                }
            }
        }
    }
}

// return -1(left), 1(right), 0(don't move), else(error)
int32_t gui_choose_move_direction (char * text){ // d/->: 1(right), a/<-: -1(left), enter: lock, ese: cancel
    int32_t dir = +1;          // 右
    SDL_Event ev;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
        SDL_RenderFillRect(ren, NULL);
        draw_hint(text, 0);

        draw_hint(dir>0?  "向右": "向左", 1);
        SDL_RenderPresent(ren);

        int s = wait_event(&ev);
        if (s) return 0;

        if (ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE: return 0;
                case SDLK_LEFT:
                case SDLK_a: dir = -1; break;
                case SDLK_RIGHT:
                case SDLK_d: dir = +1; break;
                case SDLK_RETURN: return dir;
                default: break;
            }
        }
    }
}

// return ePlayer
int32_t gui_choose_des_player (char * text){ // 0: choose me, 1: choose component, enter: lock
    int32_t cur = PLAYER2;
    SDL_Event ev;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
        SDL_RenderFillRect(ren, NULL);
        draw_hint(text, 0);

        const char *who = (cur == PLAYER1)? "你自己": "對手";
        draw_hint(who, 1);
        SDL_RenderPresent(ren);

        int s = wait_event(&ev);
        if (s) return -1;

        if (ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_a:
                case SDLK_d:
                    cur = (cur == PLAYER1)? PLAYER2: PLAYER1; break;
                case SDLK_RETURN: return cur;
            }
        }
    }
}

// return token num to use
int32_t gui_choose_token (int32_t token_use_max, int32_t player, char * text){
    sPlayerData pd;
    if (player_data_get(&pd, player) < 0)       return -1;

    // 這裡有問題
    // token 就是 token 不是能量
    // token_use_max 是輸入最多用多少

    // if (pd.power < token_use_max) {
    //     draw_hint("能量不足！", 0);
    //     SDL_Delay(1200);
    //     return -1;
    // }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
    SDL_RenderFillRect(ren, NULL);

    char buf[64];
    snprintf(buf, sizeof(buf), "%s\n使用token %d 點\n(Enter 確認 / Esc 取消)",
             text, token_use_max);
    draw_hint(buf, 0);
    SDL_RenderPresent(ren);

    SDL_Event ev;
    for (;;) {
        if (SDL_WaitEvent(&ev) == 0) continue;
        if (ev.type == SDL_QUIT)  return -1;
        if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_ESCAPE)  return -1;
            if (ev.key.keysym.sym == SDLK_RETURN)  return token_use_max;
        }
    }
}

// return -1(yes), 0(no), else(error)
int32_t gui_choose_move_yes_or_no (char * text){
    int32_t dir = 1;          // 右
    SDL_Event ev;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
        SDL_RenderFillRect(ren, NULL);
        draw_hint(text, 0);

        draw_hint(dir?  "YES": "NO", 1);
        SDL_RenderPresent(ren);

        int s = wait_event(&ev);
        if (s) return 0;

        if (ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE: return -1;
                case SDLK_LEFT:
                case SDLK_a: dir = !dir; break;
                case SDLK_RIGHT:
                case SDLK_d: dir = !dir; break;
                case SDLK_RETURN: return dir;
                default: break;
            }
        }
    }
}
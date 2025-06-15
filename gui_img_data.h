# pragma once

#include "gui_sdl_config.h"

#define IMG_SIZE_X 150
#define IMG_SIZE_Y 180
#define SCALE 1.2

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

// screen size
#define BOARD_W       1100
#define BOARD_H       600
#define BOARD_X       ((WINDOW_WIDTH  - BOARD_W)/2)
#define BOARD_Y       ((WINDOW_HEIGHT - BOARD_H)/2)

// track
#define TRACK_W       100
#define TRACK_H       150
#define TRACK_START_X (BOARD_X + (BOARD_W - 9*TRACK_W)/2)
#define TRACK_Y       (WINDOW_HEIGHT/2 - TRACK_H/2)

// card in pop up
#define CARD_W        105
#define CARD_H        160

// Play Area
#define PLAY_W        800
#define PLAY_H        140
#define PLAY_P1_X     ((WINDOW_WIDTH  - PLAY_W)/2)
#define PLAY_P2_X     PLAY_P1_X
#define PLAY_P1_Y     (TRACK_Y - 40 - PLAY_H) 
#define PLAY_P2_Y     (TRACK_Y + TRACK_H + 40) 

// button size
#define BTN_W 120
#define BTN_H 40

// plate & token
#define TOKEN_W          18      // 四種 token 都是 18×18px
#define TOKEN_H          18
#define PLATE_PADDING_X  40      // Plate 內左上角到第一格 token 的偏移
#define PLATE_PADDING_Y  40
#define PLATE_ROW_GAP    60      // 每一條(HP/DEF/POW)相隔多少像素
/* 三條 token 列在 Plate 上的 Y 座標 */
#define ROW_HP_Y(pdst)      ((pdst).y + PLATE_PADDING_Y)
#define ROW_DEF_Y(pdst)     (ROW_HP_Y(pdst)  + PLATE_ROW_GAP)
#define ROW_POW_Y(pdst)     (ROW_DEF_Y(pdst) + PLATE_ROW_GAP)


extern TTF_Font* font_main;

extern SDL_Renderer* ren; 
extern SDL_Texture* track;
extern SDL_Texture* plate;
extern SDL_Texture* sheet[];
extern SDL_Texture* token[];
extern SDL_Texture* card_back;
extern SDL_Texture* character[];
extern SDL_Texture* basic_card[];
extern SDL_Texture* rrh_card[];
extern SDL_Texture* sw_card[];
extern SDL_Texture* mulan_card[];
extern SDL_Texture* kaguya_card[];
extern SDL_Texture* mg_card[];
extern SDL_Texture* dorothy_card[];

enum BtnId { 
    BTN_CHARACTER, 
    BTN_TWIST, 
    BTN_DECK, 
    BTN_SUPPLY_BASIC,
    BTN_SUPPLY_SKILL, 
    BTN_CARD_USED,
    BTN_ROUND_END,
    BTN_ACTION_FOCUS,
    BTN_ACTION_SKILL,
    BTN_ACTION_BASIC,
    BTN_CARD_THROW,
    BTN_EVO_RRH,
    BTN_NUM 
};


# define X_LEFT   (20)
# define X_MID    (((WINDOW_WIDTH - BTN_W - 20)+20)/2)
# define X_MID_L  (((WINDOW_WIDTH - BTN_W - 20)+20)/2 - (BTN_W + 20))
# define X_MID_R  (((WINDOW_WIDTH - BTN_W - 20)+20)/2 + (BTN_W + 20))
# define X_RIGHT  (WINDOW_WIDTH - BTN_W - 20)
# define Y_UP_0   (60)
# define Y_UP_1   (110)
# define Y_MID    ((WINDOW_HEIGHT - BTN_H)/2)
# define Y_DOWN_0 (WINDOW_HEIGHT - 110 - BTN_H)
# define Y_DOWN_1 (WINDOW_HEIGHT - 160 - BTN_H)
# define Y_DOWN_2 (WINDOW_HEIGHT - 210 - BTN_H)
# define X_RRH    ((WINDOW_WIDTH - BTN_W - 20)- (BTN_W + 20))
# define NO_BUTTON (-1)

static inline SDL_Rect btn_rect(int idx, bool upper)
{
    SDL_Rect r = {0};
    r.w = BTN_W; r.h = BTN_H;
    r.x = r.y = NO_BUTTON;
    switch (idx){
        default: break;
    }
    if (upper) {
        // player2
        switch (idx) {
            case BTN_CHARACTER:        r.x = X_RIGHT;   r.y = Y_UP_0; break;
            case BTN_TWIST:            r.x = X_MID;     r.y = Y_UP_0; break;
            case BTN_SUPPLY_SKILL:     r.x = X_RIGHT;   r.y = Y_UP_1; break;
            case BTN_DECK:             r.x = X_LEFT;    r.y = Y_UP_0; break;
            case BTN_CARD_USED:        r.x = X_MID;     r.y = Y_UP_1; break;
            case BTN_CARD_THROW:       r.x = X_LEFT;    r.y = Y_UP_1; break;
        }
    } else {
        // player1
        switch (idx) {
            case BTN_CHARACTER:        r.x = X_RIGHT;   r.y = Y_DOWN_0; break;
            case BTN_TWIST:            r.x = X_MID;     r.y = Y_DOWN_0; break;
            case BTN_SUPPLY_SKILL:     r.x = X_LEFT;    r.y = Y_DOWN_0; break;
            case BTN_DECK:             r.x = X_RIGHT;   r.y = Y_DOWN_1; break;
            case BTN_CARD_USED:        r.x = X_MID;     r.y = Y_DOWN_1; break;
            case BTN_SUPPLY_BASIC:     r.x = X_LEFT;    r.y = Y_MID;    break;
            case BTN_ROUND_END:        r.x = X_RIGHT;   r.y = Y_MID;    break;
            case BTN_ACTION_FOCUS:     r.x = X_MID;     r.y = Y_DOWN_2; break;
            case BTN_ACTION_SKILL:     r.x = X_MID_R;   r.y = Y_DOWN_2; break;
            case BTN_ACTION_BASIC:     r.x = X_MID_L;   r.y = Y_DOWN_2; break;
            case BTN_CARD_THROW:       r.x = X_RIGHT;   r.y = Y_DOWN_2; break;
            case BTN_EVO_RRH:          r.x = X_RRH;     r.y = Y_DOWN_1; break;
        }
    }
    return r;
}

int gui_imd_data_texture_get (SDL_Texture*** pTex, int card_type, int32_t player);
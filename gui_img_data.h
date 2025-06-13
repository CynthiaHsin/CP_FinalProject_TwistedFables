# pragma once

#include "gui_sdl_config.h"

#define IMG_SIZE 150
#define SCALE 1.2

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

// screen size
#define BOARD_W       1100
#define BOARD_H       600
#define BOARD_X       ((WINDOW_WIDTH  - BOARD_W)/2)
#define BOARD_Y       ((WINDOW_HEIGHT - BOARD_H)/2)

// track
#define TRACK_W       80
#define TRACK_H       120
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
    BTN_NUM 
};

static inline SDL_Rect btn_rect(int idx, bool upper)
{
    SDL_Rect r = {0};
    r.w = BTN_W; r.h = BTN_H;

    if (upper) {
        // player2
        switch (idx) {
            case BTN_CHARACTER:        r.x = WINDOW_WIDTH - BTN_W - 20;          r.y = 60; break;
            case BTN_TWIST:            r.x = ((WINDOW_WIDTH - BTN_W - 20)+20)/2; r.y = 60; break;
            case BTN_SUPPLY_SKILL:     r.x = WINDOW_WIDTH - BTN_W - 20;          r.y = 110; break;
            case BTN_DECK:             r.x = 20;                                 r.y = 60; break;
        }
    } else {
        // player1
        switch (idx) {
            case BTN_CHARACTER:        r.x = WINDOW_WIDTH - BTN_W - 20;          r.y = WINDOW_HEIGHT - 110 - BTN_H; break;
            case BTN_TWIST:            r.x = ((WINDOW_WIDTH - BTN_W - 20)+20)/2; r.y = WINDOW_HEIGHT - 110 - BTN_H; break;
            case BTN_SUPPLY_SKILL:     r.x = 20;                                 r.y = WINDOW_HEIGHT - 110 - BTN_H; break;
            case BTN_SUPPLY_BASIC:     r.x = 20;                                 r.y = (WINDOW_HEIGHT - BTN_H)/2; break;
            case BTN_DECK:             r.x = WINDOW_WIDTH - BTN_W - 20;          r.y = WINDOW_HEIGHT - 160 - BTN_H; break;
        }
    }
    return r;
}

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

// Play Area
#define PLAY_W        800
#define PLAY_H        140
#define PLAY_P1_X     ((WINDOW_WIDTH  - PLAY_W)/2)
#define PLAY_P2_X     PLAY_P1_X
#define PLAY_P1_Y     (TRACK_Y - 40 - PLAY_H) // 上方
#define PLAY_P2_Y     (TRACK_Y + TRACK_H + 40) // 下方

// button size
#define BTN_W 120
#define BTN_H 40

enum BtnId { BTN_CHARACTER, BTN_TWIST, BTN_DECK, BTN_SUPPLY_BASIC,
             BTN_SUPPLY_SKILL, BTN_NUM };

static inline SDL_Rect btn_rect(int idx, bool upper)
{
    SDL_Rect r = {0};
    r.w = BTN_W; r.h = BTN_H;
    switch (idx) {
        case BTN_CHARACTER:
            r.x = upper ? WINDOW_WIDTH - BTN_W - 20 : 20;
            r.y = upper ? 60  : WINDOW_HEIGHT - BTN_H - 60;
            break;
        case BTN_TWIST:
            r.x = (WINDOW_WIDTH - BTN_W)/2;
            r.y = upper ? 20 : WINDOW_HEIGHT - BTN_H - 20;
            break;
        case BTN_DECK:
            r.x = upper ? WINDOW_WIDTH - BTN_W - 20 : 20;
            r.y = upper ? 120 : WINDOW_HEIGHT - BTN_H - 120;
            break;
        case BTN_SUPPLY_BASIC:
            r.x = 20;
            r.y = upper ? 120 : WINDOW_HEIGHT - BTN_H - 120;
            break;
        case BTN_SUPPLY_SKILL:
            r.x = 20;
            r.y = upper ? 60 : WINDOW_HEIGHT - BTN_H - 60;
            break;
    }
    return r;
}

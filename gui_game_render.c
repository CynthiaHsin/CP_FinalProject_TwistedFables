#include "gui_sdl_config.h"
#include "gui_img_data.h"

extern SDL_Renderer* ren;   // 已在 gui_game.c 建立
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

void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void popup(enum BtnId id, bool upper, int32_t characters[]);

void game_scene_loop(int32_t characters[])
{
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point p = { e.button.x, e.button.y };
                if (handle_button_click(p, characters))
                    continue;;
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        draw_board(characters);

        draw_buttons();

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
}

void draw_board(int32_t characters[])
{
    SDL_Rect play1 = {PLAY_P1_X, PLAY_P1_Y, PLAY_W, PLAY_H};
    SDL_Rect play2 = {PLAY_P2_X, PLAY_P2_Y, PLAY_W, PLAY_H};
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderDrawRect(ren, &play1);
    SDL_RenderDrawRect(ren, &play2);

    for (int i = 0; i < 9; ++i) {
        SDL_Rect dst = {
            TRACK_START_X + i*TRACK_W,
            TRACK_Y,
            TRACK_W, TRACK_H
        };
        SDL_RenderCopy(ren, track, NULL, &dst);
        SDL_RenderDrawRect(ren, &dst);
    }

    SDL_Rect token_rect = {0, 0, 48, 48};
    token_rect.x = TRACK_START_X + 3*TRACK_W + (TRACK_W-token_rect.w)/2;
    token_rect.y = TRACK_Y + (TRACK_H-token_rect.h)/2;
    SDL_RenderCopy(ren, character[characters[PLAYER1]], NULL, &token_rect); // player1

    token_rect.x = TRACK_START_X + 5*TRACK_W + (TRACK_W-token_rect.w)/2;
    SDL_RenderCopy(ren, character[characters[PLAYER2]], NULL, &token_rect); // player2
}

void draw_buttons(void)
{
    SDL_SetRenderDrawColor(ren, 160, 160, 160, 255);
    for (int i = 0; i < BTN_NUM; ++i) {
        SDL_Rect u = btn_rect(i, /*upper*/true);
        SDL_Rect d = btn_rect(i, /*upper*/false);
        SDL_RenderFillRect(ren, &u);
        SDL_RenderFillRect(ren, &d);
        // 文字 (示意用，之後換 TTF)
    }
}

bool handle_button_click(SDL_Point p, int32_t characters[])
{
    for (int i = 0; i < BTN_NUM; ++i) {
        SDL_Rect rUp = btn_rect(i, true);
        SDL_Rect rDown = btn_rect(i, false);
        bool hitUp   = SDL_PointInRect(&p, &rUp);
        bool hitDown = SDL_PointInRect(&p, &rDown);

        if (hitUp || hitDown) {
            popup((enum BtnId)i, hitUp, characters);
            return true;
        }
    }
    return false;
}

void popup(enum BtnId id, bool upper, int32_t characters[])
{
    bool open = true;
    SDL_Event e;

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    while (open) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                open = false;
        }
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
        SDL_RenderFillRect(ren, NULL);

        SDL_Rect win = { 200, 80, WINDOW_WIDTH-400, WINDOW_HEIGHT-160 };
        SDL_SetRenderDrawColor(ren, 30, 30, 30, 240);
        SDL_RenderFillRect(ren, &win);

        switch (id) {
            case BTN_CHARACTER: {
                int player = upper ? PLAYER2 : PLAYER1;
                SDL_Rect dst = { win.x+20, win.y+20, 540, 380 }; // Plate
                SDL_RenderCopy(ren, plate, NULL, &dst);

                // sheet
                SDL_Rect dstSheet = dst;
                dstSheet.x += 60; dstSheet.y += 60;
                dstSheet.w = 420; dstSheet.h = 260;
                SDL_RenderCopy(ren, sheet[characters[player]], NULL, &dstSheet);

                // TODO: hp/def/power/epic token 擺正確洞洞 (依角色初始值)
                break;
            }
            case BTN_TWIST: {
                int player = upper ? PLAYER2 : PLAYER1;
                int handCnt = 5;          
                int gap = 20, w = 105, h = 160;
                for (int i = 0; i < handCnt; ++i) {
                    SDL_Rect d = { win.x+50 + i*(w+gap), win.y+80, w, h };
                    if (player == PLAYER1) {
                        SDL_RenderCopy(ren, basic_card[CARD_BASIC_ATTACK_L1], NULL, &d);
                    } else {
                        SDL_RenderCopy(ren, card_back, NULL, &d);
                    }
                }
                break;
            }
            case BTN_DECK: {
                int player = upper ? PLAYER2 : PLAYER1;
                SDL_Rect back = { win.x+80, win.y+100, 105,160 };
                SDL_RenderCopy(ren, card_back, NULL, &back);
                SDL_Rect discard = { back.x+150, back.y, 105,160 };
                SDL_RenderCopy(ren, basic_card[CARD_BASIC_ATTACK_L1], NULL, &discard); // top of discard
                break;
            }
            case BTN_SUPPLY_BASIC: {
                int gap = 15, w = 105, h = 160;
                for (int row=0; row<4; ++row)
                    for (int col=0; col<3; ++col) {
                        int type = CARD_BASIC_ATTACK_L1 + row; 
                        SDL_Rect d = {
                            win.x+40 + col*(w+gap),
                            win.y+40 + row*(h+gap),
                            w, h
                        };
                        SDL_RenderCopy(ren, basic_card[type], NULL, &d);
                    }
                break;
            }
            case BTN_SUPPLY_SKILL: {
                int player = upper ? PLAYER2 : PLAYER1;
                SDL_Texture** pool = (player==PLAYER1)? rrh_card : sw_card; 
                int gap = 15, w = 105, h = 160, idx = 0;
                for (int row=0; row<3; ++row)
                    for (int col=0; col<3; ++col) {
                        int type = CARD_SKILL_ATTACK_BASE_L1 + idx++;
                        SDL_Rect d = { win.x+40 + col*(w+gap),
                                       win.y+40 + row*(h+gap),
                                       w, h };
                        SDL_RenderCopy(ren, pool[type], NULL, &d);
                    }
                break;
            }
            default: break;
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
}

#include "gui_sdl_config.h"
#include "gui_img_data.h"
#include "game_data_card.h"
#include "game_data.h"

// extern SDL_Renderer* ren; 
// extern SDL_Texture* track;
// extern SDL_Texture* plate;
// extern SDL_Texture* sheet[];
// extern SDL_Texture* token[];
// extern SDL_Texture* card_back;
// extern SDL_Texture* character[];
// extern SDL_Texture* basic_card[];
// extern SDL_Texture* rrh_card[];
// extern SDL_Texture* sw_card[];
// extern SDL_Texture* mulan_card[];
// extern SDL_Texture* kaguya_card[];
// extern SDL_Texture* mg_card[];
// extern SDL_Texture* dorothy_card[];

void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void draw_button_text(SDL_Rect rect, const char* text);
void popup(enum BtnId id, bool upper, int32_t characters[]);
void render_player_skills_only(SDL_Renderer* ren, int32_t player, int32_t characters[]);

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
    const char* labels[BTN_NUM] = {
        "CHARACTER", "TWISTED CARD", "DECK/DESCARD", "BASIC", "SKILL/EPIC"
    };
    SDL_SetRenderDrawColor(ren, 160, 160, 160, 255);
    for (int i = 0; i < BTN_NUM; ++i) {
        SDL_Rect u = btn_rect(i, /*upper*/true);
        SDL_Rect d = btn_rect(i, /*upper*/false);
        if(i != BTN_SUPPLY_BASIC){
            SDL_RenderFillRect(ren, &u);
            draw_button_text(u, labels[i]);
        }
        SDL_RenderFillRect(ren, &d);
        draw_button_text(d, labels[i]);
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

void draw_button_text(SDL_Rect rect, const char* text) {
    SDL_Color black = {0, 0, 0, 255};

    SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font_main, text, black);
    if (!text_surface) {
        printf("TTF_RenderUTF8 failed: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
    SDL_FreeSurface(text_surface);

    if (!text_texture) return;

    SDL_Rect dst = {
        rect.x + (rect.w - text_surface->w) / 2,
        rect.y + (rect.h - text_surface->h) / 2,
        text_surface->w, text_surface->h
    };

    SDL_RenderCopy(ren, text_texture, NULL, &dst);
    SDL_DestroyTexture(text_texture);
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
                // int player = upper ? PLAYER2 : PLAYER1;
                SDL_Rect back = { win.x+80, win.y+100, 105,160 };
                SDL_RenderCopy(ren, card_back, NULL, &back);
                SDL_Rect discard = { back.x+150, back.y, 105,160 };
                // SDL_RenderCopy(ren, basic_card[CARD_BASIC_ATTACK_L1], NULL, &discard); // top of discard
                SDL_SetRenderDrawColor(ren, 0, 200, 255, 255);  // 藍色框
                SDL_RenderDrawRect(ren, &discard);
                break;
            }
            case BTN_SUPPLY_BASIC: {
                int start_x = 100;
                int start_y = 200;
                int offset_x = 120;
                int offset_y = 160;

                eCardType attack_lv[] = { CARD_BASIC_ATTACK_L1, CARD_BASIC_ATTACK_L2, CARD_BASIC_ATTACK_L3 };
                eCardType defense_lv[] = { CARD_BASIC_DEFENSE_L1, CARD_BASIC_DEFENSE_L2, CARD_BASIC_DEFENSE_L3 };
                eCardType movement_lv[] = { CARD_BASIC_MOVEMENT_L1, CARD_BASIC_MOVEMENT_L2, CARD_BASIC_MOVEMENT_L3 };

                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < 3; col++) {
                        eCardType type;
                        if (row == 0) type = attack_lv[col];
                        else if (row == 1) type = defense_lv[col];
                        else type = movement_lv[col];

                        sCardData card_list[32];
                        int32_t count = 0;
                        game_data_search_cards(card_list, &count, PLAYER_ORIGINAL, CARD_SPACE_SHOP, type, -1);

                        if (count > 0) {
                            SDL_Rect dst = { start_x + col * offset_x, start_y + row * offset_y, CARD_W, CARD_H };
                            SDL_RenderCopy(ren, basic_card[card_list[0].index], NULL, &dst);
                        }
                    }
                }

                // 顯示通用卡（Common）
                {
                    sCardData card_list[32];
                    int32_t count = 0;
                    game_data_search_cards(card_list, &count, PLAYER_ORIGINAL, CARD_SPACE_SHOP, CARD_BASIC_COMMON, -1);

                    if (count > 0) {
                        SDL_Rect dst = { start_x, start_y + 3 * offset_y, CARD_W, CARD_H };
                        SDL_RenderCopy(ren, basic_card[card_list[0].index], NULL, &dst);
                    }
                }

                break;
            }
            case BTN_SUPPLY_SKILL: {
                int32_t player = upper ? PLAYER2 : PLAYER1;
                render_player_skills_only(ren, player, characters);
                break;
                // int player = upper ? PLAYER2 : PLAYER1;
                // SDL_Texture** pool = (player==PLAYER1)? rrh_card : sw_card; 
                // int gap = 15, w = 105, h = 160, idx = 0;
                // for (int row=0; row<3; ++row)
                //     for (int col=0; col<3; ++col) {
                //         int type = CARD_SKILL_ATTACK_BASE_L1 + idx++;
                //         SDL_Rect d = { win.x+40 + col*(w+gap),
                //                        win.y+40 + row*(h+gap),
                //                        w, h };
                //         SDL_RenderCopy(ren, pool[type], NULL, &d);
                //     }
                // break;
            }
            default: break;
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
}

void render_player_skills_only(SDL_Renderer* ren, int32_t player, int32_t characters[]) {
    SDL_Texture** skill_cards = NULL;
    switch (characters[player]) {
        case CHARACTER_RED_RIDING_HOOD:     skill_cards = rrh_card; break;
        case CHARACTER_SNOW_WHITE:          skill_cards = sw_card; break;
        case CHARACTER_DOROTHY:             skill_cards = dorothy_card; break;
        case CHARACTER_KAGUYA:              skill_cards = kaguya_card; break;
        case CHARACTER_MATCH_GIRL:          skill_cards = mg_card; break;
        case CHARACTER_MULAN:               skill_cards = mulan_card; break;
        default: return;
    }

    const int attack_cards[5] = {
        CARD_SKILL_ATTACK_BASE_L1, CARD_SKILL_ATTACK_BASE_L2,
        CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_SKILL_ATTACK_BASE_L3,
        CARD_SKILL_ATTACK_EVOLUTION_L2
    };
    const int defense_cards[5] = {
        CARD_SKILL_DEFENSE_BASE_L1, CARD_SKILL_DEFENSE_BASE_L2,
        CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_SKILL_DEFENSE_BASE_L3,
        CARD_SKILL_DEFENSE_EVOLUTION_L2
    };
    const int movement_cards[5] = {
        CARD_SKILL_MOVEMENT_BASE_L1, CARD_SKILL_MOVEMENT_BASE_L2,
        CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_SKILL_MOVEMENT_BASE_L3,
        CARD_SKILL_MOVEMENT_EVOLUTION_L2
    };
    const int finish_cards[3] = {
        CARD_SKILL_FINISH1, CARD_SKILL_FINISH2, CARD_SKILL_FINISH3
    };

    int x0 = 100, y0 = 200, dx = 110, dy = 150;

    for (int i = 0; i < 5; ++i) {
        SDL_Rect ra = { x0 + i * dx, y0 + 0 * dy, CARD_W, CARD_H };
        SDL_Rect rd = { x0 + i * dx, y0 + 1 * dy, CARD_W, CARD_H };
        SDL_Rect rm = { x0 + i * dx, y0 + 2 * dy, CARD_W, CARD_H };
        SDL_RenderCopy(ren, skill_cards[attack_cards[i]], NULL, &ra);
        SDL_RenderCopy(ren, skill_cards[defense_cards[i]], NULL, &rd);
        SDL_RenderCopy(ren, skill_cards[movement_cards[i]], NULL, &rm);
    }

    for (int i = 0; i < 3; ++i) {
        SDL_Rect rf = { x0 + i * dx, y0 + 3 * dy, CARD_W, CARD_H };
        SDL_RenderCopy(ren, skill_cards[finish_cards[i]], NULL, &rf);
    }
}


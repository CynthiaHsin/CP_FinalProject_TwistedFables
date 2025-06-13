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
void draw_token_row(SDL_Texture* tex, SDL_Rect rowStart, int tokenCnt, int tokenFilled);
void draw_stack(SDL_Renderer* ren, SDL_Texture** pool, const int types[], int n, int x, int y);

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

                // // sheet
                // SDL_Rect dstSheet = dst;
                // dstSheet.x += 60; dstSheet.y += 60;
                // dstSheet.w = 420; dstSheet.h = 260;
                // SDL_RenderCopy(ren, sheet[characters[player]], NULL, &dstSheet);

                // 角色花紋／卡面
                SDL_Rect dstSheet = { dst.x+60, dst.y+60, 420, 260 };
                SDL_RenderCopy(ren, sheet[ characters[player] ], NULL, &dstSheet);

                // 讀取玩家目前數值
                sPlayerData pd;
                player_data_get(&pd, player);   // 失敗回 -1，這裡簡化不檢查

                // 畫四條 token 列
                SDL_Rect start = { dst.x + PLATE_PADDING_X, ROW_HP_Y(dst),
                                TOKEN_W, TOKEN_H };

                // 1) HP：顯示「剩餘」生命；已損失的不畫
                draw_token_row(token[2], start, pd.hp_max, pd.hp);

                // 2) DEF：護甲 
                start.y = ROW_DEF_Y(dst);
                draw_token_row(token[0], start, pd.defense_max, pd.defense);

                // 3) POW：能量（上限固定 25）
                start.y = ROW_POW_Y(dst);
                draw_token_row(token[3], start, POWER_MAX, pd.power);

                // 4) Epic：當 hp ≤ hp_finish 時亮出 1 顆
                if (pd.hp <= pd.hp_finish) {
                    SDL_Rect epic = { dst.x + dst.w - PLATE_PADDING_X - TOKEN_W,
                                    dst.y + dst.h - PLATE_PADDING_Y - TOKEN_H,
                                    TOKEN_W, TOKEN_H };
                    SDL_RenderCopy(ren, token[1], NULL, &epic);
                }
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
                int start_x = 400;
                int start_y = 100;
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
                            SDL_RenderCopy(ren, basic_card[card_list[0].type], NULL, &dst);
                        }
                    }
                }

                // 顯示通用卡（Common）
                {
                    sCardData card_list[32];
                    int32_t count = 0;
                    game_data_search_cards(card_list, &count, PLAYER_ORIGINAL, CARD_SPACE_SHOP, CARD_BASIC_COMMON, -1);

                    if (count > 0) {
                        SDL_Rect dst = { start_x + 3 * offset_x, start_y, CARD_W, CARD_H };
                        SDL_RenderCopy(ren, basic_card[card_list[0].type], NULL, &dst);
                    }
                }

                break;
            }
            case BTN_SUPPLY_SKILL: {
                int32_t player = upper ? PLAYER2 : PLAYER1;

                SDL_Texture** tex = NULL;
                switch (characters[player]) {
                    case CHARACTER_RED_RIDING_HOOD: tex = rrh_card; break;
                    case CHARACTER_SNOW_WHITE:      tex = sw_card; break;
                    case CHARACTER_DOROTHY:         tex = dorothy_card; break;
                    case CHARACTER_KAGUYA:          tex = kaguya_card; break;
                    case CHARACTER_MATCH_GIRL:      tex = mg_card; break;
                    case CHARACTER_MULAN:           tex = mulan_card; break;
                    default: return;
                }

                const int attack[] = {
                    CARD_SKILL_ATTACK_EVOLUTION_L2,
                    CARD_SKILL_ATTACK_BASE_L3,
                    CARD_SKILL_ATTACK_EVOLUTION_L1,
                    CARD_SKILL_ATTACK_BASE_L2,
                    CARD_SKILL_ATTACK_BASE_L1
                };
                const int defense[] = {
                    CARD_SKILL_DEFENSE_EVOLUTION_L2,
                    CARD_SKILL_DEFENSE_BASE_L3,
                    CARD_SKILL_DEFENSE_EVOLUTION_L1,
                    CARD_SKILL_DEFENSE_BASE_L2,
                    CARD_SKILL_DEFENSE_BASE_L1
                };
                const int movement[] = {
                    CARD_SKILL_MOVEMENT_EVOLUTION_L2,
                    CARD_SKILL_MOVEMENT_BASE_L3,
                    CARD_SKILL_MOVEMENT_EVOLUTION_L1,
                    CARD_SKILL_MOVEMENT_BASE_L2,
                    CARD_SKILL_MOVEMENT_BASE_L1
                };
                const int finish[] = {
                    CARD_SKILL_FINISH1,
                    CARD_SKILL_FINISH2,
                    CARD_SKILL_FINISH3
                };

                int x0 = 330, y0 = 120, dx = CARD_W + 40, dy = CARD_H + 60;

                // 顯示三疊技能牌（攻、防、移）
                const int* stacks[] = {attack, defense, movement};
                for (int col = 0; col < 3; col++) {
                    for (int i = 0; i < 5; i++) {
                        sCardData list[4];
                        int32_t count = 0;
                        game_data_search_cards(list, &count,
                            PLAYER_ORIGINAL, CARD_SPACE_SHOP, stacks[col][i], -1);
                        if (count > 0) {
                            SDL_Rect dst = {
                                x0 + col * dx + i * 2,   // 疊起來稍微偏移
                                y0 + i * 2,
                                CARD_W, CARD_H
                            };
                            SDL_RenderCopy(ren, tex[stacks[col][i]], NULL, &dst);
                        }
                    }
                }

                // 顯示三張必殺牌
                for (int i = 0; i < 3; i++) {
                    sCardData list[2];
                    int32_t count = 0;
                    game_data_search_cards(list, &count,
                        PLAYER_ORIGINAL, CARD_SPACE_SHOP, finish[i], -1);
                    if (count > 0) {
                        SDL_Rect dst = {
                            x0 + i * dx,
                            y0 + dy,
                            CARD_W, CARD_H
                        };
                        SDL_RenderCopy(ren, tex[finish[i]], NULL, &dst);
                    }
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

    // int x0 = 100, y0 = 200, dx = 110, dy = 150;
    const int dx = 140;          // 三疊彼此水平間距
    const int dy = 190;          // Epic 與 Skill 疊之間縱向間距
    const int x0 = 400;          // 左上角
    const int y0 = 180;

    // for (int i = 0; i < 5; ++i) {
    //     SDL_Rect ra = { x0 + i * dx, y0 + 0 * dy, CARD_W, CARD_H };
    //     SDL_Rect rd = { x0 + i * dx, y0 + 1 * dy, CARD_W, CARD_H };
    //     SDL_Rect rm = { x0 + i * dx, y0 + 2 * dy, CARD_W, CARD_H };
    //     SDL_RenderCopy(ren, skill_cards[attack_cards[i]], NULL, &ra);
    //     SDL_RenderCopy(ren, skill_cards[defense_cards[i]], NULL, &rd);
    //     SDL_RenderCopy(ren, skill_cards[movement_cards[i]], NULL, &rm);
    // }
    // draw_stack(ren, skill_cards, attack_cards, 5, x0 + 0*dx, y0);
    // draw_stack(ren, skill_cards, defense_cards, 5, x0 + 1*dx, y0);
    // draw_stack(ren, skill_cards, movement_cards, 5, x0 + 2*dx, y0);

    for (int i = 0; i < 3; ++i) {
        // SDL_Rect rf = { x0 + i * dx, y0 + 3 * dy, CARD_W, CARD_H };
        SDL_Rect rf = { x0 + i*dx, y0 + dy, CARD_W, CARD_H };
        SDL_RenderCopy(ren, skill_cards[finish_cards[i]], NULL, &rf);
    }
}

// 把一種類型的 token 連續畫在一條水平列上
void draw_token_row(SDL_Texture* tex, SDL_Rect rowStart,
                           int tokenCnt, int tokenFilled)
{
    for (int i = 0; i < tokenCnt; ++i) {
        SDL_Rect r = rowStart;
        r.x += i * TOKEN_W;
        if (i < tokenFilled)      // 已獲得/已損失 才顯示
            SDL_RenderCopy(ren, tex, NULL, &r);
    }
}

void draw_stack(SDL_Renderer* ren, SDL_Texture** pool, const int types[], int n, int x, int y)
{
    const int offset = 3;      // 疊牌位移
    SDL_Rect dst = { x, y, CARD_W, CARD_H };

    /* 由上往下找商店裡還剩哪張就畫哪張 */
    for (int i = 0; i < n; ++i) {
        sCardData list[4];
        int32_t cnt = 0;

        if (types[i] < 0 || types[i] >= CARD_TYPE_NUM || pool[types[i]] == NULL) {
            printf("Skipping invalid or missing texture at types[%d] = %d\n", i, types[i]);
            continue;
        }

        game_data_search_cards(list, &cnt, PLAYER_ORIGINAL, CARD_SPACE_SHOP, types[i], -1);
        if (cnt > 0) {
            SDL_SetTextureAlphaMod(pool[types[i]], 255 - i*10);
            SDL_RenderCopy(ren, pool[types[i]], NULL, &dst);
            dst.x += offset;   // 下一張稍微往右下
            dst.y += offset;
        }
    }
}
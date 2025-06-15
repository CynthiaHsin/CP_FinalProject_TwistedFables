#include "gui_sdl_config.h"
#include "gui_img_data.h"
#include "gui_game_action.h"
#include "game_data.h"
#include "game_action.h"

void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void draw_button_text(SDL_Rect rect, const char* text);
void popup(enum BtnId id, bool upper, int32_t characters[]);
void render_hand(SDL_Renderer* ren, int32_t player, SDL_Texture* card_back, int32_t characters[]);
SDL_Texture* card_data_get_texture(int32_t card_id, int32_t player);

void draw_stat_text(int x, int y, const char *utf8);
int32_t detect_basic_stack(SDL_Point p);
int32_t detect_skill_stack(SDL_Point p, int32_t player);
bool detect_hand_card_click(SDL_Point p, int32_t player, int* outType);

bool gui_round_running;
static bool   g_handZoomOpen = false; 
static SDL_Texture* g_handZoomTex = NULL;

void game_scene_loop(int32_t characters[])
{
    gui_round_running = true;
    SDL_Event e;

    while (gui_round_running) {
        while (SDL_PollEvent(&e)) {
            if (g_handZoomOpen &&
                e.type == SDL_KEYDOWN &&
                e.key.keysym.sym == SDLK_ESCAPE) {

                g_handZoomOpen = false;
                continue; 
            }

            if (e.type == SDL_QUIT){
                gui_round_running = false;
                status_data_end_game();
                return;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point p = { e.button.x, e.button.y };
                if (handle_button_click(p, characters)) {continue;;}
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

    // 1. 依據 map_data 畫出所有 block
    const sMapData* md = map_data_get();
    int blocks = md->block_mid * 2 + 1;          // 1v1 = 9 
    for (int pos = -md->block_mid; pos <= md->block_mid; ++pos) {
        int idx   = pos + md->block_mid;         // 0-based column
        SDL_Rect dst = {
            TRACK_START_X + idx * TRACK_W,
            TRACK_Y,
            TRACK_W, TRACK_H
        };
        SDL_RenderCopy(ren, track, NULL, &dst);  // 賽道底圖 
        SDL_RenderDrawRect(ren, &dst);           // 外框 
    }

    // 2. 依據 map_data 決定哪些格子有玩家
    for (int pos = -md->block_mid; pos <= md->block_mid; ++pos) {
        int player = map_data_get_player(/*road=*/0, pos);   // 1v1 只有 road 0 
        if (player == PLAYER_UNDEFINED) continue;

        int idx = pos + md->block_mid;
        SDL_Rect token = {
            TRACK_START_X + idx * TRACK_W + (TRACK_W-63)/2,
            TRACK_Y        + (TRACK_H-96)/2,
            63, 96
        };
        SDL_RenderCopy(ren, character[characters[player]], NULL, &token);
    }
}

void draw_buttons(void)
{
    const char* labels[BTN_NUM] = {
        "CHARACTER", "TWISTED CARD", "DECK/DESCARD", "BASIC", "SKILL/EPIC", "CARD USED", "END ROUND",
        "FOCUS", "USE SKILL", "USE BASIC"
    };
    SDL_SetRenderDrawColor(ren, 160, 160, 160, 255);
    for (int i = 0; i < BTN_NUM; ++i) {
        SDL_Rect u = btn_rect(i, /*upper*/true);
        SDL_Rect d = btn_rect(i, /*upper*/false);
        if (u.x>=0 && u.y>=0){
            SDL_RenderFillRect(ren, &u);
            draw_button_text(u, labels[i]);
        }
        if (d.x>=0 && d.y>=0){
            SDL_RenderFillRect(ren, &d);
            draw_button_text(d, labels[i]);
        }
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
        debug_print("TTF_RenderUTF8 failed: %s\n", TTF_GetError());
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

void draw_stat_text(int x, int y, const char *utf8)
{
    SDL_Color white = {255, 255, 255, 255};           // 文字顏色
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font_main, utf8, white);
    if (!surf) { printf("TTF_RenderUTF8 failed: %s\n", TTF_GetError()); return; }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = {x, y, surf->w, surf->h};

    SDL_FreeSurface(surf);                            // surface 用完就可以丟
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_DestroyTexture(tex);                          // texture 也記得釋放
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
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                SDL_Point p = { e.button.x, e.button.y };

                if (id == BTN_SUPPLY_BASIC) {
                    int32_t cardType = detect_basic_stack(p);   // ← §2-A
                    if (cardType >= 0 &&
                        game_action_buy_basic(cardType, upper ? PLAYER2 : PLAYER1) == 0)
                        open = false;        // 買完就關視窗
                }
                else if (id == BTN_SUPPLY_SKILL) {
                    int32_t cardType = detect_skill_stack(p, upper ? PLAYER2 : PLAYER1);  // ← §2-B
                    if (cardType >= 0 &&
                        game_action_buy_skill(cardType, upper ? PLAYER2 : PLAYER1) == 0)
                        open = false;
                }
            }
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

                // 角色花紋／卡面
                SDL_Rect dstSheet = { dst.x+60, dst.y+60, 420, 260 };
                SDL_RenderCopy(ren, sheet[ characters[player] ], NULL, &dstSheet);

                // 讀取玩家目前數值
                sPlayerData pd;
                player_data_get(&pd, player);   // 失敗回 -1，這裡簡化不檢查

                // 每列 token 的起始座標
                SDL_Rect start_hp = {0};
                if(pd.hp >= 26){
                    start_hp.x = dst.x + PLATE_PADDING_X + (pd.hp-26)*18;
                    start_hp.y = ROW_HP_Y(dst);
                    start_hp.w = TOKEN_W;
                    start_hp.h = TOKEN_H;
                }
                else{
                    start_hp.x = dst.x + PLATE_PADDING_X + pd.hp*18;
                    start_hp.y = ROW_HP_Y(dst)-18;
                    start_hp.w = TOKEN_W;
                    start_hp.h = TOKEN_H;
                }
                SDL_Rect start_finish  = { dst.x + PLATE_PADDING_X + pd.hp_finish*18, ROW_HP_Y(dst)-18, TOKEN_W, TOKEN_H };

                SDL_Rect start_def     = { dst.x + PLATE_PADDING_X+18*26, ROW_HP_Y(dst)+18*3+pd.defense*18, TOKEN_W, TOKEN_H };

                SDL_Rect start_energy  = { dst.x + PLATE_PADDING_X-18+pd.power*18, ROW_HP_Y(dst)+18*17, TOKEN_W, TOKEN_H };

                SDL_RenderCopy(ren, token[2], NULL, &start_hp);
                if(pd.hp > pd.hp_finish){SDL_RenderCopy(ren, token[1], NULL, &start_finish);}
                SDL_RenderCopy(ren, token[3], NULL, &start_energy);
                SDL_RenderCopy(ren, token[0], NULL, &start_def);

                /* ==== 文字說明 ==== */
                char buf[64];
                int textX = dst.x + 30;              // 與 plate 左邊留一點 margin
                int textY = dst.y + 400;             // token 區塊下面再往下 20~30px

                // 血量
                snprintf(buf, sizeof(buf), "HP: %d / %d", pd.hp, pd.hp_max);
                draw_stat_text(textX, textY, buf);   textY += 24;

                // 防禦
                snprintf(buf, sizeof(buf), "DEFENSE: %d / %d", pd.defense, pd.defense_max);
                draw_stat_text(textX, textY, buf);   textY += 24;

                // 能量
                snprintf(buf, sizeof(buf), "ENERGY: %d / %d", pd.power, pd.power_max);
                draw_stat_text(textX, textY, buf);   textY += 24;

                // 必殺閥值（這裡假設用 hp_finish，若你要用別的欄位就換）
                snprintf(buf, sizeof(buf), "FINISH: %d", pd.hp_finish);
                draw_stat_text(textX, textY, buf);
                break;
            }
            case BTN_TWIST: {
                int player = upper ? PLAYER2 : PLAYER1;
                // // 清畫面，如果這邊是正式畫面主 loop 可以省略
                // SDL_RenderClear(ren);

                // // 渲染指定玩家的手牌
                // render_hand(ren, player, card_back, characters);

                // SDL_RenderPresent(ren);  // 顯示畫面
                while (open) {

                static bool         zoom_open = false;
                static SDL_Texture *zoom_tex  = NULL;

                while (SDL_PollEvent(&e)) {

                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                        if (zoom_open) {
                            zoom_open = false;          // 關閉放大
                        } else {
                            open = false;               // 關閉整個手牌視窗
                        }
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN &&
                            e.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_Point p = { e.button.x, e.button.y };

                        if (zoom_open) {                // 已放大 任何點擊都關閉
                            zoom_open = false;
                        } else {
                            int type = -1;
                            if (detect_hand_card_click(p, player, &type)) {
                                zoom_tex  = card_data_get_texture(type, player);
                                zoom_open = (zoom_tex != NULL);
                            }
                        }
                    }

                }

                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                SDL_RenderClear(ren);

                render_hand(ren, player, card_back, characters);

                if (zoom_open && zoom_tex) {
                    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
                    SDL_RenderFillRect(ren, NULL);

                    const int bigW = CARD_W * 3;
                    const int bigH = CARD_H * 3;
                    SDL_Rect dst = {
                        (WINDOW_WIDTH  - bigW) / 2,
                        (WINDOW_HEIGHT - bigH) / 2,
                        bigW, bigH
                    };
                    SDL_RenderCopy(ren, zoom_tex, NULL, &dst);
                    SDL_RenderDrawRect(ren, &dst);
                    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
                }

                SDL_RenderPresent(ren);
            }
                break;
            }
            case BTN_DECK: {
                // int player = upper ? PLAYER2 : PLAYER1;
                SDL_Rect back = { win.x+80, win.y+100, CARD_W,CARD_H };
                SDL_RenderCopy(ren, card_back, NULL, &back);
                SDL_Rect discard = { back.x+150, back.y, CARD_W,CARD_H };
                // SDL_RenderCopy(ren, basic_card[CARD_BASIC_ATTACK_L1], NULL, &discard); // top of discard
                // SDL_SetRenderDrawColor(ren, 0, 200, 255, 255);  // 藍色框
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
                            player, CARD_SPACE_SHOP, stacks[col][i], -1);
                        if (count > 0) {
                            SDL_Rect dst = {
                                x0 + col * dx + i * 2,   // 疊起來稍微偏移
                                y0 + i * 2,
                                CARD_W, CARD_H
                            };
                            SDL_RenderCopy(ren, tex[stacks[col][i]], NULL, &dst);
                        }
                        // if (count == 0) {
                        //     debug_print("⚠️ 未找到卡牌: type = %d, player = %d\n", stacks[col][i], player);
                        // }
                    }
                }

                // 顯示三張必殺牌
                for (int i = 0; i < 3; i++) {
                    sCardData list[2];
                    int32_t count = 0;
                    game_data_search_cards(list, &count,
                        player, CARD_SPACE_SHOP, finish[i], -1);
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
            case BTN_CARD_USED: {
                int32_t player = upper ? PLAYER2 : PLAYER1;
                int x0 = 0, y0 = 0;
                int dx = CARD_W + 40, dy = CARD_H + 60;
                int r_num_max= 5;
                int c_num_max= 10;
                SDL_Texture** tex;
                sCardData cards[CARD_NUM];
                int32_t card_num= 0;
                int32_t count= 0;
                game_data_search_cards (cards, &count, player, CARD_SPACE_USE, CARD_ORIGINAL, -1);
                card_num+= count;
                game_data_search_cards (cards+card_num, &count, player, CARD_SPACE_USE_LASTING, CARD_ORIGINAL, -1);
                card_num+= count;
                for (int32_t i=0; i<r_num_max; i++){
                    for (int32_t j=0; i*c_num_max+j<card_num && j<c_num_max; j++){
                        SDL_Rect dst = {
                            x0 + j * dx ,
                            y0 + i * dy ,
                            CARD_W, CARD_H
                        };
                        int32_t type= cards[i*c_num_max+j].type;
                        gui_imd_data_texture_get (&tex, type, player);
                        SDL_RenderCopy(ren, tex[type], NULL, &dst);
                    }
                }
                break;
            }
            case BTN_ROUND_END: {
                gui_round_running= false;
                open = false;
                debug_print ("end round\n");
                break;
            }
            case BTN_ACTION_FOCUS: {
                if (gui_action_focus (upper ? PLAYER2 : PLAYER1)<0) return;
                gui_round_running= false;
                return;
            }
            case BTN_ACTION_BASIC: {
                gui_action_use_basic (upper ? PLAYER2 : PLAYER1);
                return;
            }
            case BTN_ACTION_SKILL: {
                gui_action_use_skill (upper ? PLAYER2 : PLAYER1);
                return;
            }
            default: break;
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
}

void render_hand(SDL_Renderer* ren, int32_t player, SDL_Texture* card_back, int32_t characters[])
{
    sCardData cards[CARD_NUM];  // 預設最多不會超過手牌上限
    int32_t num = 0;

    // debug_print("呼叫查詢手牌: player=%d\n", player);
    // 查詢該玩家的手牌（space = CARD_SPACE_HAND）
    game_data_search_cards(cards, &num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    // debug_print("查到張數 = %d\n", num);

    int gap = 20, w = CARD_W, h = CARD_H;
    int base_x = 50;
    int base_y = (player == PLAYER1) ? 500 : 100;  // 玩家在下面，對手在上面

    for (int i = 0; i < num; ++i) {
        int32_t card_id = cards[i].index;
        // debug_print("player %d hand[%d] = card_id %d\n", player, i, card_id);

        SDL_Rect d = { base_x + i * (w + gap), base_y, w, h };

        if (player == PLAYER1) {
            SDL_Texture* tex = card_data_get_texture(cards[i].type, player);
            if (tex != NULL) SDL_RenderCopy(ren, tex, NULL, &d);
        } else {
            SDL_RenderCopy(ren, card_back, NULL, &d);
        }
    }
}

SDL_Texture* card_data_get_texture(int32_t card_type, int32_t player)
{
    // if (card_id < 0 || card_id >= CARD_NUM) return NULL;

    SDL_Texture ** tex;
    gui_imd_data_texture_get(&tex, card_type, player);
    return tex[card_type];
}

int32_t detect_basic_stack(SDL_Point p)
{
    const int start_x = 400, start_y = 100;
    const int offset_x = 120, offset_y = 160;

    // 3×3 三列三行（攻/防/移 × L1~L3）
    int col = (p.x - start_x) / offset_x;
    int row = (p.y - start_y) / offset_y;
    if (col < 0 || col > 2 || row < 0 || row > 2) goto check_common;

    // 點在卡片矩形內才算
    SDL_Rect rect = { start_x + col*offset_x, start_y + row*offset_y, CARD_W, CARD_H };
    if (!SDL_PointInRect(&p, &rect)) goto check_common;

    static const eCardType attack[]   = {CARD_BASIC_ATTACK_L1,   CARD_BASIC_ATTACK_L2,   CARD_BASIC_ATTACK_L3};
    static const eCardType defense[]  = {CARD_BASIC_DEFENSE_L1,  CARD_BASIC_DEFENSE_L2,  CARD_BASIC_DEFENSE_L3};
    static const eCardType movement[] = {CARD_BASIC_MOVEMENT_L1, CARD_BASIC_MOVEMENT_L2, CARD_BASIC_MOVEMENT_L3};

    const eCardType* table[] = {attack, defense, movement};
    return table[row][col];

check_common:
    /* 通用卡（Common）是在 attack 第 4 欄 */
    SDL_Rect rectCommon = { start_x + 3*offset_x, start_y, CARD_W, CARD_H };
    if (SDL_PointInRect(&p, &rectCommon)) return CARD_BASIC_COMMON;

    return -1;   // 點到空白
}

int32_t detect_skill_stack(SDL_Point p, int32_t player)
{
    const int x0 = 330, y0 = 120;
    const int dx = CARD_W + 40, dy = CARD_H + 60;

    // 3 固定列 = 攻、防、移
    int col = (p.x - x0) / dx;
    int row = (p.y - y0) / dy;   // row==0 → 技能，row==1 → finish
    if (col < 0 || col > 2) return -1;

    /* ① 技能三疊（五等級） */
    int type_stack[3]= {CARD_SKILL_ATTACK_BASE_L1, CARD_SKILL_DEFENSE_BASE_L1, CARD_SKILL_MOVEMENT_BASE_L1};
    int type_stack_max[3]= {CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_SKILL_MOVEMENT_EVOLUTION_L2};
    if (row == 0) {
        SDL_Rect top = { x0 + col*dx, y0, CARD_W, CARD_H };
        if (!SDL_PointInRect(&p, &top)) return -1;
        int idx= card_data_get_index (player, type_stack[col]);
        sCardData cd;
        while (1){
            card_data_get (&cd, idx);
            if (cd.type > type_stack_max[col]) return -1;
            if (cd.space == CARD_SPACE_SHOP) break;
            idx++;
        }
        return cd.type;
    }

    /* ② 必殺牌三張 */
    if (row == 1) {
        SDL_Rect top = { x0 + col*dx, y0 + dy, CARD_W, CARD_H };
        if (!SDL_PointInRect(&p, &top)) return -1;

        const int finish[] = {CARD_SKILL_FINISH1,
                              CARD_SKILL_FINISH2,
                              CARD_SKILL_FINISH3};
        return finish[col];
    }
    return -1;
}

bool detect_hand_card_click(SDL_Point p, int32_t player, int* outType)
{
    sCardData cards[CARD_NUM];
    int32_t   num = 0;
    game_data_search_cards(cards, &num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);

    const int gap    = 20;
    const int w      = CARD_W;
    const int h      = CARD_H;
    const int base_x = 50;
    const int base_y = (player == PLAYER1) ? 500 : 100;   // only this line changed

    for (int i = 0; i < num; ++i) {
        SDL_Rect r = { base_x + i*(w+gap), base_y, w, h };
        if (SDL_PointInRect(&p, &r)) {
            *outType = cards[i].type;
            return true;
        }
    }
    return false;
}

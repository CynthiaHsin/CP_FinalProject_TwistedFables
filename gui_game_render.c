#include "gui_sdl_config.h"
#include "gui_img_data.h"
#include "game_data.h"

void draw_board(int32_t characters[]);
void draw_buttons(void);
bool handle_button_click(SDL_Point p, int32_t characters[]);
void draw_button_text(SDL_Rect rect, const char* text);
void popup(enum BtnId id, bool upper, int32_t characters[]);
void draw_token_row(SDL_Texture* tex, SDL_Rect rowStart, int tokenCnt, int tokenFilled);
void render_hand(SDL_Renderer* ren, int32_t player, SDL_Texture* card_back, int32_t characters[]);
SDL_Texture* card_data_get_texture(int32_t card_id, int32_t characters[], int32_t player);

bool gui_round_running;

void game_scene_loop(int32_t characters[])
{
    gui_round_running = true;
    SDL_Event e;

    while (gui_round_running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                gui_round_running = false;
                status_data_end_game();
                return;
            }
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
                // SDL_Rect start_finish  = { dst.x + PLATE_PADDING_X, ROW_HP_Y(dst)-18, TOKEN_W, TOKEN_H };
                SDL_Rect start_finish  = { dst.x + PLATE_PADDING_X + pd.hp_finish*18, ROW_HP_Y(dst)-18, TOKEN_W, TOKEN_H };
                // SDL_Rect start_def     = { dst.x + PLATE_PADDING_X+18*26, ROW_HP_Y(dst)+18*3, TOKEN_W, TOKEN_H };
                SDL_Rect start_def     = { dst.x + PLATE_PADDING_X+18*26, ROW_HP_Y(dst)+18*3+pd.defense*18, TOKEN_W, TOKEN_H };
                // SDL_Rect start_energy  = { dst.x + PLATE_PADDING_X-18, ROW_HP_Y(dst)+18*17, TOKEN_W, TOKEN_H };
                SDL_Rect start_energy  = { dst.x + PLATE_PADDING_X-18+pd.power*18, ROW_HP_Y(dst)+18*17, TOKEN_W, TOKEN_H };

                SDL_RenderCopy(ren, token[2], NULL, &start_hp);
                if(pd.hp > pd.hp_finish){SDL_RenderCopy(ren, token[1], NULL, &start_finish);}
                SDL_RenderCopy(ren, token[3], NULL, &start_energy);
                SDL_RenderCopy(ren, token[0], NULL, &start_def);
                break;
            }
            case BTN_TWIST: {
                int player = upper ? PLAYER2 : PLAYER1;
                // 清畫面，如果這邊是正式畫面主 loop 可以省略
                SDL_RenderClear(ren);

                // 渲染指定玩家的手牌
                render_hand(ren, player, card_back, characters);

                SDL_RenderPresent(ren);  // 顯示畫面
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
                debug_print ("action focus not done\n");
                return;
            }
            case BTN_ACTION_BASIC: {
                debug_print ("action use basic not done\n");
                return;
            }
            case BTN_ACTION_SKILL: {
                debug_print ("action use skill not done\n");
                return;
            }
            default: break;
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
}

// 把一種類型的 token 連續畫在一條水平列上
void draw_token_row(SDL_Texture* tex, SDL_Rect rowStart, int tokenCnt, int tokenFilled)
{
    for (int i = 0; i < tokenCnt; ++i) {
        SDL_Rect r = rowStart;
        r.x += i * TOKEN_W;
        if (i < tokenFilled)      // 已獲得/已損失 才顯示
            SDL_RenderCopy(ren, tex, NULL, &r);
    }
}

void render_hand(SDL_Renderer* ren, int32_t player, SDL_Texture* card_back, int32_t characters[])
{
    sCardData cards[CARD_NUM];  // 預設最多不會超過手牌上限
    int32_t num = 0;

    // debug_print("呼叫查詢手牌: player=%d\n", player);
    // 查詢該玩家的手牌（space = CARD_SPACE_HAND）
    game_data_search_cards(cards, &num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    // debug_print("查到張數 = %d\n", num);

    int gap = 20, w = 105, h = 160;
    int base_x = 50;
    int base_y = (player == PLAYER1) ? 500 : 100;  // 玩家在下面，對手在上面

    for (int i = 0; i < num; ++i) {
        int32_t card_id = cards[i].index;
        // debug_print("player %d hand[%d] = card_id %d\n", player, i, card_id);

        SDL_Rect d = { base_x + i * (w + gap), base_y, w, h };

        if (player == PLAYER1) {
            SDL_Texture* tex = card_data_get_texture(cards[i].type, characters, player);
            if (tex != NULL) SDL_RenderCopy(ren, tex, NULL, &d);
        } else {
            SDL_RenderCopy(ren, card_back, NULL, &d);
        }
    }
    // sPlayerData pdata;
    // if (player_data_get(&pdata, player) < 0) return;

    // int gap = 20, w = 105, h = 160;
    // int base_x = 50;
    // int base_y = (player == PLAYER1) ? 500 : 100;  // 玩家在下面，對手在上面
    // int count = 0;

    // for (int i = 0; i < CARD_SPACE_HAND; ++i) {
    //     int32_t card_id = pdata.card_on[i];
    //     if (card_id == CARD_UNDEFINED) continue;
    //     debug_print("player %d hand[%d] = card_id %d\n", player, i, card_id);

    //     SDL_Rect d = { base_x + count * (w + gap), base_y, w, h };

    //     if (player == PLAYER1) {
    //         // 顯示卡片正面
    //         SDL_Texture* tex = card_data_get_texture(card_id, characters, player);
    //         if (tex != NULL) SDL_RenderCopy(ren, tex, NULL, &d);
    //     } else {
    //         // 顯示卡背
    //         SDL_RenderCopy(ren, card_back, NULL, &d);
    //     }
    //     count++;
    // }
}

SDL_Texture* card_data_get_texture(int32_t card_type, int32_t characters[], int32_t player)
{
    // if (card_id < 0 || card_id >= CARD_NUM) return NULL;

    SDL_Texture ** tex;
    gui_imd_data_texture_get(&tex, card_type, player);
    return tex[card_type];

    // if (card_id >= CARD_BASIC_ATTACK_L1 && card_id <= CARD_BASIC_DEFENSE_L3) {
    //     return basic_card[card_id];  // 基本牌：ID 可當 index
    // }

    // int32_t owner;
    // if (card_data_get_owner(card_id, &owner) < 0) return NULL;

    // switch (characters[player]) {
    //     case CHARACTER_RED_RIDING_HOOD:     return rrh_card[card_id];
    //     case CHARACTER_SNOW_WHITE: return sw_card[card_id];
    //     case CHARACTER_MULAN:   return mulan_card[card_id];
    //     case CHARACTER_KAGUYA:  return kaguya_card[card_id];
    //     case CHARACTER_DOROTHY: return dorothy_card[card_id];
    //     case CHARACTER_MATCH_GIRL: return mg_card[card_id];
    //     default: return NULL;
    // }
}

// int32_t card_data_get_owner(int32_t card_id, int32_t* player)
// {
//     if (card_id < 0 || card_id >= CARD_NUM || player == NULL) return -1;

//     *player = card_data[card_id].player;
//     return 0;
// }

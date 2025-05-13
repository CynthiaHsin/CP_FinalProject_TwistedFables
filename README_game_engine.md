# README about Game Engine

### 全域設定
- main.h
    - 統一引入基礎 header file
    ```c
    # include <stdio.h>
    # include <stdint.h>
    # include <stdlib.h>
    # include <string.h>
    # include <time.h>
    # include <math.h>
    # include <sys/param.h>
    # include "main_debug.h"
    # include "main_config.h"
    ```
- main_cofig.h
    - 設置所有全域要用的 define 值
    ```c
    typedef enum _eCardType eCardType;
    typedef enum _eCardSpace eCardSpace;
    typedef enum _eCharacter eCharacter;
    typedef enum _eGameMode eGameMode;
    typedef enum _ePlayer ePlayer;
    typedef enum _eAction eAction;
    ```

### 遊戲資料
- game_data.h
    - 提供資料讀取
    ```c
    // card

    typedef struct _sCardData{
        int32_t index;
        int32_t player; // 屬於誰的卡： bisic 預設 undefined，購買後屬於某玩家；skill預設屬於該玩家
        int32_t space;
        int32_t type;
    } sCardData;

    // basic
    int32_t game_data_get_card (sCardData *pCard, int32_t idx);                         // 取得「牌編號idx」的資料
    int32_t game_data_search_cards (sCardData cards[], int32_t *pGet_num, int32_t player, int32_t space, int32_t type) // 查詢，所有符合條件的牌，ORIGINAL代表不篩選此項，無錯誤回傳符合數量（=*pGet_num）

    // deck
    int32_t game_data_get_deck_card (sCardData *pCard, int32_t player, int32_t idx);    // 取得「玩家(player)的牌庫頂，第(idx)張牌」的資料
    int32_t game_data_deck_card_delete (int32_t player, int32_t idx);                   // 將「玩家(player)的牌庫頂，第(idx)張牌」移除
    int32_t game_data_deck_card_take (int32_t player, int32_t idx);                     // 將「玩家(player)的牌庫頂，第(idx)張牌」抽進手牌
    ```
    ```c
    // player

    typedef struct _sPlayerData{
        int32_t player;     // enum ePlayer
        int32_t character;  // enum eCharacter
        int32_t token;
        int32_t token_max;
        int32_t hp;
        int32_t hp_finish;  // 必殺閾值
        int32_t hp_max;
        int32_t defense;
        int32_t defense_max;
        int32_t power;
        int32_t power_max;
        int32_t pos;
    } sPlayerData;

    // basic
    int32_t game_data_get_player (sPlayerData *pPlayer_data, int32_t player);           // 取得「玩家(player)」的資料
    ```

### 遊戲進行

- game_action.h
    - 回合進行中，執行動作
    ```c
    // allow 陣列索引值為eAction中的各個動作, 目前設計只檢查專注
    int32_t game_action_actions_allow (int32_t allow[], int32_t player);
        // 陣列儲存值: 
        // 1 true(可以執行此動作), 
        // 0 flase(不可執行)，
    ```
    ```c
    // 使用基本牌
    int32_t game_action_use_basic_card (int32_t card_idx, int32_t card_type, int32_t token_num, int32_t move_direction, int32_t player_use, int32_t player_des);
        // card_idx: 要使用的卡牌編號, 
        // card_type: 使用卡牌種類, 
        // token_num: 用幾個token（沒有就0）,
        // move_direction: 1 or -1 or 0,
        // player_use: 使用者,
        // player_des: 目標，沒有目標的話就用 PLAYER_ORIGINAL
    ```
    ```c
    // 玩家 player 購買編號 card_idx 的牌，如果買到剛好能買蛻變牌，會直接自動買好
    int32_t game_action_buy_card (int32_t card_idx, int32_t player);
    ```
    ```c
    // 玩家 player 執行專注
    int32_t game_action_focus (int32_t card_delete_hand, int32_t card_delete_throw, int32_t player);
        // 刪除：
        // 手牌中，編號card_delete_hand
        // 棄牌堆中，編號card_delete_throw
    ```
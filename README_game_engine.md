# README about Game Engine

## 檔案

### 全域設定
- main.h
    - 統一引入基礎 header file
    ```
    # include <stdio.h>
    # include <stdint.h>
    # include <stdlib.h>
    # incldue <time.h>
    # include "main_debug.h"
    # include "main_config.h"
    ```
- main_cofig.h
    - 設置所有全域要用的 define 值
    ```
    typedef enum _eCard eCard;
    typedef enum _eCharacter eCharacter;
    typedef enum _eGAMEMODE eGAMEMODE;
    ```

### 遊戲資料
- game_data.h
    - 提供資料讀取
    ```
    typedef struct _sCardData{
        int32_t index;
        int32_t player; // 屬於誰的卡： bisic 預設 undefined，購買後屬於某玩家；skill預設屬於該玩家
        int32_t space;
        int32_t type;
    } sCardData;

    int32_t game_data_get_card (sCardData *pCard, int32_t idx);                         // 取得「牌編號idx」的資料
    int32_t game_data_get_deck_card (sCardData *pCard, int32_t player, int32_t idx);    // 取得「玩家(player)的牌庫頂，第(idx)張牌」的資料
    
    int32_t game_data_deck_card_delete (int32_t player, int32_t idx);                   // 將「玩家(player)的牌庫頂，第(idx)張牌」移除
    
    int32_t game_data_deck_card_take (int32_t player, int32_t idx);                     // 將「玩家(player)的牌庫頂，第(idx)張牌」抽進手牌
    int32_t game_data_search_cards (sCardData cards[], int32_t *pGet_num, int32_t player, int32_t space, int32_t type) // 查詢，所有符合條件的牌，ORIGINAL代表不篩選此項，無錯誤回傳符合數量（=*pGet_num）

    ```

### 遊戲進行

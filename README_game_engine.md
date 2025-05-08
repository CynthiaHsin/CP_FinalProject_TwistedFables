# README about Game Engine

## 檔案

### 全域設定
- main.h
    - 統一引入基礎 header file
    ```
    # include <stdio.h>
    # include <stdint.h>
    # include <stdlib.h>
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
    int32_t game_data_get_card (sCardData *pCard, int32_t idx); // 讀取編號idx的卡牌資料
    ```
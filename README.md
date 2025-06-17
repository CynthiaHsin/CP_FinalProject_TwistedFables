# CP_FinalProject_TwistedFables
> 2025 NTNU CSIE Computer Programming II Final Project 
> Twist Fables

---

## 使用說明

本專題使用 C 語言開發，並搭配 SDL2 函式庫。

### 執行步驟

1. 請先安裝 SDL2：
   >以 Ubuntu 為例：
   ```bash
   sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
   ```

2. 編譯專案：
   ```bash
   make
   ```

3. 執行遊戲：

   ```bash
   ./game
   ```
---

## 遊戲介紹

### 基本流程

1. 遊戲開始畫面
2. 選擇角色
3. 初始化設置（包含角色狀態與各類牌庫）
4. 重複進行對戰回合，直到一方勝出

### 卡牌分類

* 基本供應牌庫（公共）
* 技能供應牌庫（私人）
* 必殺牌庫
* 出牌區、棄牌堆、抽牌堆與蛻變區

### 遊戲回合概覽

每回合包含以下階段：

1. **回合開始階段**：結算持續效果
2. **行動階段**：出牌、移動、購牌與觸發技能
3. **清理階段**：棄牌、防禦歸零等處理
4. **回合結束階段**：重置能量、抽新手牌

---

## 成員與分工

- [@CynthiaHsin](https://github.com/CynthiaHsin)  ：遊戲邏輯架構
- [@willyliki  ](https://github.com/willyliki)      ：遊戲介面
- [@AndyShe-811](https://github.com/AndyShe-811)  ：對戰機器人

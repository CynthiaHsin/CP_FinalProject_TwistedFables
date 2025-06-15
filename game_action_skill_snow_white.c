# include "game_action_skill_snow_white.h"
# include "main.h"
# include "game_data.h"
# include "game_action.h"
int32_t poison_card_top;
sSnowWhite_Status snow_white;//這可能可以寫進去初始化裡面
sStatus player;
int32_t skill_snow_white (int32_t card_idx[Snow_White_CARD_IDX_NUM], int32_t move_direction, int32_t player_use, int32_t player_des)
{
    sCardData card_data[Snow_White_CARD_IDX_NUM];
    card_data_get(&card_data[Snow_White_CARD_IDX_SKILL], card_idx[Snow_White_CARD_IDX_SKILL]);
    card_data_get(&card_data[Snow_White_CARD_IDX_ATTACH], card_idx[Snow_White_CARD_IDX_ATTACH]);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    sPlayerData player_data_des;
    player_data_get(&player_data_des, player_des);
    int32_t attack_area=0;
    int32_t card_level = card_data_get_level(card_data[Snow_White_CARD_IDX_SKILL].type);
    switch (card_data[0].type) 
    {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        {
            int32_t attach_level= card_attach_calculate(card_idx[Snow_White_CARD_IDX_ATTACH], ACTION_ATTACK);
            int32_t level=card_level+attach_level;
            attack_area = 1;
            int32_t num=0;
            sCardData cards[1];
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
            if(level>=2&&game_data_search_cards ( cards, &num,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)snow_white_poison(player_des,1);
            card_data_set (card_idx[Snow_White_CARD_IDX_ATTACH], 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_data[Snow_White_CARD_IDX_SKILL].index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            game_data_deck_card_fold( player_des,card_level);
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            int32_t attach_level= card_attach_calculate(card_idx[Snow_White_CARD_IDX_ATTACH], ACTION_DEFENSE);
            int32_t level;
            attack_area = (card_level-1)+attach_level;
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
            int32_t move_area=abs(player_data_des.pos-player_data_use.pos)+move_direction;
            action_move (move_area, move_direction, player_use);
            card_data_set (card_idx[Snow_White_CARD_IDX_ATTACH], 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[Snow_White_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        {
            int32_t attach_level= card_attach_calculate(card_idx[Snow_White_CARD_IDX_ATTACH], ACTION_MOVE);
            int32_t level=card_level;
            attack_area = 1;
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
            if(snow_white_poison(player_des,attach_level) < 0)debug_print("Don't have enough poison card");
            card_data_set (card_idx[Snow_White_CARD_IDX_ATTACH], 1, CARD_SPACE_THROW, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[Snow_White_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        case CARD_SKILL_FINISH1:
        {
        int32_t num1,num2,num3,num;
        sCardData cards[1];
        game_data_search_cards ( cards, &num1,  player_des, CARD_SPACE_THROW, CARD_POISON_L1, CARD_COST_ORIGINAL); 
        game_data_search_cards ( cards, &num2,  player_des, CARD_SPACE_THROW, CARD_POISON_L2, CARD_COST_ORIGINAL); 
        game_data_search_cards ( cards, &num3,  player_des, CARD_SPACE_THROW, CARD_POISON_L3, CARD_COST_ORIGINAL); 
        num=num1+num2+num3;
        int32_t distance=abs(player_data_des.pos-player_data_use.pos);
        
        if(num!=0&&distance<=1)player_data_des.hp-=num;
        card_data_set (card_idx[Snow_White_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        break;
        }
        case CARD_SKILL_FINISH2:
        {
        sCardData cards[30];
        int32_t num;
        int32_t level=3;
        attack_area=1;
        action_attack(level, attack_area, player_use, player_des);
        game_data_search_cards ( cards, &num,  player_des, CARD_SPACE_HAND, CARD_ORIGINAL, CARD_COST_ORIGINAL);
        for(int32_t i=0;i<num;i++)
        {
            cards[i].space=CARD_SPACE_THROW;
        }
        deck_data_draw_cards (player_des, 4);
        card_data_set (card_idx[Snow_White_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        break;
        }
        case CARD_SKILL_FINISH3:
        {
            if(card_idx[Snow_White_CARD_IDX_FINISH1]!=-1)
            {
                card_data_get(&card_data[Snow_White_CARD_IDX_FINISH1], card_idx[Snow_White_CARD_IDX_FINISH1]);
                card_data[Snow_White_CARD_IDX_FINISH1].space=CARD_SPACE_DECK;
            }
            if(card_idx[Snow_White_CARD_IDX_FINISH2]!=-1)
            {
                card_data_get(&card_data[Snow_White_CARD_IDX_FINISH2], card_idx[Snow_White_CARD_IDX_FINISH2]);
                card_data[Snow_White_CARD_IDX_FINISH2].space=CARD_SPACE_DECK;
            }
            if(card_idx[Snow_White_CARD_IDX_FINISH3]!=-1)
            {
                card_data_get(&card_data[Snow_White_CARD_IDX_FINISH3], card_idx[Snow_White_CARD_IDX_FINISH3]);
                card_data[Snow_White_CARD_IDX_FINISH3].space=CARD_SPACE_DECK;
            }
            card_data_set (card_idx[Snow_White_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        
    }
}

int32_t snow_white_poison ( int32_t player_des,int32_t idx )
{
    
    sCardData cards[10];
    int32_t n=0;
    for(int32_t i=0; i<idx;i++)
    {
        game_data_search_cards ( cards, &n, PLAYER_ORIGINAL, CARD_SPACE_DECK_POISON, CARD_POISON_L1, CARD_COST_ORIGINAL);
        if(n!=0)
        {
            card_data_set (cards[0].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, player_des);
            continue;
        } 
        game_data_search_cards ( cards, &n, PLAYER_ORIGINAL, CARD_SPACE_DECK_POISON, CARD_POISON_L2, CARD_COST_ORIGINAL);
        if(n!=0)
        {
            card_data_set (cards[0].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, player_des);
            continue;
        }  
        game_data_search_cards ( cards, &n, PLAYER_ORIGINAL, CARD_SPACE_DECK_POISON, CARD_POISON_L3, CARD_COST_ORIGINAL);
        if(n!=0)
        {
            card_data_set (cards[0].index, 1, CARD_SPACE_THROW, CARD_ORIGINAL, player_des);
            continue;
        } 
        if(n==0)return -1;;
    }
    return 0;
   
}
//確認他們有沒有和開movementtwist的白雪公主交換位子
int32_t skill_snow_white_movement_evolution(int32_t player_use,int32_t move_direction,int32_t delta)
{
    int32_t player_des=0;
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    if(PLAYER1==player_use)player_des=PLAYER2;
    else player_des=PLAYER1;
    sPlayerData player_data_des;
    player_data_get(&player_data_des, player_des);
    sCardData cards[1];
    int32_t num=0;
    int32_t early_distance=player_data_use.pos-player_data_des.pos;
    int32_t des=player_data_use.pos+(move_direction*delta);
    while (map_data_cannot_move(0, des, player_use)){
        int32_t stay= player_data_use.pos - des;
        stay/= abs(stay);
        des+= stay;    
    }
    int32_t later_distance=des-player_data_des.pos;
    if((game_data_search_cards  (cards, &num,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )>0&&later_distance<0&&early_distance>0)||(game_data_search_cards ( cards, &num,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )>0&&later_distance>0&&early_distance<0))return 0;
}

int32_t snow_white_poison_count(int32_t *card, int32_t len, int32_t player_des)
{
    int32_t player_use= player_data_search_character(CHARACTER_SNOW_WHITE);
    if (player_use == PLAYER_UNDEFINED) return 0;
    int32_t posion_level=0,n=0,poison,num;
    sCardData *card_data;
    sCardData cards[1];
    card_data=malloc(len*sizeof(sCardData));
    for(int32_t i=0;i<len;i++)card_data_get(&card_data[i],card[i]);
    for(int32_t i=0;i < len;i++)
    {
        switch(card_data[i].type)
        {
            case CARD_POISON_L1:
                poison+=1;
                num+=1;
            case CARD_POISON_L2:
                poison+=2;
                num+=1;
            case CARD_POISON_L3:
                poison+=3;
                num+=1;
        }
    }
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)posion_level+=1;
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)posion_level+=1;
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)posion_level+=1;
    poison+=num*posion_level;
    sPlayerData player_data_des;
    player_data_get(&player_data_des,player_des);
    player_data_des.hp-=poison;
    player_data_set(player_des,player_data_des);
}
#include"game_action_skill_match_girl.h"
#include"main.h"
# include "game_data.h"
# include "game_action_basic.h"

#include<stdint.h>

int32_t skill_match_girl (int32_t card_idx[Match_Girl_CARD_IDX_NUM],  int32_t player_use, int32_t player_des)
{
    sCardData card_data[Match_Girl_CARD_IDX_NUM];
    card_data_get(&card_data[Match_Girl_CARD_IDX_SKILL], card_idx[Match_Girl_CARD_IDX_SKILL]);
    card_data_get(&card_data[Match_Girl_CARD_IDX_ATTACH], card_idx[Match_Girl_CARD_IDX_ATTACH]);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    sPlayerData player_data_des;
    player_data_get(&player_data_des, player_des);
    int32_t attack_area=0;
    int32_t card_level = card_data_get_level(card_data[Match_Girl_CARD_IDX_SKILL].type);
    switch (card_data[0].type) 
    {
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        {
            
            
            if(card_idx[Match_Girl_POWER_NUM_ATTACK]>player_data_use.power)return -1;
            int32_t attach_level= card_attach_calculate(card_idx[Match_Girl_CARD_IDX_ATTACH], ACTION_ATTACK);
            int32_t power_plus=(card_idx[Match_Girl_POWER_NUM_ATTACK]/3);
            if(card_idx[Match_Girl_POWER_NUM_ATTACK]<=0)power_plus=0;
            
            player_data_use.power-=card_idx[Match_Girl_POWER_NUM_ATTACK];
            attack_area = 1;
            int32_t damage_plus=0;
            damage_plus=skill_match_girl_attack_evolution( player_des);
            int32_t level=card_level+attach_level+power_plus+damage_plus;
            
            
            if (action_attack(level, attack_area, player_use, player_des) < 0) {
                return -1;
            }
            player_data_set(player_use,player_data_use);
            card_data_set (card_idx[Match_Girl_CARD_IDX_ATTACH], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_data[Match_Girl_CARD_IDX_SKILL].index, 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            int32_t attach_level= card_attach_calculate(card_idx[Match_Girl_CARD_IDX_ATTACH], ACTION_DEFENSE);
            int32_t level=card_level;
            attack_area = card_level;
            
            action_attack(level, attack_area, player_use, player_des); 
                
            
            int32_t power_plus=match_girl_match (  player_des,attach_level );
            player_data_use.power+=power_plus;
            player_data_set(player_use,player_data_use);
            card_data_set (card_idx[Match_Girl_CARD_IDX_ATTACH], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[Match_Girl_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        {
            int32_t attach_level= card_attach_calculate(card_idx[Match_Girl_CARD_IDX_ATTACH], ACTION_MOVE);
            
            int32_t level=attach_level;
            sCardData cards[CARD_MATCH_NUM];
            int32_t n=0;
            if (action_defense (level, player_use) < 0) {
                return -1;
            }
            if(card_idx[Match_Girl_HP_NUM_DEFENSE]<0)return -1;
            if(card_idx[Match_Girl_HP_NUM_DEFENSE]>card_level)card_idx[Match_Girl_HP_NUM_DEFENSE]=card_level;
            deck_data_draw_cards (player_use,card_idx[Match_Girl_HP_NUM_DEFENSE] );
            player_data_get(&player_data_use,player_use);
            player_data_use.hp-=card_idx[Match_Girl_HP_NUM_DEFENSE];
            player_data_set(player_use,player_data_use);
            int32_t num=0;
            if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)num=match_girl_match(player_des,1);
            deck_data_draw_cards (player_use,num );
            card_data_set (card_idx[Match_Girl_CARD_IDX_ATTACH], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            card_data_set (card_idx[Match_Girl_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            
            break;
        }
        case CARD_SKILL_FINISH1:
        {
        int32_t power_plus=player_data_use.power/2;
        float power_remainder=player_data_use.power/2;
        
        if((power_remainder-power_plus)!=0)power_plus+=1;
        
        action_attack (power_plus, 1,  player_use,  player_des);
        card_data_set (card_idx[Match_Girl_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        break;
        }
        case CARD_SKILL_FINISH2:
        {
        int32_t n_bf=0,n_af=0;
        sCardData cards[30];
        int32_t distance=abs(player_data_use.pos-player_data_des.pos);
        if(distance>3)return -1;
        else 
        {
            game_data_search_cards ( cards, &n_bf, player_des, CARD_SPACE_THROW, CARD_MATCH, CARD_COST_ORIGINAL);
            game_data_deck_card_fold (player_des, 6);
            game_data_search_cards ( cards, &n_af, player_des, CARD_SPACE_THROW, CARD_MATCH, CARD_COST_ORIGINAL);
            action_attack ((n_af-n_bf), 3, player_use, player_des);
        }
        card_data_set (card_idx[Match_Girl_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
        break;
        }
        case CARD_SKILL_FINISH3:
        {
            sCardData cards[30];
           int32_t n=0;
           game_data_search_cards ( cards, &n, player_use, CARD_SPACE_DECK_MATCH, CARD_MATCH, CARD_COST_ORIGINAL);
           if(n>3)n=3;
           
           for(int32_t i=0;i<n;i++)
           {
            
            deck_data_card_put (cards[i].index,  player_des);
           }
            card_data_set (card_idx[Match_Girl_CARD_IDX_SKILL], 1, CARD_SPACE_USE, CARD_ORIGINAL, PLAYER_ORIGINAL);
            break;
        }
    }
    return 0;
}

int32_t match_girl_match ( int32_t player_des,int32_t idx )
{
    
    sCardData cards[30];
    int32_t n=0,num=0;
    int32_t player_use= player_data_search_character(CHARACTER_MATCH_GIRL);
    game_data_search_cards ( cards, &n, player_des, CARD_SPACE_THROW, CARD_MATCH, CARD_COST_ORIGINAL);
    if(n!=0)
    {
        if(n>=idx)n=idx;
        
        for(int32_t i=0;i<n;i++)
        {
            card_data_set (cards[i].index, 1, CARD_SPACE_DECK_MATCH, CARD_ORIGINAL,player_use );
            //printf("card=%d\n",cards[i].index);
            num++;
        }   
        
    } 
   
    return num; 
}
int32_t skill_match_girl_attack_evolution(int32_t player_des)
{
    sCardData cards[30];
    int32_t n=0;
    int32_t player_use= player_data_search_character(CHARACTER_MATCH_GIRL);
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)
    {
        if(match_girl_match (  player_des,1  )==0)return 0;
        return 2; 
    }
    return 0;
}
//可以加上傷害在裡面，這樣可以用盾來算
int32_t skill_match_girl_movement_evolution(int32_t damage,int32_t player_des,int32_t move_direction)
{
    int32_t player_use= player_data_search_character(CHARACTER_MATCH_GIRL);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
   
    sCardData cards[30];
    int32_t n=0;
    if(player_data_use.defense<damage)
    {
        if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)match_girl_match(player_des,1);
        action_move (1, move_direction,  player_use);
    }
    return 0;
}

int32_t skill_match_girl_evolution2(int32_t player_des)
{
    int32_t player_use= player_data_search_character(CHARACTER_MATCH_GIRL);
    sPlayerData player_data_use;
    player_data_get(&player_data_use, player_use);
    
    sCardData cards[30];
    
    int32_t n=0,num=0;
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)num+=1;
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)num+=1;
    if(game_data_search_cards  (cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)num+=1;
    game_data_search_cards  (cards, &n,  player_des, CARD_SPACE_USE, CARD_MATCH, CARD_COST_ORIGINAL );
    for(int32_t i=0;i<num;i++)
    {
        player_data_use.power+=1;
    }
    player_data_set(player_use, player_data_use);
    return 0;
}
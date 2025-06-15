#include"main.h"
#include"snow_white_robot.h"
#include"game_action_skill_snow_white.h"
#include"game_data.h"
#include"game_action.h"
#include<stdint.h>
sSnow_White_Robot snow_white_best_status;

int32_t snow_white_process(int *card_idx, int end,int *best_card,int *best_card_skill,int *best_card_defense, int32_t player_use,int32_t player_des) {
    if(card_idx==NULL)return -1;
    int32_t len=end;
    sSnow_White_Robot status;
    status.poison=0;
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    int32_t *card_skill;
    int32_t *card_defense;
    int32_t *card_idx_tmp;
    int32_t poison_num=0,tmp_poison=0;
    int32_t poison_idx[CARD_NUM];
    sCardData poison_card[CARD_NUM];
    game_data_search_cards ( poison_card, &tmp_poison,  player_use, CARD_SPACE_DECK_POISON, CARD_POISON_L1, CARD_COST_ORIGINAL );
    for(int32_t i=0;i<tmp_poison;i++)poison_idx[i]=poison_card[i].index;
    poison_num+=tmp_poison;
    game_data_search_cards ( poison_card, &tmp_poison,  player_use, CARD_SPACE_DECK_POISON, CARD_POISON_L1, CARD_COST_ORIGINAL );
    for(int32_t i=poison_num;i<(tmp_poison+poison_num);i++)poison_idx[i]=poison_card[i-poison_num].index;
    poison_num+=tmp_poison;
    game_data_search_cards ( poison_card, &tmp_poison,  player_use, CARD_SPACE_DECK_POISON, CARD_POISON_L1, CARD_COST_ORIGINAL );
    for(int32_t i=poison_num;i<(tmp_poison+poison_num);i++)poison_idx[i]=poison_card[i-poison_num].index;
    poison_num+=tmp_poison;


    player_data_get(&player_data_use, player_use);
    player_data_get(&player_data_des, player_des);

    
    card_defense=(int32_t *)malloc(len*sizeof(int32_t));
    card_skill=(int32_t *)malloc(len*sizeof(int32_t));
    card_idx_tmp=(int32_t *)malloc(len*sizeof(int32_t));
    for(int32_t i=0;i<end;i++)
    {
        card_defense[i]=-1;
        card_skill[i]=-1;
        card_idx_tmp[i]= -1;
    }

        sCardData *card_data;
        card_data=malloc(len*sizeof(sCardData));
        //printf("card_idx=");
        for(int32_t i=0; i<end; i++)
        {
        card_data_get(&card_data[i], card_idx[i]);
        //printf("%d,",card_idx[i]);
        }
        //printf("\n");
        // 每個可能的組合跑一遍
        for (int i = 0; i < len; i++) 
        {
            int card[Snow_White_CARD_IDX_NUM];
            for(int32_t i=0;i<Snow_White_CARD_IDX_NUM;i++)card[i]=-1;
            sCardData cards[30];
            int n=0;
        for(int32_t k=0;k<len;k++)
        {
            if(card_skill[k]==card_idx[i])n=1;
        }
        if(n==1)continue;
            switch(card_data[i].type)
            {
            case CARD_SKILL_ATTACK_BASE_L1:
            case CARD_SKILL_ATTACK_BASE_L2:
            case CARD_SKILL_ATTACK_BASE_L3:
            {
            for(int32_t k=i+1;k<end;k++)
            {
                card[Snow_White_CARD_IDX_SKILL]=card_idx[i];
                card[Snow_White_CARD_IDX_ATTACH]=card_idx[k];
                
                if(skill_snow_white  (card,  0, player_use, player_des)<0)continue;
                else
                {
                    card_idx_tmp[i]=card_idx[i];
                    card_skill[i]=card_idx[k];
                    break;
                }

                
                
            }
            break;
            }
            case CARD_SKILL_MOVEMENT_BASE_L1:
            case CARD_SKILL_MOVEMENT_BASE_L2:
            case CARD_SKILL_MOVEMENT_BASE_L3:
            {
            for(int32_t k=i+1;k<end;k++)
            {
                card[0]=card_idx[i];
                card[Snow_White_CARD_IDX_ATTACH]=card_idx[k];
                int32_t move_direction=(-player_data_des.pos)/player_data_des.pos;
                
                if(skill_snow_white(card,move_direction, player_use, player_des)<0)continue;
                
                card_idx_tmp[i]=card_idx[i];
                card_skill[i]=card_idx[k];
                //printf("skill=%d\n",card_idx[k]);
         
                break;
                    
                   
            }
            break;
            }
            case CARD_SKILL_DEFENSE_BASE_L1:
            case CARD_SKILL_DEFENSE_BASE_L2:
            case CARD_SKILL_DEFENSE_BASE_L3:
            {
            for(int32_t k=i+1;k<end;k++)
            {
                card[0]=card_idx[i];
                card[Snow_White_CARD_IDX_ATTACH]=card_idx[k];
                int32_t num=0;
                sCardData poison_card_tmp;
                poison_card_tmp.index=0;
                poison_card_tmp.type=0;
                //int32_t a=game_data_search_cards ( cards, &num,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL );
                
                if(game_data_search_cards ( cards, &num,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)
                {
                        num=card_attach_calculate(card_idx[k], ACTION_DEFENSE);
                        
                        for(int32_t i=0; i<num;i++)
                        {
                            game_data_search_cards ( cards, &n, PLAYER_ORIGINAL, CARD_SPACE_DECK_POISON, CARD_POISON_L1, CARD_COST_ORIGINAL);
                            if(n!=0&&poison_card_tmp.index==0)
                            {
                                poison_card_tmp.index=cards[0].index;
                                continue;
                            } 
                            game_data_search_cards ( cards, &n, PLAYER_ORIGINAL, CARD_SPACE_DECK_POISON, CARD_POISON_L2, CARD_COST_ORIGINAL);
                            if((n!=0&&poison_card_tmp.index==0)||(n!=0&&poison_card_tmp.type==CARD_POISON_L1))
                            {     
                                poison_card_tmp.index=cards[0].index;    
                                continue;
                            }  
                            game_data_search_cards ( cards, &n, PLAYER_ORIGINAL, CARD_SPACE_DECK_POISON, CARD_POISON_L3, CARD_COST_ORIGINAL);
                            if((n!=0&&poison_card_tmp.index==0)||(n!=0&&poison_card_tmp.type==CARD_POISON_L1)||(n!=0&&poison_card_tmp.type==CARD_POISON_L2))
                            {
                                poison_card_tmp.index=cards[0].index;
                                continue;
                            } 
                        }
                        
                    card[Snow_White_CARD_IDX_POISON]=poison_card_tmp.index;
                   
                    if(poison_card_tmp.index>0)card_defense[i]=poison_card_tmp.index;
                }
                //printf("card_tmp=%d\n",card_idx_tmp[i]);
                if(skill_snow_white (card, 0,player_use, player_des)<0)continue;
                card_idx_tmp[i]=card_idx[i];
                card_skill[i]=card_idx[k];
                status.poison+=card_attach_calculate(card_skill[i],ACTION_DEFENSE);

                
                break;
                
                   
            }
            break;
            }
            
            case CARD_SKILL_FINISH1:
            case CARD_SKILL_FINISH2:
            case CARD_SKILL_FINISH3:
            {
            int32_t distance=abs(player_data_des.pos-player_data_use.pos);
            if(distance<=1)
            {
                card[0]=card_idx[i];
                skill_snow_white (card, 0,  player_use,  player_des);
            }
            else  card_idx_tmp[i]=-1;
            break;
            }
            case CARD_BASIC_ATTACK_L1:
            case CARD_BASIC_ATTACK_L2:
            case CARD_BASIC_ATTACK_L3:
            {
                int32_t delta=card_data_get_level(card_data[i].type);
                
                int32_t num=0;
                
                if(action_attack ( delta, 1, player_use,  player_des)>0&&delta>=2&&game_data_search_cards ( cards, &num,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)snow_white_poison(player_des,1);
                card_data[i].space=CARD_SPACE_USE;
                //printf("%d\n",card_data[i].space);
                 card_idx_tmp[i]=card_idx[i];
                 sPlayerData player_date_use_tmp;
                player_data_get(&player_date_use_tmp,player_use);
                player_date_use_tmp.power+=delta;
                player_data_set(player_use,player_date_use_tmp);
                break;
            }
            case CARD_BASIC_DEFENSE_L1:
            case CARD_BASIC_DEFENSE_L2:
            case CARD_BASIC_DEFENSE_L3:
            case CARD_BASIC_COMMON: 
            {
                int32_t delta=card_data_get_level(card_data[i].type);
                action_defense ( delta,  player_use);
                card_data[i].space=CARD_SPACE_USE;
                 card_idx_tmp[i]=card_idx[i];
                 sPlayerData player_date_use_tmp;
                player_data_get(&player_date_use_tmp,player_use);
                player_date_use_tmp.power+=delta;
                player_data_set(player_use,player_date_use_tmp);
                break;
            }
            case CARD_BASIC_MOVEMENT_L1:
            case CARD_BASIC_MOVEMENT_L2:
            case CARD_BASIC_MOVEMENT_L3:

            {
                int32_t delta=card_data_get_level(card_data[i].type);
                
                if(action_move ( delta,  1, player_use)<0)action_move(delta,  1, player_use);
                card_data[i].space=CARD_SPACE_USE;
                card_idx_tmp[i]=card_idx[i];
                sPlayerData player_date_use_tmp;
                player_data_get(&player_date_use_tmp,player_use);
                player_date_use_tmp.power+=delta;
                player_data_set(player_use,player_date_use_tmp);
                break;
            }
            

            
        }
              
        }
        //開始比較type
            sPlayerData player_data_usecopy;
            player_data_get (&player_data_usecopy, player_use);
            sPlayerData player_data_descopy;
            player_data_get (&player_data_descopy, player_des);
            
            
            
            status.damage = abs(player_data_des.hp-player_data_descopy.hp);
            status.distance = abs(player_data_descopy.pos-player_data_usecopy.pos);
            status.shell = player_data_usecopy.defense;
            status.power = player_data_usecopy.power;
            
            //   printf("%d,%d,%d,%d,%d,%d\n",card_idx_tmp[0],card_idx_tmp[1],card_idx_tmp[2],card_idx_tmp[3],card_idx_tmp[4],card_idx_tmp[5]);
            //   printf("poison=%d,damage=%d,distance=%d,shell=%d,power=%d\n",status.poison,status.damage,status.distance,status.shell,status.power);
            //   printf("poison=%d,best_damage=%d,distance=%d,shell=%d,power=%d\n",snow_white_best_status.poison,snow_white_best_status.damage,snow_white_best_status.distance,snow_white_best_status.shell,snow_white_best_status.power);
            if(status.distance>=4||status.distance>snow_white_best_status.distance)
            {
                if(snow_white_best_status.poison==0)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                else if(snow_white_best_status.poison>=status.poison)
                {
                    if(snow_white_best_status.poison>status.poison)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                    else if(status.power>=snow_white_best_status.power)
                    {
                        if(status.power>snow_white_best_status.power)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                        else if(status.damage>=snow_white_best_status.damage)
                        {
                            if(status.shell>=snow_white_best_status.shell)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                            else if(status.damage>snow_white_best_status.damage)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                        }
                        
                    }
                     
                }
            }
            else if(snow_white_best_status.poison<status.poison&&snow_white_best_status.distance<4)
            {
                
                if(snow_white_best_status.poison<status.poison)
                {
                   
                    snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);

                }
                else if(status.power>=snow_white_best_status.power)
                {
                    if(status.power>snow_white_best_status.power)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                    else if(status.damage>=snow_white_best_status.damage)
                    {
                        
                        if(status.damage>snow_white_best_status.damage)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                        else if(status.shell>=snow_white_best_status.shell)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                        
                    }
                }
               
            }
            else if(status.power>snow_white_best_status.power&&snow_white_best_status.poison==status.poison)
            {
                if(status.power>snow_white_best_status.power)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                else if(status.damage>=snow_white_best_status.damage)
                {
                    if(status.damage>snow_white_best_status.damage)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                    else if(status.shell>=snow_white_best_status.shell)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                        
                }
            }
            else if(status.damage>snow_white_best_status.damage&&snow_white_best_status.poison==status.poison)
            {
                if(status.damage>snow_white_best_status.damage)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                else if(status.shell>=snow_white_best_status.shell)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill);
                        
            }
            else if(status.shell>=snow_white_best_status.shell&&snow_white_best_status.distance<=4&&snow_white_best_status.power==0&&snow_white_best_status.poison==0&&snow_white_best_status.damage==0)snow_white_best_data_cpy (&snow_white_best_status, &status,len,best_card,card_idx_tmp,best_card_defense,card_defense,best_card_skill,card_skill); 
            player_data_set(player_use,player_data_use);
            player_data_set(player_des,player_data_des);
            
            for(int32_t i=0;i<len;i++)
            {
                
                card_data_set(card_data[i].index,1,CARD_SPACE_HAND , card_data[i].type, card_data[i].player);
            }
            for(int32_t i=0;i<poison_num;i++)
            {
                sCardData poison_data_idx;
                card_data_get(&poison_data_idx, poison_idx[i]);
                card_data_set(poison_data_idx.index,1,CARD_SPACE_DECK_POISON , poison_data_idx.type, player_use);
            }
            free(card_defense);
            
            free(card_skill);
            free(card_idx_tmp);
            free(card_data);
        return 0;
}

int32_t snow_white_robot(int *arr, int32_t n, int *best_card,int *best_card_skill,int *best_card_defense,int32_t player_use,int32_t player_des){
    int c[n]; // 控制陣列（Heap's algorithm 的輔助用）
    for (int i = 0; i < n; i++) c[i] = 0;

    
    if(snow_white_process(arr, n,best_card,best_card_skill,best_card_defense, player_use, player_des)==-1)return -1; // 初始排列
    //printf("%d,%d,%d,%d,%d,%d\n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            // 偶數位置用 arr[0] 交換，奇數用 arr[c[i]]
            if (i % 2 == 0) {
                int tmp = arr[0];
                arr[0] = arr[i];
                arr[i] = tmp;
            } else {
                int tmp = arr[c[i]];
                arr[c[i]] = arr[i];
                arr[i] = tmp;
            }

            if(snow_white_process(arr, n,best_card,best_card_skill,best_card_defense, player_use, player_des)==-1)return -1;  // 每次新排列都處理一次

            c[i] += 1;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    
    return 0;
}

int32_t snow_white_best_data_cpy (sSnow_White_Robot *snow_white_best_status, sSnow_White_Robot *status,int32_t len,int32_t *best_card,int32_t *card,int32_t *best_card_defense,int32_t*card_defense,int32_t *best_card_skill,int32_t*card_skill)
{
        snow_white_best_status->poison=status->poison;
        snow_white_best_status->damage=status->damage;
        snow_white_best_status->shell=status->shell;
        snow_white_best_status->distance=status->distance;
        snow_white_best_status->power=status->power;
    
    for(int32_t i=0; i<len ; i++)
    {
        best_card[i]=card[i];
        best_card_defense[i]=card_defense[i];
        best_card_skill[i]=card_skill[i];
        //printf("%d,%d,%d,%d,%d\n",best_card[i],best_card_attack[i],best_card_skill[i],best_card_movement[i],best_card_keep[i]);
    }

    return 0;
}


int32_t snow_white_buy_card(int32_t player)
{
    sPlayerData play_data;
    sCardData cards[CARD_NUM];
    int32_t n=0;
    player_data_get(&play_data,player);
    if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_ATTACK_BASE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_ATTACK_L1,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_DEFENSE_BASE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_DEFENSE_L1,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_DEFENSE_BASE_L3,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_DEFENSE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_MOVEMENT_BASE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_MOVEMENT_L1,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_ATTACK_BASE_L3,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_ATTACK_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_MOVEMENT_BASE_L3,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_DEFENSE_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_ATTACK_L3,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_DEFENSE_L3,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_DEFENSE_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_ATTACK_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_DEFENSE_L1,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_MOVEMENT_L1,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_ATTACK_L1,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_MOVEMENT_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_MOVEMENT_L3,  player)>=0);
    else game_action_buy_card (CARD_BASIC_DEFENSE_L1,  player);
    
    return 0;
}
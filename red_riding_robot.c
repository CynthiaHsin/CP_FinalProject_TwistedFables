#include"main.h"
#include"red_riding_robot.h"
#include"game_data_player.h"
#include"game_data_card.h"
#include"game_action_skill_red_riding_hood.h"
#include"game_data.h"
#include"game_action.h"
#include<stdint.h>
sRed_Riding_Robot best_status;

int32_t process(int *card_idx, int end,int *best_card,int *best_card_skill,int *best_card_attack,int *best_card_movement,int32_t player_use,int32_t player_des) {
    if(card_idx==NULL)return -1;
    int32_t len=end;
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    int32_t *card_skill;
    int32_t *card_attack;
    int32_t *card_movement;
    player_data_get(&player_data_use, player_use);
    player_data_get(&player_data_des, player_des);

    // best_card=(int32_t *)malloc(len*sizeof(int32_t));
    // best_card_attack=(int32_t *)malloc(len*sizeof(int32_t));
    // best_card_movement=(int32_t *)malloc(len*sizeof(int32_t));
    // best_card_skill=(int32_t *)malloc(len*sizeof(int32_t));
    card_attack=(int32_t *)malloc(len*sizeof(int32_t));
    card_movement=(int32_t *)malloc(len*sizeof(int32_t));
    card_skill=(int32_t *)malloc(len*sizeof(int32_t));

        sCardData *card_data;
        card_data=malloc(len*sizeof(sCardData));
        for(int32_t i=0; i<end; i++)
        {
        card_data_get(&card_data[i], card_idx[i]);
        //printf("%d,",card_idx[i]);
        }
        //printf("\n");
        // 每個可能的組合跑一遍
        for (int i = 0; i <= len; i++) 
        {
            int card[5];
            for(int32_t k=0;k<5;k++)card[k]=0;
            sCardData cards[1];
            int n=0;
            switch(card_data[i].type)
            {
            case CARD_SKILL_ATTACK_BASE_L1:
            case CARD_SKILL_ATTACK_BASE_L2:
            case CARD_SKILL_ATTACK_BASE_L3:
            case CARD_SKILL_MOVEMENT_BASE_L1:
            case CARD_SKILL_MOVEMENT_BASE_L2:
            case CARD_SKILL_MOVEMENT_BASE_L3:
            {
            for(int32_t k=i;k<end;k++)
            {
                card[0]=card_idx[i];
                card[4]=card_idx[k];
                if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&skill_red_riding_hood (card, player_use, player_des)>=0)
                {
                    card_skill[i]=card_idx[k];
                    break;
                }
                else if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)
                {
                    for(int32_t j=i;j<end;j++)
                    {
                        card[0]=card_idx[i];
                        card[4]=card_idx[k];
                        card[1]=card_idx[j];
                        if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&skill_red_riding_hood (card, player_use, player_des)>=0)
                        {
                            card_skill[i]=card_idx[k];
                            card_attack[i]=card_idx[j];
                            break;
                        }
                        else if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)
                        {
                            for(int32_t w=j;w<end;w++)
                            {
                                card[0]=card_idx[i];
                                card[4]=card_idx[k];
                                card[1]=card_idx[j];
                                card[2]=card_idx[w];
                                skill_red_riding_hood (card, player_use, player_des);
                                card_skill[i]=card_idx[k];
                                card_attack[i]=card_idx[j];
                                card_movement[i]=card_idx[w];
                                break;
                            }
                        }
                    }
                }
            }
            }
            break;
            case CARD_SKILL_DEFENSE_BASE_L1:
            case CARD_SKILL_DEFENSE_BASE_L2:
            case CARD_SKILL_DEFENSE_BASE_L3:
            {
            for(int32_t k=i;k<end;k++)
            {
                card[0]=card_idx[i];
                card[4]=card_idx[k];
                if(skill_red_riding_hood (card, player_use, player_des)>=0)
                {
                    card_skill[i]=card_idx[k];
                    break;  
                }
            }
            break;
            }
            
            case CARD_SKILL_FINISH1:
            case CARD_SKILL_FINISH2:
            case CARD_SKILL_FINISH3:
            {
            int32_t finish1_skill_type[2]={0};
            int32_t finish2_card_idx[6]={0};
            skill_red_riding_hood_finish (card_idx[i],  finish1_skill_type,  finish2_card_idx, 3,  player_use,  player_des);
            break;
            }
            case CARD_BASIC_ATTACK_L1:
            case CARD_BASIC_ATTACK_L2:
            case CARD_BASIC_ATTACK_L3:
            {
                int32_t delta=card_data_get_level(card_data[i].type);
                action_attack ( delta, 1, player_use,  player_des);
                break;
            }
            case CARD_BASIC_DEFENSE_L1:
            case CARD_BASIC_DEFENSE_L2:
            case CARD_BASIC_DEFENSE_L3:
            {
                int32_t delta=card_data_get_level(card_data[i].type);
                action_defense ( delta,  player_use);
                break;
            }
            case CARD_BASIC_MOVEMENT_L1:
            case CARD_BASIC_MOVEMENT_L2:
            case CARD_BASIC_MOVEMENT_L3: 
            {
                int32_t delta=card_data_get_level(card_data[i].type);
                action_move ( delta,  1, player_use);
            }
            }
            if(card_data[i].space==CARD_SPACE_HAND)
            {
                card[0]=CARD_SKILL_ATTACK_EVOLUTION_L2;
                card[3]=card[i];
                skill_red_riding_hood (card, player_use, player_des);
            }//開始比較
            sPlayerData player_data_usecopy;
            player_data_get (&player_data_usecopy, player_use);
            sPlayerData player_data_descopy;
            player_data_get (&player_data_descopy, player_des);
            sRed_Riding_Robot status;
            status.damage = abs(player_data_des.hp-player_data_descopy.hp);
            status.distance = abs(player_data_usecopy.pos-player_data_use.pos);
            status.shell = player_data_usecopy.defense;
            status.power = player_data_usecopy.power;
            //printf("damage=%d,distance=%d,shell=%d,power=%d\n",status.damage,status.distance,status.shell,status.power);
            if(status.distance>=3)
            {
                if(best_status.damage>=status.damage)
                {
                     if(status.power>=best_status.power)
                     {
                        if(status.shell>=best_status.shell)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                        else if(status.power>best_status.power)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                     }
                     else if(best_status.damage>status.damage)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                }
            }
            else if(status.damage>=best_status.damage&&best_status.distance<3)
            {
                if(status.power>=best_status.power)
                {
                    if(status.shell>=best_status.shell) red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                    else if(status.power>best_status.power)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                }
                else if(best_status.damage>status.damage)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
            }
            else if(status.power>=best_status.power&&best_status.distance<3&&best_status.damage==0)
            {
                if(status.shell>=best_status.shell)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                else if(status.power>best_status.power)red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
            }
            else if(status.shell>=best_status.shell&&best_status.distance<3&&best_status.damage==0&&best_status.power==0)
            {
               red_riding_best_data_cpy (&best_status, status,len,best_card,card_idx,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement);
                
            }
            player_data_set(player_use,player_data_use);
            player_data_set(player_des,player_data_des);
            for(int32_t k=0;k<len;k++)
            {
                card_data_set(card_data[0].index,1,CARD_SPACE_HAND , card_data[0].type, card_data[0].player);
            }
        }
}

void generate_permutations(int *arr, int32_t n, int *best_card,int *best_card_skill,int *best_card_attack,int *best_card_movement,int32_t player_use,int32_t player_des) {
    int c[n]; // 控制陣列（Heap's algorithm 的輔助用）
    for (int i = 0; i < n; i++) c[i] = 0;

    process(arr, n,best_card,best_card_skill,best_card_attack,best_card_movement, player_use, player_des); // 初始排列
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

            process(arr, n,best_card,best_card_skill,best_card_attack,best_card_movement, player_use, player_des);  // 每次新排列都處理一次

            c[i] += 1;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
}

int32_t red_riding_best_data_cpy (sRed_Riding_Robot *pStatusData, sRed_Riding_Robot src,int32_t len,int32_t *best_card,int32_t *card,int32_t *best_card_attack,int32_t*card_attack,int32_t *best_card_skill,int32_t*card_skill,int32_t *best_card_movement,int32_t*card_movement){
    int8_t *pA= (int8_t*)pStatusData;
    int8_t *pB= (int8_t*)(&src);
    for (int32_t i=0; i<sizeof(sRed_Riding_Robot); i++){
        pA[i]= pB[i];
    }
    
    for(int32_t i=0; i<len ; i++)
    {
        best_card[i]=card[i];
        best_card_attack[i]=card_attack[i];
        best_card_skill[i]=card_skill[i];
        best_card_movement[i]=card_movement[i];
    }

    return 0;
}


int32_t red_riding_buy_card(int32_t player)
{
    sPlayerData play_data;
    sCardData cards[1];
    int32_t n=0;
    player_data_get(&play_data,player);
    if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_ATTACK_BASE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_ATTACK_L1,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_MOVEMENT_BASE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_MOVEMENT_L1,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_MOVEMENT_BASE_L3,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_MOVEMENT_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_ATTACK_BASE_L3,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_ATTACK_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_DEFENSE_BASE_L2,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L1, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_DEFENSE_L1,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_SKILL_DEFENSE_BASE_L3,  player)>=0);
    else if(game_data_search_cards ( cards, &n,  player, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )<=0&&game_action_buy_card (CARD_BASIC_DEFENSE_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_ATTACK_L3,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_ATTACK_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_MOVEMENT_L3,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_MOVEMENT_L2,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_DEFENSE_L3,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_ATTACK_L1,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_MOVEMENT_L1,  player)>=0);
    else if(game_action_buy_card (CARD_BASIC_DEFENSE_L2,  player)>=0);
    else game_action_buy_card (CARD_BASIC_DEFENSE_L1,  player);
}
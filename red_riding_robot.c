#include"main.h"
#include"red_riding_robot.h"
#include"game_action_skill_red_riding_hood.h"
#include"game_data.h"
#include"game_action.h"
#include<stdint.h>
sRed_Riding_Robot red_riding_hood_best_status;

int32_t red_riding_robot_process(int *card_idx, int end,int *best_card,int *best_card_skill,int *best_card_attack,int *best_card_movement,int *best_card_keep, int32_t player_use,int32_t player_des) {
    if(card_idx==NULL)return -1;
    int32_t len=end;
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    int32_t *card_skill;
    int32_t *card_attack;
    int32_t *card_movement;
    int32_t *card_keep;
    int32_t *card_idx_tmp;
    player_data_get(&player_data_use, player_use);
    player_data_get(&player_data_des, player_des);

    
    card_attack=(int32_t *)malloc(len*sizeof(int32_t));
    card_movement=(int32_t *)malloc(len*sizeof(int32_t));
    card_skill=(int32_t *)malloc(len*sizeof(int32_t));
    card_keep=(int32_t *)malloc(len*sizeof(int32_t));
    card_idx_tmp=(int32_t *)malloc(len*sizeof(int32_t));
    for(int32_t i=0;i<end;i++)
    {
        card_attack[i]=-1;
        card_movement[i]=-1;
        card_skill[i]=-1;
        card_keep[i]=-1;
        card_idx_tmp[i]=-1;
    }

        sCardData *card_data;
        card_data=malloc(len*sizeof(sCardData));
        for(int32_t i=0; i<end; i++)
        {
        card_data_get(&card_data[i], card_idx[i]);
        //printf("gg:%d,",card_idx[i]);
        }
        //printf("\n");
        // 每個可能的組合跑一遍
        for (int i = 0; i < len; i++) 
        {
            int card[RED_RIDING_HOOD_CARD_IDX_NUM];
            for(int32_t i=0;i<RED_RIDING_HOOD_CARD_IDX_NUM;i++)card[i]=-1;
            sCardData cards[1];
            int n=0;
            for(int k=0;k<len;k++)
            {
                if((card_skill[k]==card_idx[i])||(card_attack[k]==card_idx[i])||(card_movement[k]==card_idx[i]))n=1;
            }
            if(n==1)continue;
            switch(card_data[i].type)
            {
            case CARD_SKILL_ATTACK_BASE_L1:
            case CARD_SKILL_ATTACK_BASE_L2:
            case CARD_SKILL_ATTACK_BASE_L3:
            case CARD_SKILL_MOVEMENT_BASE_L1:
            case CARD_SKILL_MOVEMENT_BASE_L2:
            case CARD_SKILL_MOVEMENT_BASE_L3:
            {

            for(int32_t k=i+1;k<end;k++)
            {
                card[0]=card_idx[i];
                card[4]=card_idx[k];
                //game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL );
                
                if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )==0)
                {
                    if(card_attach_calculate(card_idx[k], ACTION_ATTACK)<0)continue;
                    if(skill_red_riding_hood (card, player_use, player_des)<0)continue;
                    card_skill[i]=card_idx[k];
                    card_idx_tmp[i]=card_idx[i];
                    break;
                }
                else if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)
                {
                    
                    for(int32_t j=i+1;j<end;j++)
                    {   if(j==k)j++;
                        card[0]=card_idx[i];
                        card[4]=card_idx[k];
                        card[RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION]=card_idx[j];
                        if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )==0)
                        {
                            if(card_attach_calculate(card_idx[k], ACTION_ATTACK)<0)continue;
                            if(skill_red_riding_hood (card, player_use, player_des)<0)continue;
                            card_skill[i]=card_idx[k];
                            card_attack[i]=card_idx[j];
                            card_idx_tmp[i]=card_idx[i];
                            break;
                        }
                        else if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L1, CARD_COST_ORIGINAL )>0)
                        {
                           
                            for(int32_t w=i+1;w<end;w++)
                            {
                                if(w==k||w==j)w++;
                                card[0]=card_idx[i];
                                card[4]=card_idx[k];
                                card[1]=card_idx[j];
                                card[2]=card_idx[w];
                                if(card_attach_calculate(card_idx[k], ACTION_ATTACK)<0)continue;
                                if(skill_red_riding_hood (card, player_use, player_des)<0)continue;
                                card_skill[i]=card_idx[k];
                                card_attack[i]=card_idx[j];
                                card_movement[i]=card_idx[w];
                                card_idx_tmp[i]=card_idx[i];
                                break;
                            }
                        }
                    }
                }
                //printf("aaaaa\n");
                //printf("card_idx=%d,%d,%d,%d,%d\n",card[0],card[1],card[2],card[3],card[4]);
            }
            }
            break;
            case CARD_SKILL_DEFENSE_BASE_L1:
            case CARD_SKILL_DEFENSE_BASE_L2:
            case CARD_SKILL_DEFENSE_BASE_L3:
            {
                
            for(int32_t k=i+1;k<end;k++)
            {
                card[0]=card_idx[i];
                card[4]=card_idx[k];
                if(card_attach_calculate(card_idx[k], ACTION_DEFENSE)<0)continue;
                skill_red_riding_hood (card, player_use, player_des);
                card_skill[i]=card_idx[k];
                card_idx_tmp[i]=card_idx[i];
                       
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
            case CARD_BASIC_COMMON:
            {
                
                int32_t delta=card_data_get_level(card_data[i].type);
                action_attack ( delta, 1, player_use,  player_des);
                card_data[i].space=CARD_SPACE_USE;
                card_idx_tmp[i]=card_idx[i];
                sPlayerData player_date_use_tmp;
                player_data_get(&player_date_use_tmp,player_use);
                player_date_use_tmp.power+=delta;
                player_data_set(player_use,player_date_use_tmp);
                //printf("%d\n",card_data[i].space);
                break;
            }
            case CARD_BASIC_DEFENSE_L1:
            case CARD_BASIC_DEFENSE_L2:
            case CARD_BASIC_DEFENSE_L3:
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
                action_move ( delta,  1, player_use);
                card_data[i].space=CARD_SPACE_USE;
                card_idx_tmp[i]=card_idx[i];
                sPlayerData player_date_use_tmp;
                player_data_get(&player_date_use_tmp,player_use);
                player_date_use_tmp.power+=delta;
                player_data_set(player_use,player_date_use_tmp);
                
                break;
            }
            
        }
         
        if(card_data[i].space==CARD_SPACE_HAND) 
        { 
    
            int32_t n=0,num=0;
            sCardData cards[1];
            if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_ATTACK_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)num+=1;
            if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_DEFENSE_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)num+=1;
            if(game_data_search_cards ( cards, &n,  player_use, CARD_SPACE_USE_LASTING, CARD_SKILL_MOVEMENT_EVOLUTION_L2, CARD_COST_ORIGINAL )>0)num+=1;
            //printf("%d,%d\n",card_data[i].index,CARD_SPACE_USE);
            if(num>=1)
            {
                card[0]=CARD_SKILL_ATTACK_EVOLUTION_L2;
                card[3]=card_idx[i];
                card_keep[i]=card_idx[i];
                card[i]=CARD_SKILL_ATTACK_EVOLUTION_L2;
                skill_red_riding_hood (card, player_use, player_des);
            }
        }
             
        }
        //開始比較
            sPlayerData player_data_usecopy;
            player_data_get (&player_data_usecopy, player_use);
            sPlayerData player_data_descopy;
            player_data_get (&player_data_descopy, player_des);
            sRed_Riding_Robot status;
            status.damage = abs(player_data_des.hp-player_data_descopy.hp);
            status.distance = abs(player_data_usecopy.pos-player_data_use.pos);
            status.shell = player_data_usecopy.defense;
            status.power = player_data_usecopy.power;
             printf("%d,%d,%d,%d,%d,%d\n",card_idx[0],card_idx[1],card_idx[2],card_idx[3],card_idx[4],card_idx[5]);
             //printf("damage=%d,distance=%d,shell=%d,power=%d\n",status.damage,status.distance,status.shell,status.power);
            // printf("best_damage=%d,distance=%d,shell=%d,power=%d\n",red_riding_hood_best_status.damage,red_riding_hood_best_status.distance,red_riding_hood_best_status.shell,red_riding_hood_best_status.power);
            if(status.distance>=3)
            {
                if(red_riding_hood_best_status.damage==0)
                if(red_riding_hood_best_status.damage>status.damage)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                {
                    if(red_riding_hood_best_status.damage>status.damage)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                    else if(status.power>=red_riding_hood_best_status.power)
                     {
                        if(status.power>red_riding_hood_best_status.power)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                        else if(status.shell>=red_riding_hood_best_status.shell)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                     }
                     
                }
            }
            else if(red_riding_hood_best_status.damage>status.damage&&red_riding_hood_best_status.distance<3)
            {
                if(red_riding_hood_best_status.damage>status.damage)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                else if(status.power>=red_riding_hood_best_status.power)
                {
                    if(status.power>red_riding_hood_best_status.power)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                    else if(status.shell>=red_riding_hood_best_status.shell)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                }
                     
            }
            else if(status.power>red_riding_hood_best_status.power&&status.damage==red_riding_hood_best_status.damage)
            {
                if(status.power>red_riding_hood_best_status.power)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                else if(status.shell>=red_riding_hood_best_status.shell)red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
            }
            else if(status.shell>=red_riding_hood_best_status.shell&&red_riding_hood_best_status.distance<3&&red_riding_hood_best_status.damage==0&&red_riding_hood_best_status.power==0)
            {
               red_riding_best_data_cpy (&red_riding_hood_best_status, &status,len,best_card,card_idx_tmp,best_card_attack,card_attack,best_card_skill,card_skill,best_card_movement,card_movement,best_card_keep,card_keep);
                
            }
            player_data_set(player_use,player_data_use);
            player_data_set(player_des,player_data_des);
            for(int32_t i=0;i<len;i++)
            {
                card_data_set(card_data[i].index,1,CARD_SPACE_HAND , card_data[i].type, card_data[i].player);
            }
            free(card_attack);
            free(card_movement);
            free(card_skill);
            free(card_keep);
            free(card_data);
        return 0;
}

int32_t red_riding_robot(int *arr, int32_t n, int *best_card,int *best_card_skill,int *best_card_attack,int *best_card_movement,int *best_card_keep,int32_t player_use,int32_t player_des) {
    int c[n]; // 控制陣列（Heap's algorithm 的輔助用）
    for (int i = 0; i < n; i++) c[i] = 0;

    
    if(red_riding_robot_process(arr, n,best_card,best_card_skill,best_card_attack,best_card_movement,best_card_keep, player_use, player_des)==-1)return -1; // 初始排列
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

            if(red_riding_robot_process(arr, n,best_card,best_card_skill,best_card_attack,best_card_movement,best_card_keep, player_use, player_des)==-1)return -1;  // 每次新排列都處理一次

            c[i] += 1;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    
    return 0;
}

int32_t red_riding_best_data_cpy (sRed_Riding_Robot *red_riding_hood_best_status, sRed_Riding_Robot *status,int32_t len,int32_t *best_card,int32_t *card,int32_t *best_card_attack,int32_t*card_attack,int32_t *best_card_skill,int32_t*card_skill,int32_t *best_card_movement,int32_t*card_movement,int32_t *best_card_keep,int32_t*card_keep)
{

        red_riding_hood_best_status->damage=status->damage;
        red_riding_hood_best_status->shell=status->shell;
        red_riding_hood_best_status->distance=status->distance;
        red_riding_hood_best_status->power=status->power;
    
    for(int32_t i=0; i<len ; i++)
    {
        best_card[i]=card[i];
        best_card_attack[i]=card_attack[i];
        best_card_skill[i]=card_skill[i];
        best_card_movement[i]=card_movement[i];
        best_card_keep[i]=card_keep[i];

        //printf("%d,%d,%d,%d,%d\n",best_card[i],best_card_attack[i],best_card_skill[i],best_card_movement[i],best_card_keep[i]);
    }

    return 0;
}


int32_t red_riding_buy_card(int32_t player)
{
    sPlayerData play_data;
    sCardData cards[CARD_NUM];
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
    
    return 0;
}
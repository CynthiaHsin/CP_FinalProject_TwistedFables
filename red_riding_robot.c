#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sRed_Riding_Robot best_status;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//card_idx是手牌，card_use是弄好的回傳，start=0，end=card_num
int32_t permute(int *card_idx, int32_t *card_use,int32_t start,int32_t end,int32_t player_use,int32_t player_des) {
    if(card_idx==NULL)return -1;
    int32_t len = sizeof(card_idx) / sizeof(card_idx[0]);
    sPlayerData player_data_use;
    sPlayerData player_data_des;
    int32_t *best_card;
    best_card=(int32_t *)malloc(len*sizeof(int32_t));
    if(start==0&&end==len)//先儲存初始的數值，好在後面跑完能恢復
    {
        player_data_get(&player_data_use, player_use);
        player_data_get(&player_data_des, player_des);
    }
    if (start == end) {
        sCardData card_data[6];

        for(int32_t i=0; i<end; i++)
        {
        card_data_get(&card_data[i], card_idx[i]);
        }
        // 每個可能的組合跑一遍
        for (int i = 0; i <= len; i++) 
        {
            int card[5];
            switch(card_data[i].type)
            {
            case CARD_SKILL_ATTACK_BASE_L1:
            case CARD_SKILL_ATTACK_BASE_L2:
            case CARD_SKILL_ATTACK_BASE_L3:
            for(int32_t k=i;k<end;i++)
            {
                card[0]=card_idx[i];
                card[4]=card_idx[k];
                if(skill_red_riding_hood (card, player_use, player_des)>=0)break;
                for(int32_t j=k;j<end;j++)
                {
                    card[0]=CARD_SKILL_ATTACK_EVOLUTION_L1;
                    card[1]=card_idx[j];
                    if(skill_red_riding_hood (card, player_use, player_des)>=0)break;
                }
            }
            break;
            case CARD_SKILL_DEFENSE_BASE_L1:
            case CARD_SKILL_DEFENSE_BASE_L2:
            case CARD_SKILL_DEFENSE_BASE_L3:
            case CARD_SKILL_MOVEMENT_BASE_L1:
            case CARD_SKILL_MOVEMENT_BASE_L2:
            case CARD_SKILL_MOVEMENT_BASE_L3:
            for(int32_t k=i;k<end;i++)
            {
                card[0]=card_idx[i];
                card[4]=card_idx[k];
                if(skill_red_riding_hood (card, player_use, player_des)>=0)break;
            }
            break;
            case CARD_SKILL_ATTACK_EVOLUTION_L1:
            card[0]=card_idx[i];
            skill_red_riding_hood (card, player_use, player_des);
            break;
            case CARD_SKILL_DEFENSE_EVOLUTION_L1:
            card[0]=card_idx[i];
            skill_red_riding_hood (card, player_use, player_des);
            break;
            case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
            card[0]=card_idx[i];
            skill_red_riding_hood (card, player_use, player_des);
            break;
            case CARD_SKILL_ATTACK_EVOLUTION_L2:
            case CARD_SKILL_DEFENSE_EVOLUTION_L2:
            case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
            card[0]=card_idx[i];
            skill_red_riding_hood (card, player_use, player_des);
            case CARD_SKILL_FINISH1:
            case CARD_SKILL_FINISH2:
            case CARD_SKILL_FINISH3:
            skill_red_riding_hood_finish (card_idx[i], int32_t finish1_skill_type[2], int32_t finish2_card_idx[RED_RIDING_HOOD_CARD_IDX_NUM], 3,  player_use,  player_des);
            break;
            }
            if(card_data[i].space==CARD_SPACE_HAND)
            {
                card[0]=CARD_SKILL_ATTACK_EVOLUTION_L2;
                card[3]=card[i];
                skill_red_riding_hood (card, player_use, player_des);
            }//開始比較
            sPlayerData player_data_usecopy;
            player_data_get (sPlayerData *player_data_usecopy, player_use);
            sPlayerData player_data_descopy;
            player_data_get (sPlayerData *player_data_descopy, player_des);
            sRed_Riding_Robot status;
            status.damage = player_data_descopy.hp-player_data_des.des;
            status.distance = abs(player_data_usecopy-player_data_use);
            status.shell = player_data_usecopy.defense;
            status.power = player_data_usecopy.power;
            if(status.distance>=3)
            {
                if(best_status.damage>=status.damage)
                {
                     if(status.power>=best_status.power)
                     {
                        if(status.shell>=best_status.shell)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                        else if(status.power>best_status.power)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                     }
                     else if(best_status.damage>status.damage)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                }
            }
            else if(status.damage>=best_status.damage&&best_status.distance<3)
            {
                if(status.power>=best_status.power)
                {
                    if(status.shell>=best_status.shell)red_riding_status_data_cpy red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                    else if(status.power>best_status.power)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                }
                else if(best_status.damage>status.damage)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
            }
            else if(status.power>=best_status.power&&best_status.distance<3&&best_status.damage=0)
            {
                if(status.shell>=best_status.shell)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                else if(status.power>best_status.power)red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
            }
            else if(status.shell>=best_status.shell&&best_status.distance<3&&best_status.damage=0&&best_status.power==0)
            {
                red_riding_best_data_cpy (&best_status, status,&best_card,&card_idx);
                
            }
            player_data_set(player_use,player_data_use);
            player_data_set(player_des,player_data_des);
        }
        //shopping還沒寫不知道在哪:)
    } 
    else {
        for (int i = start; i <= end; i++) {
            // Swap current index with the start
            swap(&card[start], &card[i]);
            // Recurse for the rest
            permute(arr, start + 1, end);
            // Backtrack
            swap(&card[start], &card[i]);
        }
    }
}

int32_t red_riding_best_data_cpy (sRed_Riding_Robot *pStatusData, sRed_Riding_Robot src,int32_t *best_cards,int32_t *cards){
    int8_t *pA= (int8_t*)pStatusData;
    int8_t *pB= (int8_t*)(&src);
    for (int32_t i=0; i<sizeof(sPlayerData); i++){
        pA[i]= pB[i];
    }
    int32_t len=sizeof(cards)/sizeof(cards[0]);
    for(int32_t i=0; i<len ; i++)
    {
        best_cards[i]=cards[i];
    }
    for()
    return 0;
}



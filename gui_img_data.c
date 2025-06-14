#include "gui_img_data.h"
#include "game_data.h"

int gui_imd_data_texture_get (SDL_Texture*** pTex, int card_type, int32_t player){
    sPlayerData player_data;
    player_data_get (&player_data, player);
    
    if (card_type<CARD_BASIC_ATTACK_L1){
        return -1;
    }else if (card_type <= CARD_BASIC_COMMON){
        *pTex = basic_card;
    }else if (card_type <= CARD_SKILL_FINISH3){
        switch (player_data.character){
            case CHARACTER_RED_RIDING_HOOD: *pTex = rrh_card;     break;
            case CHARACTER_SNOW_WHITE:      *pTex = sw_card;      break;
            case CHARACTER_DOROTHY:         *pTex = dorothy_card; break;
            case CHARACTER_KAGUYA:          *pTex = kaguya_card;  break;
            case CHARACTER_MATCH_GIRL:      *pTex = mg_card;      break;
            case CHARACTER_MULAN:           *pTex = mulan_card;   break;
            default: return -1;
        }
    }else if (card_type <= CARD_POISON_L3){
        *pTex = sw_card;
    }else if (card_type <= CARD_MATCH){
        *pTex = mg_card;
    }else return -1;
    return 0;
}
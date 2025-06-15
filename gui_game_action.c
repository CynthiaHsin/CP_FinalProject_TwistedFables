# include "main.h"
# include "game_data.h"
# include "game_action.h"
# include "gui_sdl_config.h"
# include "gui_img_data.h"
# include "gui_game_render.h"
# include "gui_game_choose.h"
# include "gui_game_action.h"

# define TEXT_CHOOSE_DES_PLAYER "Choose the destination player."
# define TEXT_CHOOSE_MOVE_DIRECTION "Choose the moving direction."
# define TEXT_CHOSE_TOKEN "Choose the number of token you want to use."

typedef enum _eSkillCardIdx{
    CARD_IDX_SKILL,
    CARD_IDX_ATTACH,
    CARD_IDX_NUM
} eSkillCardIdx;

extern SDL_Renderer *ren;
extern TTF_Font     *font_main;

int32_t gui_action_get_card (sCardData cards[], int32_t *pNum, int32_t player, int32_t space, int32_t type_min, int32_t type_max){
    int32_t card_num= 0;
    int32_t cnt= 0;
    for (int32_t i=type_min; i<=type_max; i++){
        game_data_search_cards (cards+card_num, &cnt, player, space, i, -1);
        card_num += cnt;
    }
    *pNum = card_num;
    return 0;
}

int32_t gui_action_get_basic_card (sCardData cards[], int32_t *pNum, int32_t player, int32_t space){
    return gui_action_get_card (cards, pNum, player, space, CARD_BASIC_ATTACK_L1, CARD_BASIC_COMMON);
}

int32_t gui_action_get_skill_card (sCardData cards[], int32_t *pNum, int32_t player, int32_t space){
    return gui_action_get_card (cards, pNum, player, space, CARD_SKILL_ATTACK_BASE_L1, CARD_SKILL_FINISH3);
}

int32_t gui_action_focus (int32_t player){
    int32_t action_allow[ACTION_NUM];
    game_action_actions_allow (action_allow, player);
    if (!action_allow[ACTION_FOCUS]) return -1;
    debug_print ("action_allow\n");
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    int32_t card_type= CARD_UNDEFINED;

    // 手牌丟一張
    game_data_search_cards (cards, &card_num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    int32_t card_delete_hand= gui_choose_card (&card_type, cards, card_num, "Choose the card you wand to delete.");
    
    // 棄牌丟一張
    game_data_search_cards (cards, &card_num, player, CARD_SPACE_THROW, CARD_ORIGINAL, -1);
    int32_t card_delete_throw= gui_choose_card (&card_type, cards, card_num, "Choose the card you wand to delete.");
    
    return game_action_focus (card_delete_hand, card_delete_throw, player);
}

int32_t gui_action_use_basic (int32_t player){
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;
    gui_action_get_basic_card (cards, &card_num, player, CARD_SPACE_HAND);

    int32_t card_type= CARD_UNDEFINED;
    int32_t move_direction= 0;
    int32_t player_des= PLAYER_UNDEFINED;
    int32_t token= 0;
    int32_t choose= gui_choose_card (&card_type, cards, card_num, "Choose the basic card you want to use.\n");
    
    if (choose < 0) return -1;

    switch (card_type){
        case CARD_BASIC_ATTACK_L1:
        case CARD_BASIC_ATTACK_L2:
        case CARD_BASIC_ATTACK_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            break;
        }    
        // case CARD_BASIC_DEFENSE_L1:
        // case CARD_BASIC_DEFENSE_L2:
        // case CARD_BASIC_DEFENSE_L3:
        case CARD_BASIC_MOVEMENT_L1:
        case CARD_BASIC_MOVEMENT_L2:
        case CARD_BASIC_MOVEMENT_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            move_direction= gui_choose_move_direction (TEXT_CHOOSE_MOVE_DIRECTION);
            break;
        }    
        default: break;
    }
    game_action_use_basic_card (choose, card_type, token, move_direction, player, player_des);
    return 0;
}

int32_t gui_action_use_skill (int32_t player){

    int32_t card_idx[CARD_IDX_NUM];
    int32_t type[CARD_IDX_NUM];
    sCardData cards[CARD_NUM];
    int32_t card_num= 0;

    gui_action_get_skill_card (cards, &card_num, player, CARD_SPACE_HAND);
    card_idx[CARD_IDX_SKILL]= gui_choose_card (&(type[CARD_IDX_SKILL]), cards, card_num, 
                                                "Choose the skill you want to use.\n");
    if (card_idx[CARD_IDX_SKILL] < 0) return -1;

    if (type[CARD_IDX_SKILL]<CARD_SKILL_FINISH1){
        gui_action_get_basic_card (cards, &card_num, player, CARD_SPACE_HAND);
        card_idx[CARD_IDX_ATTACH]= gui_choose_card (&type[CARD_IDX_ATTACH], cards, card_num, 
            "Choose the basic card you want to use as attach card.\n");
        if (card_idx[CARD_IDX_ATTACH] < 0) return -1;
    }else{
        card_idx[CARD_IDX_ATTACH]= -1;
        type[CARD_IDX_ATTACH]= CARD_UNDEFINED;
    }
    
    sPlayerData pd;
    player_data_get (&pd, player);
    switch (pd.character){
        case CHARACTER_RED_RIDING_HOOD:     return -1;
        case CHARACTER_MULAN:               return -1;
        case CHARACTER_KAGUYA:              return -1;
        case CHARACTER_DOROTHY:             return gui_skill_dorothy (player, card_idx, type);
        case CHARACTER_SNOW_WHITE:          return -1;
        case CHARACTER_MATCH_GIRL:          return -1;
        default: return -1;
    }
}

int32_t gui_skill_red_riding_hood (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        default: break;
    }
}

int32_t gui_skill_mulan (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        default: break;
    }
}

int32_t gui_skill_kaguya (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        default: break;
    }
}

int32_t gui_skill_dorothy (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    
    int32_t defense_throw_idx[3]= {0};
    int32_t defense_throw_num= 0;
    int32_t movement_evolution1_card_idx[CARD_NUM]= {0};
    int32_t movement_evolution1_card_num= 0;
    int32_t mevement_evolution1_des_direction= 0;
    int32_t player_des= player;

    sCardData cards[CARD_NUM];
    int32_t card_num;
    int32_t choose= -1;
    int32_t choose_type= CARD_ORIGINAL;

    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_DEFENSE_BASE_L3:{
            gui_action_get_basic_card (cards, &card_num, player, CARD_SPACE_HAND);
            choose= gui_choose_card(&choose_type, cards, card_num, "Choose a card you want to throw for the skill of defense.");
            if (choose<0) break;
            defense_throw_idx[defense_throw_num++]= choose;
            // no break (still can throw card)
        }
        case CARD_SKILL_DEFENSE_BASE_L2:{
            gui_action_get_basic_card (cards, &card_num, player, CARD_SPACE_HAND);
            choose= gui_choose_card(&choose_type, cards, card_num, "Choose a card you want to throw for the skill of defense.");
            if (choose<0) break;
            defense_throw_idx[defense_throw_num++]= choose;
            // no break (still can throw card)
        }
        case CARD_SKILL_DEFENSE_BASE_L1:{
            gui_action_get_basic_card (cards, &card_num, player, CARD_SPACE_HAND);
            choose= gui_choose_card(&choose_type, cards, card_num, "Choose a card you want to throw for the skill of defense.");
            if (choose<0) break;
            defense_throw_idx[defense_throw_num++]= choose;
            // no break (still need to choose des)
        }
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            break;
        }
        case CARD_SKILL_FINISH1:{
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            // no break (still need to choose token)
        }
        case CARD_SKILL_FINISH2:
        case CARD_SKILL_FINISH3:
        {
            sPlayerData pd;
            player_data_get (&pd, player);
            int32_t token= gui_choose_token (pd.token_max, player, TEXT_CHOSE_TOKEN);
            return skill_dorothy_finish (card_idx[CARD_IDX_SKILL], token, player, player_des);
        }
        default: break;
    }
    while (player_data_card_is_on (-1, CARD_SKILL_MOVEMENT_EVOLUTION_L1, player) && type[CARD_IDX_SKILL]<CARD_SKILL_FINISH1){
        gui_action_get_card (cards, &card_num, player, CARD_SPACE_HAND, CARD_BASIC_MOVEMENT_L1, CARD_BASIC_COMMON);
        choose= gui_choose_card(&choose_type, cards, card_num, "Choose a card you want to throw for the skill of move evolution 1.");
        if (choose < 0) break;
        movement_evolution1_card_idx[movement_evolution1_card_num++]= choose;
    }
    return skill_dorothy (card_idx, defense_throw_idx, defense_throw_num, 
        movement_evolution1_card_idx, movement_evolution1_card_num, player_des, player, player_des);
}

int32_t gui_skill_snow_white (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        default: break;
    }
}

int32_t gui_skill_match_girl (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        case CARD_SKILL_ATTACK_EVOLUTION_L1:
        case CARD_SKILL_DEFENSE_EVOLUTION_L1:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L1:
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        default: break;
    }
}
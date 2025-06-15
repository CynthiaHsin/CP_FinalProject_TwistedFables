# include "main.h"
# include "game_data.h"
# include "game_action.h"
# include "gui_sdl_config.h"
# include "gui_img_data.h"
# include "gui_game_render.h"
# include "gui_game_choose.h"
# include "gui_game_action.h"
# include "game_action_skill_match_girl.h"

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
        case CHARACTER_RED_RIDING_HOOD:     return gui_skill_red_riding_hood (player, card_idx, type);
        case CHARACTER_MULAN:               return gui_skill_mulan (player, card_idx, type);
        case CHARACTER_KAGUYA:              return gui_skill_kaguya (player, card_idx, type);
        case CHARACTER_DOROTHY:             return gui_skill_dorothy (player, card_idx, type);
        case CHARACTER_SNOW_WHITE:          return gui_skill_snow_white (player, card_idx, type);
        case CHARACTER_MATCH_GIRL:          return gui_skill_match_girl (player, card_idx, type);
        default: return -1;
    }
}

int32_t gui_evolution2_red_riding_hood (int32_t player){
    int32_t stored[3], stored_on[3];
    status_red_riding_hood_evolution2_card_get (stored);
    status_red_riding_hood_evolution2_on_get (stored_on);
    sCardData card_stored[CARD_IDX_NUM];
    int32_t card_stored_num= 0;
    for (int32_t i=0; i<3; i++){
        debug_print ("%d, %d\n", stored[i], stored_on[i]);
        if (stored[i]<0) continue;
        card_data_get (card_stored + card_stored_num, stored[i]);
        card_stored_num++;
    }
    gui_show_card (card_stored, card_stored_num, "Now you have stored these cards:");
    
    sCardData card_hand[CARD_NUM];
    int32_t hand_num;
    game_data_search_cards (card_hand, &hand_num, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
    for (int32_t i=0; i<3; i++){
        if (stored_on[i] && stored[i]==-1){
            int32_t choose= gui_choose_move_yes_or_no ("Do you want to store a card?");
            if (!choose) return 0;
            int32_t card_idx[CARD_IDX_NUM];
            int32_t card_type[CARD_IDX_NUM];
            if (i==0){
                card_type[0]= CARD_SKILL_ATTACK_EVOLUTION_L2;
            }else if (i==2){
                card_type[0]= CARD_SKILL_DEFENSE_EVOLUTION_L2;
            }else{
                card_type[0]= CARD_SKILL_MOVEMENT_EVOLUTION_L2;
            }
            card_idx[0]= card_data_get_index(player, card_type[0]);
            return gui_skill_red_riding_hood (player, card_idx, card_type);
        }
    }
    for (int32_t i=0; i<3; i++){
        if (stored_on[i] && stored[i]!=-1){
            int32_t choose= gui_choose_move_yes_or_no ("Do you want to get a stored card?");
            if (!choose) return 0;
            int32_t card_choose= gui_choose_card (&choose, card_stored, card_stored_num, "Choose the card you want to get.");
            if (card_choose<0) return -1;
            int32_t card_type[CARD_IDX_NUM];
            if (i==0){
                card_type[0]= CARD_SKILL_ATTACK_EVOLUTION_L2;
            }else if (i==2){
                card_type[0]= CARD_SKILL_DEFENSE_EVOLUTION_L2;
            }else{
                card_type[0]= CARD_SKILL_MOVEMENT_EVOLUTION_L2;
            }
            return status_red_riding_hood_evolution2_card_set (card_choose, card_type[0]);
        }
    }
}

int32_t gui_skill_red_riding_hood (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    int32_t skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_NUM];
    skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_SKILL]= card_idx[CARD_IDX_SKILL];
    skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACH]= card_idx[CARD_IDX_ATTACH];
    int32_t player_des= player;
    sPlayerData pd;
    player_data_get (&pd, player);
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            sCardData cards[CARD_NUM];
            int32_t card_num;
            int32_t type;
            gui_action_get_card (cards, &card_num, player, CARD_SPACE_HAND, CARD_SKILL_ATTACK_BASE_L1, CARD_SKILL_DEFENSE_EVOLUTION_L2);
            if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_ATTACK_EVOLUTION_L1, player))
                skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION]= gui_choose_card (&type, cards, card_num, "Choose a card if you wand to use ATTACK EVOLUTION 1.");
            while (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_MOVEMENT_EVOLUTION_L1, player)
                ||(skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_MOVEMENT_EVOLUTION]==skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION] && skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_ATTACK_EVOLUTION]!=-1))
                skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_MOVEMENT_EVOLUTION]= gui_choose_card (&type, cards, card_num, "Choose a card if you wand to use ATTACK EVOLUTION 1.");
            // no break
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            break;
        }
        case CARD_SKILL_FINISH1:
        {
            int32_t types[5]= {CARD_ORIGINAL, CARD_ORIGINAL, 0, 0, 0};
            sCardData cards[3];
            int32_t card_num= 3;
            int32_t t;
            card_data_get (cards + 0, card_data_get_index (player, CARD_SKILL_ATTACK_BASE_L1));
            card_data_get (cards + 1, card_data_get_index (player, CARD_SKILL_DEFENSE_BASE_L1));
            card_data_get (cards + 2, card_data_get_index (player, CARD_SKILL_MOVEMENT_BASE_L1));
            types[0]= gui_choose_card (&t, cards, card_num, "Choose the deck you want to get card from (card 1).");
            types[1]= gui_choose_card (&t, cards, card_num, "Choose the deck you want to get card from (card 2).");
            return skill_red_riding_hood_finish (card_idx[CARD_IDX_SKILL], types, types, 0, player, player_des);
        }
        case CARD_SKILL_FINISH2:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            int32_t actions[100][RED_RIDING_HOOD_CARD_IDX_NUM];
            int32_t action_num;
            status_red_riding_hood_get_action_used ((int32_t **)actions, &action_num);
            sCardData cards[CARD_NUM];
            int32_t card_num= 0;
            for (int32_t i=0; i<action_num; i++){
                card_data_get (cards+i, actions[i][0]);
                card_num++;
            }
            int32_t type;
            int32_t choose= gui_choose_card (&type, cards, card_num, "Choose the skill you want to do again.");
            for (int32_t i=0; i<action_num; i++){
                if (choose == actions[i][0]){
                    return skill_red_riding_hood_finish (card_idx[CARD_IDX_SKILL], actions[i], actions[i], 0, player, player_des);
                }
            }
        }
        case CARD_SKILL_FINISH3:
        {
            int32_t arr[5]= {0};
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            int32_t delta= gui_choose_token (3, player, "choose how long you want knock the opponent back.");
            return skill_red_riding_hood_finish (card_idx[CARD_IDX_SKILL], arr, arr, delta, player, player_des);
        }
        case CARD_SKILL_ATTACK_EVOLUTION_L2:
        case CARD_SKILL_DEFENSE_EVOLUTION_L2:
        case CARD_SKILL_MOVEMENT_EVOLUTION_L2:
        {
            sCardData cards[CARD_NUM];
            int32_t cnt;
            game_data_search_cards (cards, &cnt, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
            int32_t type;
            skilluse_card_idx[RED_RIDING_HOOD_CARD_IDX_EVOLUTION2]= gui_choose_card (&type, cards, cnt, "Choose the card you want to store.");
            break;
        }
        default: break;
    }
    if (skill_red_riding_hood (skilluse_card_idx, player, player_des)<0) return -1;
    status_red_riding_hood_action (skilluse_card_idx);
}

int32_t gui_skill_mulan (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    int32_t mulan_action[MULAN_ACTION_IDX_NUM];
    int32_t player_des;
    sPlayerData pd;
    player_data_get (&pd, player);

    mulan_action[MULAN_ACTION_IDX_THROW_DES]= 1;
    mulan_action[MULAN_ACTION_IDX_ATTACK_MOVE]= 1;
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            mulan_action[MULAN_ACTION_IDX_ATTACK_MOVE]= gui_choose_move_yes_or_no("Do you want to move the opponent (to the other side)?");
            mulan_action[MULAN_ACTION_IDX_THROW_DES]=   gui_choose_move_yes_or_no("Do you want to throw his/her card (if on the edge)?");
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        {
            int32_t level= card_data_get_level (type[CARD_IDX_SKILL]);
            char mes[100]= TEXT_CHOSE_TOKEN;
            strcat (mes, " (for defense skill: use token to get pull)");
            mulan_action[MULAN_ACTION_IDX_DEFENSE_PULL]= gui_choose_token (MIN(pd.token, level), player, mes);
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            mulan_action[MULAN_ACTION_IDX_THROW_DES]=   gui_choose_move_yes_or_no("Do you want to throw his/her card (if on the edge)?");
            break;
        }
        case CARD_SKILL_FINISH1:{
            skill_mulan_finish (card_idx[CARD_IDX_SKILL], 0, player, player);
            return 0;
        }
        case CARD_SKILL_FINISH2:{
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            int32_t direction= gui_choose_move_direction ("Choose the direction you want to be at. (count from the opponent)");
            skill_mulan_finish (card_idx[CARD_IDX_SKILL], direction, player, player_des);
            return 0;
        }
        case CARD_SKILL_FINISH3:{
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            skill_mulan_finish (card_idx[CARD_IDX_SKILL], 0, player, player_des);
            return 0;
        }
        default: break;
    }
    if (player_data_card_is_on (-1, CARD_SKILL_ATTACK_EVOLUTION_L1, player)){
        char mes[100]= TEXT_CHOSE_TOKEN;
        strcat (mes, " (for attack evolution: use token to get damage)");
        mulan_action[MULAN_ACTION_IDX_ATTACK_EVOLUTION_TOKEN]= gui_choose_token (pd.token, player, mes);
    }
    skill_mulan (card_idx, mulan_action, player, player_des);
    return 0;
}

int32_t gui_skill_kaguya (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){
    int32_t mulan_action[MULAN_ACTION_IDX_NUM];
    int32_t player_des= player;
    int32_t skill_move_use_hp_card_idx= CARD_ORIGINAL;
    int32_t skill_move_evolution_direction= gui_choose_move_direction("Move the opponent to this direction. (1 time / round)");
    sPlayerData pd;
    player_data_get (&pd, player);

    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            int32_t choose= gui_choose_move_yes_or_no ("Do you want to lose 1 hp to DELETE a card from HAND or THROW?");
            if (choose){
                sCardData cards[CARD_NUM];
                int32_t card_num, cnt;
                game_data_search_cards (cards, &cnt, player, CARD_SPACE_HAND, CARD_ORIGINAL, -1);
                card_num+= cnt;
                game_data_search_cards (cards + card_num, &cnt, player, CARD_SPACE_THROW, CARD_ORIGINAL, -1);
                card_num+= cnt;
                skill_move_use_hp_card_idx= gui_choose_card (&cnt, cards, card_num, "Choose the card to delete.");
            }
            break;
        }
        case CARD_SKILL_FINISH3:
        {
            skill_move_evolution_direction= gui_choose_move_direction ("Choose the direction you want the opponent move to. (count from your position)");
            // no break
        }
        case CARD_SKILL_FINISH2:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            // no break
        }
        case CARD_SKILL_FINISH1:
        {
            return skill_kaguya_finish (card_idx[CARD_IDX_SKILL], skill_move_evolution_direction, player, player_des);
        }
        default: break;
    }
    return skill_kaguya (card_idx, skill_move_use_hp_card_idx, skill_move_evolution_direction, player, player_des);
}

// return card idx
int32_t gui_passive_dorothy (int32_t player){
    int32_t choose= gui_choose_move_yes_or_no ("Do you want to use the passive skill?");
    if (!choose) return -1;
    sCardData cards[CARD_NUM];
    int32_t cnt;
    gui_action_get_skill_card (cards, &cnt, player, CARD_SPACE_HAND);
    return gui_choose_card (&cnt, cards, cnt, "Choose the skill you want to use.");
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
            int32_t token= gui_choose_token (pd.token, player, TEXT_CHOSE_TOKEN);
            return skill_dorothy_finish (card_idx[CARD_IDX_SKILL], token, player, player_des);
        }
        default: break;
    }
    while (player_data_card_is_on (-1, CARD_SKILL_MOVEMENT_EVOLUTION_L1, player)){
        gui_action_get_card (cards, &card_num, player, CARD_SPACE_HAND, CARD_BASIC_MOVEMENT_L1, CARD_BASIC_COMMON);
        choose= gui_choose_card(&choose_type, cards, card_num, "Choose a card you want to throw for the skill of move evolution 1.");
        if (choose < 0) break;
        movement_evolution1_card_idx[movement_evolution1_card_num++]= choose;
    }
    return skill_dorothy (card_idx, defense_throw_idx, defense_throw_num, 
        movement_evolution1_card_idx, movement_evolution1_card_num, player_des, player, player_des);
}

int32_t gui_skill_snow_white (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){

    int32_t snow_white_action[Snow_White_CARD_IDX_NUM];
    snow_white_action[Snow_White_CARD_IDX_SKILL]=card_idx[CARD_IDX_SKILL];
    snow_white_action[Snow_White_CARD_IDX_ATTACH]= card_idx[CARD_IDX_ATTACH];
    int32_t player_des= player;
    int32_t player_use= player_data_search_character(CHARACTER_SNOW_WHITE);
    int32_t move_direction=0;
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        {
            sCardData cards[CARD_NUM];
            int32_t card_num;
            int32_t type;
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            if (player_data_card_is_on (CARD_ORIGINAL, CARD_SKILL_DEFENSE_EVOLUTION_L1, player))
            {
                snow_white_action[Snow_White_CARD_IDX_POISON]= gui_choose_card (&type, cards, card_num, "Choose a card if you wand to use DEFENSE EVOLUTION 1.");
            }
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER); 
            move_direction=gui_choose_move_direction("Choose the direction you want to move(the oppenment right side or left side)? ")  ;
            break;
        }
        case CARD_SKILL_FINISH1:
        case CARD_SKILL_FINISH2:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER); 
            break;
        }
        case CARD_SKILL_FINISH3:
        {
            sCardData cards[CARD_NUM];
            int32_t card_num;
            int32_t type;
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            snow_white_action[Snow_White_CARD_IDX_FINISH1]= gui_choose_card (&type, cards, card_num, "Choose a card you want to put into your oppenment deck?(first one)");
            snow_white_action[Snow_White_CARD_IDX_FINISH2]= gui_choose_card (&type, cards, card_num, "Choose a card you want to put into your oppenment deck?(secend one)");
            snow_white_action[Snow_White_CARD_IDX_FINISH3]= gui_choose_card (&type, cards, card_num, "Choose a card you want to put into your oppenment deck?(last one)");
            break;
        }
        default: break;
    }
    return skill_snow_white ( snow_white_action, move_direction, player_use, player_des);
}

int32_t gui_skill_match_girl (int32_t player, int32_t card_idx[CARD_IDX_NUM], int32_t type[CARD_IDX_NUM]){

    int32_t match_girl_action[Match_Girl_CARD_IDX_NUM];
    match_girl_action[Match_Girl_CARD_IDX_SKILL]=card_idx[CARD_IDX_SKILL];
    match_girl_action[Match_Girl_CARD_IDX_ATTACH]= card_idx[CARD_IDX_ATTACH];
    int32_t player_des= player;
    int32_t player_use= player_data_search_character(CHARACTER_MATCH_GIRL);
    sPlayerData pd;
    player_data_get (&pd, player);
    switch (type[CARD_IDX_SKILL]){
        case CARD_SKILL_ATTACK_BASE_L1:
        case CARD_SKILL_ATTACK_BASE_L2:
        case CARD_SKILL_ATTACK_BASE_L3:
        {
            int32_t energy= gui_choose_token (pd.power, player, "想要花費的能量值(3的倍數)");
            if(energy<0)energy=0;
            energy=(energy/3)*3;
            match_girl_action[Match_Girl_POWER_NUM_ATTACK]=energy;
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER);
            break;
        }
        case CARD_SKILL_DEFENSE_BASE_L1:
        case CARD_SKILL_DEFENSE_BASE_L2:
        case CARD_SKILL_DEFENSE_BASE_L3:
        {
            int32_t level= card_data_get_level (type[CARD_IDX_SKILL]);
            int32_t HP= gui_choose_token (MIN(level, pd.hp), player, "想要花費的HP值");
            if(HP<0)HP=0;
            match_girl_action[Match_Girl_HP_NUM_DEFENSE]=HP;
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER); 
            break;
        }
        case CARD_SKILL_MOVEMENT_BASE_L1:
        case CARD_SKILL_MOVEMENT_BASE_L2:
        case CARD_SKILL_MOVEMENT_BASE_L3:
        case CARD_SKILL_FINISH1:
        case CARD_SKILL_FINISH2:
        case CARD_SKILL_FINISH3:
        {
            player_des= gui_choose_des_player (TEXT_CHOOSE_DES_PLAYER); 
            break;
        }    
        default: break;
    }
    return skill_match_girl (match_girl_action, player_use, player_des);
}
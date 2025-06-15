# pragma once
# include "main.h"

// typedef enum _eMulanTokenType{
//     MULAN_TOKEN_TYPE_DEFENSE,
//     MULAN_TOKEN_TYPE_NUM
// } eMulanTokenType;

int32_t status_mulan_init();
int32_t status_mulan_defense_token_accept_add (int32_t delta);
int32_t status_mulan_defense_token_accept_get ();
int32_t status_mulan_token_add (int32_t token, int32_t player);
int32_t status_mulan_finish1_on();
int32_t status_mulan_use_finish1();


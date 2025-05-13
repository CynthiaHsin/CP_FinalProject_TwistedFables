GAME_DATA := game_data.c game_data_card.c game_data_player.c game_data_deck.c game_data_status.c game_data_map.c
GAME_ACTION := game_action.c game_action_basic.c
GAME_ROUND := game_round.c
FUNC := -lm $(GAME_DATA) $(GAME_ACTION) $(GAME_ROUND)

all:
	# - gcc game.c $(FUNC) -o game

debug:
	# - gcc -D _DEBUG_ game.c $(FUNC) -o game
	- gcc -D _DEBUG_ test_main.c $(FUNC) -o test 

clean:
	- rm test
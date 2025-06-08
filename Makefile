# gmae engine
GAME_DATA := game_data.c game_data_card.c game_data_player.c game_data_deck.c game_data_status.c game_data_map.c
GAME_ACTION := game_action.c game_action_basic.c game_action_skill_red_riding_hood.c
GAME_ROUND := game_round.c
FUNC := -lm $(GAME_DATA) $(GAME_ACTION) $(GAME_ROUND)

# ui
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2 `sdl2-config --cflags`
LDFLAGS := `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2 -lm
OBJ := gui_game.o gui_opening.o gui_choose_character.o gui_destroy.o gui_img_init.o

all: TwitedFables
	# - gcc game.c $(FUNC) -o game

debug:
	# - gcc -D _DEBUG_ game.c $(FUNC) -o game
	- gcc -D _DEBUG_ test_main.c $(FUNC) -o test 

TwitedFables: $(OBJ)
	- $(CC) $(OBJ) -o TwitedFables $(LDFLAGS)

%.o: %.c
	- $(CC) $(CFLAGS) -c $< -o $@

clean:
	- rm -f *.o TwitedFables
	- rm test

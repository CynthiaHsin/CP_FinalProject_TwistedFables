# gmae engine
GAME_DATA_STATUS := game_data_status.c game_data_status_red_riding_hood.c game_data_status_mulan.c game_data_status_kaguya.c game_data_status_dorothy.c
GAME_DATA := game_data_card.c game_data_player.c game_data_deck.c $(GAME_DATA_STATUS) game_data_map.c game_data.c
GAME_ACTION := game_action.c game_action_basic.c game_action_skill_red_riding_hood.c game_action_skill_mulan.c game_action_skill_kaguya.c game_action_skill_dorothy.c
GAME_ROUND := game_round.c
OBJ_GAME := $(GAME_DATA) $(GAME_ACTION) $(GAME_ROUND)

# ui
OBJ_GUI := gui_game.c gui_opening.c gui_choose_character.c gui_destroy.c gui_img_init.c

# all
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2 `sdl2-config --cflags`
LDFLAGS := `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2 -lm
OBJ := $(OBJ_GAME) $(OBJ_GUI)

all: TwitedFables
	# - gcc game.c $(FUNC) -o game

debug:
	- $(CC) $(OBJ) -D _DEBUG_ game.c  -o game $(LDFLAGS)
	# - gcc -D _DEBUG_ test_main.c $(FUNC) -o test 

# TwitedFables: $(OBJ)
# 	- $(CC) $(OBJ) -o TwitedFables $(LDFLAGS)

# %.o: %.c
# 	- $(CC) $(CFLAGS) -c $< -o $@

clean:
	- rm -f *.o TwitedFables
	- rm test

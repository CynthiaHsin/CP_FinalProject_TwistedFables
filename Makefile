CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2 `sdl2-config --cflags`
LDFLAGS := `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2 -lm
OBJ := gui_game.o gui_opening.o gui_choose_character.o gui_destroy.o gui_img_init.o

all: TwitedFables

TwitedFables: $(OBJ)
	$(CC) $(OBJ) -o TwitedFables $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o TwitedFables

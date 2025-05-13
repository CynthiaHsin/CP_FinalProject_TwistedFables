CFLAGS := `sdl2-config --cflags` -Wall -Wextra -g
LDFLAGS := `sdl2-config --libs` -lSDL2_image -lSDL2 -lm

all: TwitedFables

TwitedFables: init.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f TwitedFables

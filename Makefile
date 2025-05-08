GAME_DATA := game_data.c game_data_card.c
FUNC := $(GAME_DATA)

all: $(FUNC)

debug: $(FUNC)
	- gcc -D _DEBUG_ test_main.c $(FUNC) -o test 

clean:
	- rm test

# game_data:
# 	- gcc -c game_data.c -o game_data.o

# game_data_card:
# 	- gcc -c game_data_card.c -o game_data.o
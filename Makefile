##
## File: Makefile
## Project: discord-rp-mpris
## File Created: 9th June 2022
## Author: Parumezan
## Copyright (c) 2022 JB
##

SRC =	\
		src/tools.c		\
		src/mpris.c		\
		src/discord.c	\
		src/memory.c	\
		src/main.c

BUILD_DIR = build
OBJ	= $(SRC:%.c=$(BUILD_DIR)/%.o)
CC = gcc

## Binary Name
OUTPUT = discord_rp_mpris

## Flags
CFLAGS = -I include/ -Wall -Wextra `pkg-config playerctl --cflags`
LDFLAGS = -L ./lib/ -l:libdiscord-rpc.so `pkg-config playerctl --libs`

## Rules
all: $(OUTPUT)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OBJ)
	$(CC) -o $(OUTPUT) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug: CFLAGS += -fsanitize=address,leak,undefined -g3
debug: LDFLAGS += -lasan -fsanitize=address,leak,undefined
debug: re

clean:
	rm -fr $(BUILD_DIR)

fclean: clean
	rm -f $(OUTPUT)

re: fclean all

.PHONY: all clean fclean debug re
##
## File: Makefile
## Project: discord-rp-mpris
## File Created: Thursday, 9th June 2022 1:01:11 pm
## Author: Parumezan
## -----
## Last Modified: Thursday, 9th June 2022 2:24:10 pm
## Modified By: Parumezan
## -----
## Copyright JB 2022
##

SRC =	\
		src/main.c

BUILD_DIR = build
OBJ	= $(SRC:%.c=$(BUILD_DIR)/%.o)
CC = gcc

## Binary Name
OUTPUT = discord_rp_mpris

## Flags
CFLAGS = -I include/ -Wall -Wextra `pkg-config playerctl --cflags`
LDFLAGS = -L ./lib/ -l:discord_game_sdk.so `pkg-config playerctl --libs`

## Rules
all: $(OUTPUT)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OBJ)
	$(CC) -o $(OUTPUT) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug: CFLAGS += -g
debug: fclean all

clean:
	rm -fr $(BUILD_DIR)

fclean: clean
	rm -f $(OUTPUT)

re: fclean all

.PHONY: all clean fclean debug re
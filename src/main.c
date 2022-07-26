/*
** File: main.c
** Project: src
** File Created: 9th June 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#include "discord_rp_mpris.h"

discord_rp_mpris_t *general = NULL;

void sig_handler(int sig)
{
    if (sig == SIGINT || sig == SIGTERM) {
		free_general(general);
        exit(0);
    }
}

int main(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	general = init_general();
	if (general == NULL) {
		fprintf(stderr, "Error: failed to initialize discord_rp_mpris struct\n");
		return 1;
	}
	if (refresh_mpris_data(general) != 0)
		return 1;
	display_player_data(general->player_data);
	free_general(general);
	return 0;
}
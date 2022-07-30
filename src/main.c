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
		free_discord_rpc();
        exit(0);
    }
}

int main(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	init_discord_rpc();
	general = init_general();
	if (general == NULL) {
		fprintf(stderr, "Error: failed to initialize discord_rp_mpris struct\n");
		return 1;
	}
	while (1) {
		if (refresh_mpris_data(general) != 0)
			return 1;
		if (general->activity == true) {
			printf("\033[2J\033[1;1H");
			display_player_data(general->player_data);
			update_status(general);
		}
		sleep(2);
	}
	free_general(general);
	free_discord_rpc();
	return 0;
}
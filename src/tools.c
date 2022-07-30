/*
** File: tools.c
** Project: src
** File Created: 26th July 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#include "discord_rp_mpris.h"

void display_player_data(playerdata_t *data)
{
    if (data == NULL)
        return;
    printf("Player name: %s\n", data->player_name);
    printf("Status: ");
	switch (data->status) {
		case PLAYERCTL_PLAYBACK_STATUS_PLAYING: printf("Playing..\n");
			break;
		case PLAYERCTL_PLAYBACK_STATUS_PAUSED: printf("Paused\n");
			break;
		case PLAYERCTL_PLAYBACK_STATUS_STOPPED: printf("Stopped\n");
			break;
		default: printf("None\n");
			break;
	}
    printf("Title: %s\n", data->title);
    printf("Artist: %s\n", data->artist);
    printf("Album: %s\n", data->album);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Actual time: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
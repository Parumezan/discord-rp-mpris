/*
** File: mpris.c
** Project: src
** File Created: 26th July 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#include "discord_rp_mpris.h"

static playerdata_t *get_player_data(discord_rp_mpris_t *general, PlayerctlPlayerName *player_name)
{
	GError *error = NULL;
	PlayerctlPlayer *player = NULL;
	playerdata_t *data = init_playerdata();

	if (data == NULL)
		return NULL;
	player = playerctl_player_new_from_name(player_name, &error);
	if (error != NULL) {
		g_printerr("%s\n", error->message);
		return NULL;
	}
	data->player_name = strdup(player_name->name);
	g_object_get(player, "playback-status", &data->status, NULL);
	if (data->status != PLAYERCTL_PLAYBACK_STATUS_STOPPED) {
		if ((data->title = strdup(playerctl_player_get_title(player, &error))) == NULL)
			fprintf(stderr, "Error: failed to get title\n");
		if ((data->artist = strdup(playerctl_player_get_artist(player, &error))) == NULL)
			fprintf(stderr, "Error: failed to get artist\n");
		if ((data->album = strdup(playerctl_player_get_album(player, &error))) == NULL)
			fprintf(stderr, "Error: failed to get album\n");
		if (general->last_song == NULL) {
			general->last_song = strdup(data->title);
			general->icon_index = rand() % (MAX_ICONS - 1);
		} else {
			if (strcmp(general->last_song, data->title) != 0) {
				free(general->last_song);
				general->last_song = strdup(data->title);
				general->icon_index = rand() % (MAX_ICONS - 1);
			}
		}
	}
	g_object_unref(player);
	return data;
}

static int remove_player_data(discord_rp_mpris_t *general)
{
	if (general->player_data != NULL) {
		free_playerdata(general->player_data);
		general->player_data = NULL;
	}
	if (general->actual_player != NULL) {
		free(general->actual_player);
		general->actual_player = NULL;
	}
	return 0;
}

static int parse_players(discord_rp_mpris_t *general, GList *list, guint length)
{
	PlayerctlPlayerName *player_name = NULL;
	playerdata_t *data = NULL;

	for (guint cpt = 0; cpt < length; cpt++) {
		player_name = g_list_nth_data(list, cpt);
		data = get_player_data(general, player_name);
		if (data->status == PLAYERCTL_PLAYBACK_STATUS_PLAYING) {
			general->actual_player = strdup(player_name->name);
			general->player_data = data;
			general->activity = true;
			return 0;
		}
		free_playerdata(data);
	}
	player_name = g_list_nth_data(list, 0);
	general->actual_player = strdup(player_name->name);
	general->player_data = get_player_data(general, player_name);
	general->activity = true;
	return 0;
}

static int get_pos_find_player(discord_rp_mpris_t *general, GList *list, guint length)
{
	PlayerctlPlayerName *player_name = NULL;

	for (guint cpt = 0; cpt < length; cpt++) {
		player_name = g_list_nth_data(list, cpt);
		if (g_strcmp0(general->actual_player, player_name->name) == 0) {
			return cpt;
		}
	}
	return -1;
}

int refresh_mpris_data(discord_rp_mpris_t *general)
{
	GError *error = NULL;
	GList *list = playerctl_list_players(&error);
	guint length = g_list_length(list);
	PlayerctlPlayerName *player_name = NULL;
	int check = -1;

	if (error != NULL) {
		g_printerr("%s\n", error->message);
		return 1;
	}
	if (length == 0) {
		general->activity = false;
		Discord_ClearPresence();
		return remove_player_data(general);
	}
	if (general->actual_player != NULL) {
		if ((check = get_pos_find_player(general, list, length)) != -1) {
			player_name = g_list_nth_data(list, check);
			free_playerdata(general->player_data);
			general->player_data = get_player_data(general, player_name);
			return 0;
		}
		remove_player_data(general);
	}
	return parse_players(general, list, length);
}
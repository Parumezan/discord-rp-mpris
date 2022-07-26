/*
** File: mpris.c
** Project: src
** File Created: 26th July 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#include "discord_rp_mpris.h"

static playerdata_t *get_player_data(PlayerctlPlayerName *player_name)
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
	if (data->player_name == NULL)
		data->player_name = g_strdup(player_name->name);
	g_object_get(player, "playback-status", &data->status, NULL);
	if (data->status != PLAYERCTL_PLAYBACK_STATUS_STOPPED) {
		if ((data->title = g_strdup(playerctl_player_get_title(player, &error))) == NULL)
			g_printerr("%s\n", error->message);
		if ((data->artist = g_strdup(playerctl_player_get_artist(player, &error))) == NULL)
			g_printerr("%s\n", error->message);
		if ((data->album = g_strdup(playerctl_player_get_album(player, &error))) == NULL)
			g_printerr("%s\n", error->message);
		data->position = playerctl_player_get_position(player, &error);
	}
	return data;
}

static int remove_player_data(discord_rp_mpris_t *general)
{
	free_playerdata(general->player_data);
	if (general->actual_player != NULL) {
		g_free(general->actual_player);
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
		data = get_player_data(player_name);
		if (data->status != PLAYERCTL_PLAYBACK_STATUS_STOPPED) {
			general->actual_player = g_strdup(player_name->name);
			general->player_data = data;
			return 0;
		}
		free_playerdata(data);
	}
	player_name = g_list_nth_data(list, 0);
	general->player_data = get_player_data(player_name);
	general->actual_player = g_strdup(player_name->name);
	return 0;
}

int refresh_mpris_data(discord_rp_mpris_t *general)
{
	GError *error = NULL;
	GList *list = playerctl_list_players(&error);
	GList *check = NULL;
	guint length = g_list_length(list);
	PlayerctlPlayerName *player_name = NULL;

	if (error != NULL) {
		g_printerr("%s\n", error->message);
		return 1;
	}
	if (length == 0)
		return remove_player_data(general);
	if (general->actual_player != NULL) {
		if ((check = g_list_find_custom(list, general->actual_player,
		(GCompareFunc)g_strcmp0)) != NULL) {
			player_name = g_list_nth_data(list, g_list_position(list, check));
			free_playerdata(general->player_data);
			general->player_data = get_player_data(player_name);
			return 0;
		}
		remove_player_data(general);
	}
	remove_player_data(general);
	return parse_players(general, list, length);
}
/*
** File: memory.c
** Project: src
** File Created: 26th July 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#include "discord_rp_mpris.h"

discord_rp_mpris_t *init_general(void)
{
    discord_rp_mpris_t *general = malloc(sizeof(discord_rp_mpris_t));

    if (general == NULL)
        return NULL;
    general->activity = false;
    general->actual_player = NULL;
    general->player_data = NULL;
    general->large_icons = malloc(sizeof(char *) * 8);
    if (general->large_icons == NULL)
        return NULL;
    general->large_icons[0] = strdup("dj-mixer");
    general->large_icons[1] = strdup("magazine");
    general->large_icons[2] = strdup("note");
    general->large_icons[3] = strdup("playlist");
    general->large_icons[4] = strdup("turntable");
    general->large_icons[5] = strdup("tape");
    general->large_icons[6] = strdup("vinyl");
    general->large_icons[7] = NULL;
    general->icon_index = 0;
    general->last_song = NULL;
    return general;
}

void free_general(discord_rp_mpris_t *general)
{
    if (general == NULL)
        return;
    free_playerdata(general->player_data);
    if (general->actual_player != NULL)
        free(general->actual_player);
    if (general->large_icons != NULL) {
        for (int cpt = 0; general->large_icons[cpt] != NULL; cpt++)
            free(general->large_icons[cpt]);
        free(general->large_icons);
    }
    if (general->last_song != NULL)
        free(general->last_song);
    free(general);
}

playerdata_t *init_playerdata(void)
{
    playerdata_t *player = malloc(sizeof(playerdata_t));

    if (player == NULL)
        return NULL;
    player->player_name = NULL;
    player->status = 0;
    player->title = NULL;
    player->artist = NULL;
    player->album = NULL;
    return player;
}

void free_playerdata(playerdata_t *player)
{
    if (player == NULL)
        return;
    if (player->player_name != NULL) {
        free(player->player_name);
        player->player_name = NULL;
    }
    if (player->title != NULL) {
        free(player->title);
        player->title = NULL;
    }
    if (player->artist != NULL) {
        free(player->artist);
        player->artist = NULL;
    }
    if (player->album != NULL) {
        free(player->album);
        player->album = NULL;
    }
    free(player);
}
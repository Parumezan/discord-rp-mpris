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
    general->actual_player = NULL;
    general->player_data = NULL;
    return general;
}

void free_general(discord_rp_mpris_t *general)
{
    if (general == NULL)
        return;
    free_playerdata(general->player_data);
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
    player->length = 0;
    return player;
}

void free_playerdata(playerdata_t *player)
{
    if (player == NULL)
        return;
    if (player->player_name != NULL) {
        g_free(player->player_name);
        player->player_name = NULL;
    }
    if (player->title != NULL) {
        g_free(player->title);
        player->title = NULL;
    }
    if (player->artist != NULL) {
        g_free(player->artist);
        player->artist = NULL;
    }
    if (player->album != NULL) {
        g_free(player->album);
        player->album = NULL;
    }
    free(player);
}
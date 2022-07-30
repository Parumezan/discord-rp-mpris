/*
** File: discord_rp_mpris.h
** Project: include
** File Created: 26th July 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#ifndef DISCORD_RP_MPRIS_H_
#define DISCORD_RP_MPRIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <playerctl.h>
#include "discord_rpc.h"

#define MAX_ICONS 7

typedef struct playerdata_s {
    char *player_name;
    PlayerctlPlaybackStatus status;
    char *title;
    char *artist;
    char *album;
} playerdata_t;

typedef struct discord_rp_mpris_s {
    bool activity;
    char *actual_player;
    playerdata_t *player_data;
    char **large_icons;
    int icon_index;
    char *last_song;
} discord_rp_mpris_t;

// src
    // tools.c
        void display_player_data(playerdata_t *player);

    // mpris.c
        int refresh_mpris_data(discord_rp_mpris_t *general);

    // memory.c
        discord_rp_mpris_t *init_general(void);
        void free_general(discord_rp_mpris_t *general);
        playerdata_t *init_playerdata(void);
        void free_playerdata(playerdata_t *player);

    // discord.c
        void init_discord_rpc(void);
        void update_status(discord_rp_mpris_t *general);
        void free_discord_rpc(void);

#endif /* !DISCORD_RP_MPRIS_H_ */
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
#include <playerctl.h>

typedef struct playerdata_s {
    gchar *player_name;
    PlayerctlPlaybackStatus status;
    gchar *title;
    gchar *artist;
    gchar *album;
    guint length;
} playerdata_t;

typedef struct discord_rp_mpris_s {
    gchar *actual_player;
    playerdata_t *player_data;
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

#endif /* !DISCORD_RP_MPRIS_H_ */
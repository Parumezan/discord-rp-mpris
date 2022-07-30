/*
** File: discord.c
** Project: src
** File Created: 28th July 2022
** Author: Parumezan
** Copyright (c) 2022 JB
*/

#include "discord_rp_mpris.h"

// Discord_Shutdown();

static void handleDiscordDisconnected(int errcode, const char *message)
{
    printf("Discord-rpc: Disconnected (%d): %s\n", errcode, message);
}

static void handleDiscordError(int errcode, const char *message)
{
    printf("Discord-rpc: Error (%d): %s\n", errcode, message);
}

static void handleDiscordReady(const DiscordUser *user)
{
    printf("Discord-rpc: %s(%s) Connected\n", user->username, user->userId);
}

void init_discord_rpc(void)
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordError;
    handlers.disconnected = handleDiscordDisconnected;
    Discord_Initialize("1001983147052900453", &handlers, 1, NULL);
}

void update_status(discord_rp_mpris_t *general)
{
    DiscordRichPresence discordPresence;
    char *details = NULL;

    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.largeImageKey = general->large_icons[general->icon_index];
    switch (general->player_data->status) {
        case PLAYERCTL_PLAYBACK_STATUS_PLAYING: discordPresence.smallImageKey = "play";
            break;
        case PLAYERCTL_PLAYBACK_STATUS_PAUSED: discordPresence.smallImageKey = "pause";
            break;
        case PLAYERCTL_PLAYBACK_STATUS_STOPPED: discordPresence.smallImageKey = "stop";
            break;
        default: discordPresence.smallImageKey = "stop";
            break;
    }
    details = malloc(sizeof(char) * (strlen(general->player_data->title)
    + strlen(general->player_data->album) + 4));
    if (details == NULL)
        return;
    sprintf(details, "%s | %s", general->player_data->title, general->player_data->album);
    discordPresence.details = details;
    discordPresence.state = general->player_data->artist;
    Discord_UpdatePresence(&discordPresence);
    free(details);
}

void free_discord_rpc(void)
{
    Discord_Shutdown();
}
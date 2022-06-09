/*
** File: main.c
** Project: src
** File Created: Thursday, 9th June 2022 1:01:11 pm
** Author: Parumezan
** -----
** Last Modified: Thursday, 9th June 2022 1:18:13 pm
** Modified By: Parumezan
** -----
** Copyright JB 2022
*/

#include "discord_mpris.h"

int main()
{
    GError *error = NULL;
    GList *players = playerctl_list_players(error);

    // print the list of players
    for (GList *l = players; l != NULL; l = l->next)
    {
        g_print("%s\n", (char *)l->data);
    }
    return 0;
}
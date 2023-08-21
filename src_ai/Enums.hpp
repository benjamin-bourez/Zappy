/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Enums
*/

#pragma once

#include <vector>
#include <string>

namespace Zappy::AI {
    enum Ressource {
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        FOOD,
        PLAYER,
        EMPTY
    };

    enum Commands {
        FORWARD,
        RIGHT,
        LEFT,
        LOOK,
        INVENTORY,
        BROADCAST,
        CONNECT_NBR,
        FORK,
        EJECT,
        TAKE,
        SET,
        INCANTATION,
        UNKNOWN
    };

    enum Orientation {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    enum IncantationStatus {
        WAITING,
        READY,
        START
    };
    
    enum Incantation {
        NOTENOUGHPLAYER,
        TOOMANYPLAYER,
        NOTENOUGHFOOD,
        NOTENOUGHRESSOURCES,
        SETRESSOURCES,
        SUCCESS
    };
}
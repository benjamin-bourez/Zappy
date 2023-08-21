/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Core
*/

#pragma once

#include "Args.hpp"
#include "../shared_src/Client.hpp"
#include "VoxelCore.hpp"
#include <iostream>
#include <memory>
#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <tuple>
#include <chrono>

namespace Zappy::GUI
{
    class Core {
        public:
            /**
             * @brief Construct a new Core object
            */
            Core();
            /**
             * @brief Destroy the Core object
            */
            ~Core();
            /**
             * @brief Run the core
            */
            void run();
            /**
             * @brief Set the Args object
             * @param args
             * @return void
            */
            void setArgs(std::shared_ptr<Args> args);
            /**
             * @brief Set the Client object
             * @param client
             * @return void
            */
            void setClient(std::shared_ptr<Client> client);
            /**
             * @brief Unload Voxel
            */
            void unloadUponServerMissing();
        protected:
        private:
            /**
             * @brief Receive WELCOME from server
            */
            void welcome(std::string command);
            /**
             * @brief Receive MAP_SIZE from server
            */
            void mapSize(std::string command);
            /**
             * @brief Receive TILE_CONTENT from server
            */
            void tileContent(std::string command);
            /**
             * @brief Receive TEAMS_NAMES from server
            */
            void teamName(std::string command);
            /**
             * @brief Receive PLAYER_POSITION from server
            */
            void playerPosition(std::string command);
            /**
             * @brief Receive PLAYER_LEVEL from server
            */
            void playerLevel(std::string command);
            /**
             * @brief Receive PLAYER_INVENTORY from server
            */
            void playerInventory(std::string command);
            /**
             * @brief Receive TIME_UNIT from server
            */
            void timeUnit(std::string command);
            /**
             * @brief Receive PLAYER_CONNECTION from server
            */
            void playerConnection(std::string command);
            /**
             * @brief Receive PLAYER_EXPULSION from server
            */
            void expulse(std::string command);
            /**
             * @brief Receive BROADCAST from server
            */
            void broadcast(std::string command);
            /**
             * @brief Receive INCANTATION_START from server
            */
            void incantationStart(std::string command);
            /**
             * @brief Receive INCANTATION_END from server
            */
            void incantationEnd(std::string command);
            /**
             * @brief Receive EGG_LAYING from server
            */
            void eggLaying(std::string command);
            /**
             * @brief Receive EGG_HATCHING from server
            */
            void resourceDrop(std::string command);
            /**
             * @brief Receive RESOURCE_COLLECT from server
            */
            void resourceCollect(std::string command);
            /**
             * @brief Receive PLAYER_DEATH from server
            */
            void playerDeath(std::string command);
            /**
             * @brief Receive EGG_LAID from server
            */
            void eggLaid(std::string command);
            /**
             * @brief Receive EGG_CONNECTION from server
            */
            void eggConnection(std::string command);
            /**
             * @brief Receive EGG_DEATH from server
            */
            void eggDeath(std::string command);
            /**
             * @brief Receive END_GAME from server
            */
            void endGame(std::string command);
            /**
             * @brief Receive SERVER_MESSAGE from server
            */
            void serverMessage(std::string command);
            /**
             * @brief Receive UNKNOWN_COMMAND from server
            */
            void unknownCommand(std::string command);
            /**
             * @brief Receive COMMAND_PARAMETER from server
            */
            void commandParameter(std::string command);

            std::shared_ptr<Args> _args;
            std::shared_ptr<Client> _client;
            std::map<std::string, void (Core::*)(const std::string)> _handlers;
            Voxel::VoxelCore _voxel;
            std::vector<int> _playerIDs;
            bool _voxelInit;
            std::chrono::_V2::system_clock::time_point _lastUpdate;
            int _timeUnit;
    };
} // namespace Zappy

/**
 * @brief Signal handler
 * @param flag
 * @param value
 * @return int
*/
int signalMemory(int flag, int value);

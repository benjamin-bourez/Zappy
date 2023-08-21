/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxelCore
*/

#pragma once

#include <chrono>
#include <map>

#include "Window.hpp"
#include "Camera.hpp"
#include "Character.hpp"
#include "VoxMusic.hpp"
#include "VoxSound.hpp"

namespace Voxel {
    class VoxelCore {
        public:
            VoxelCore();
            ~VoxelCore();

            /**
            * @brief Draw the window
            */
            void draw();
            /**
            * @brief Check if the window should close
            * @return True if the window should close, false otherwise
            */
            bool shouldStop();
            /**
            * @brief Close the window
            */
            void closeWindow();
            /**
            * @brief Set the map size
            * @param x The x size
            * @param y The y size
            */
            void setMapSize(int x, int y);
            /**
            * @brief Set the tile content
            * @param x The x position of the tile
            * @param y The y position of the tile
            * @param content The content of the tile
            */
            void setTileContent(int x, int y, std::vector<int> content);
            /**
            * @brief Add a team name
            * @param teamName The name of the team
            */
            void addTeamName(std::string teamName);
            /**
            * @brief Set the player position
            * @param id The id of the player
            * @param x The x position of the player
            * @param y The y position of the player
            * @param orientation The orientation of the player
            */
            void setPlayerPosition(int id, int x, int y, int orientation);
            /**
            * @brief Set the player level
            * @param id The id of the player
            * @param level The level of the player
            */
            void setPlayerLevel(int id, int level);
            /**
            * @brief Set the player inventory
            * @param id The id of the player
            * @param inventory The inventory of the player
            */
            void setPlayerInventory(int id, std::vector<int> inventory);
            /**
            * @brief Set the player team
            * @param id The id of the player
            * @param teamName The name of the team
            */
            void setPlayerTeam(int id, std::string teamName);
            /**
            * @brief Set the player broadcast
            * @param id The id of the player
            */
            void setPlayerBroadcast(int id);
            /**
            * @brief Set the time unit
            * @param timeUnit The time unit
            */
            void setTimeUnit(int timeUnit);
            /**
            * @brief Add an egg
            * @param x The x position of the egg
            * @param y The y position of the egg
            * @param playerId The id of the player
            * @param id The id of the egg
            */
            void addEgg(int x, int y, int playerId, int id);
            /**
            * @brief Remove an egg
            * @param id The id of the egg
            */
            void removeEgg(int id);
            /**
            * @brief Unload the models
            */
            void unloadModels();
            /**
            * @brief Set the camera position
            * @param x The x position of the camera
            * @param y The y position of the camera
            * @param z The z position of the camera
            */
            void setCameraPosition(float x, float y, float z);
            /**
            * @brief Expulse every other player from the tile
            * @param id The id of the player that used the expulse command
            */
            void expulse(int id);
            /**
            * @brief Drop a resource
            * @param id The id of the player that used the drop command
            * @param resource The resource that was dropped
            */
            void resourceDrop(int id, int resource);
            /**
            * @brief Collect a resource
            * @param id The id of the player that used the collect command
            * @param resource The resource that was collected
            */
            void resourceCollect(int id, int resource);
            /**
            * @brief Kill a player
            * @param id The id of the player that was killed
            */
            void playerDeath(int id);
            /**
            * @brief Set the winner team
            * @param teamName The name of the team that won
            */
            void endGame(std::string teamName);
            /**
            * @brief Check if the game must start
            * @return True if the game must start, false otherwise
            */
            bool shouldStart();
            /**
            * @brief Update the audio
            */
            void updateAudio();
            /**
            * @brief Set the level up boolean
            * @param levelUp The level up boolean
            */
            void setLevelUp(bool levelUp);
            /**
            * @brief Display the main menu
            * @return True if an option changed false otherwise
            */
            int mainMenu();
            /**
            * @brief Reset the position of the camera
            */
            void resetPosition();
            /**
            * @brief Update the volume of the sounds
            */
            void updateVolume();
            /**
            * @brief Get the time unit
            * @return The time unit
            */
            int getTimeUnit() const;
            /**
            * @brief Start an incantation
            * @param id The id of the player that started the incantation
            */
            void incantationStart(std::vector<std::string> id);
            /**
            * @brief End an incantation
            * @param x The x position of the incantation
            * @param y The y position of the incantation
            */
            void incantationEnd(int x, int y);
            /**
            * @brief Connect a player to an egg
            * @param id The id of the egg
            */
            void eggConnection(int id);
            /***
             * @brief Set the Mute object
             * 
             * @param mute 
             */
            void setMute(bool mute);
        private:
            std::unique_ptr<VoxMusic> _music;
            std::map<std::string, std::shared_ptr<VoxSound>> _sounds;
            Window _window;
            Camera _camera;
            Scene _scene;
            bool _levelUp;
            bool _broadcast;
            bool _dead;
            bool _egglaid;
            bool _eggremoved;
            bool _eject;
            bool _win;
            int _incantation;
    };
};

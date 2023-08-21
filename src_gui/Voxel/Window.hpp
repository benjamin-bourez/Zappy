/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Window
*/

#pragma once

#include <chrono>
#include <map>

#include "Voxel.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "VoxColor.hpp"

namespace Voxel {
    enum MenuType {
        MAIN_MENU,
        OPTIONS_MENU,
        DEFAULT
    };

    struct egg {
        egg();
        egg(int x, int y, std::string teamName, int id);
        ~egg() = default;
        int x;
        int y;
        int id;
        std::string team;
    };

    struct map {
        map();
        ~map() = default;
        int x;
        int y;
        std::vector<std::vector<std::vector<int>>> tiles;
    };

    struct button {
        button();
        ~button() = default;
        Vector2 pos;
        Rectangle rect;
        int btnState;
        bool btnAction;
        MenuType menuType;
        bool displayed;
        bool changeMap;
        bool startGame;
        int type;
        float scale;
        bool stop;
    };

    struct slider {
        slider();
        ~slider() = default;
        Vector2 pos;
        Rectangle rect;
        float value;
        bool displayed;
        bool held;
        std::string option;
    };

    struct player {
        player();
        ~player() = default;
        int id;
        int x;
        int y;
        int direction;
        int level;
        bool incantation;
        std::string team;
        Voxel::VoxColor color;
        std::vector<int> inventory;
        BroadcastType broadcastType;
        std::chrono::time_point<std::chrono::system_clock> broadcastStart;
    };

    class Window {
        public:
            Window();
            ~Window();

            /**
            * @brief Check if the window should close
            * @return True if the window should close, false otherwise
            */
            bool shouldClose();
            /**
            * @brief Draw the window
            * @param scene The scene to draw
            * @param camera The camera to draw
            */
            void draw(Scene &scene, Voxel::Camera &camera);
            /**
            * @brief Close the window
            */
            void close();
            /**
            * @brief Set the map
            * @param tiles The tiles of the map
            */
            void setMap(std::vector<std::vector<std::vector<int>>> tiles);
            /**
            * @brief Set the map size
            * @param x The x size of the map
            * @param y The y size of the map
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
            * @param teamName The team name of the player
            */
            void setPlayerTeam(int id, std::string teamName);
            /**
            * @brief Set the player broadcast
            * @param id The id of the player
            */
            void setPlayerBroadcast(int id);
            /**
            * @brief Add an egg
            * @param x The x position of the egg
            * @param y The y position of the egg
            * @param playerId The id of the player who laid the egg
            * @param id The id of the egg
            */
            void addEgg(int x, int y, int playerId, int id);
            /**
            * @brief Remove an egg
            * @param id The id of the egg
            */
            void removeEgg(int id);
            /**
            * @brief Expulse every other player from the tile
            * @param id The id of the player
            */
            void expulse(int id);
            /**
            * @brief Drop a resource on the tile
            * @param id The id of the player
            * @param resource The resource to drop
            */
            void resourceDrop(int id, int resource);
            /**
            * @brief Collect a resource from the tile
            * @param id The id of the player
            * @param resource The resource to collect
            */
            void resourceCollect(int id, int resource);
            /**
            * @brief Kill a player
            * @param id The id of the player
            */
            void playerDeath(int id);
            /**
            * @brief Set the winner team
            * @param teamName The name of the team
            */
            void endGame(std::string teamName);
            /**
            * @brief Set the time unit
            * @param timeUnit The time unit
            */
            void setTimeUnit(int timeUnit);
            /**
            * @brief Add a team name
            * @param teamName The name of the team
            */
            void addTeamName(std::string teamName);
            /**
            * @brief Check if the game should start
            * @return True if the game should start, false otherwise
            */
            bool shouldStart();
            /**
            * @brief Display the main menu
            * @param scene The scene to draw
            * @return True if the game should start, false otherwise
            */
            int mainMenu(Scene &scene);
            /**
            * @brief Get the volume
            * @return The volume
            */
            float getVolume() const;
            void setVolume(float volume);
            /**
            * @brief Get the time unit
            * @return The time unit
            */
            int getTimeUnit() const;
            /**
            * @brief Disable the cursor
            */
            void disableCursor();
            /**
            * @brief Enable the cursor
            */
            void enableCursor();
            /**
            * @brief Start an incantation
            * @param id The id of the players
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
            * @param id The id of the player
            */
            void eggConnection(int id);
        private:
            map _map;
            std::map<int, player> _players;
            std::map<int, egg> _eggs;
            std::vector<button> _buttons;
            std::vector<slider> _sliders;
            int _timeUnit;
            float _volume;
            std::vector<std::string> _teamNames;
            std::vector<int> _teamSizes;
            bool _shouldStart;
            Vector2 _mousePos;
            MenuType _menuType;
            int _tileType;
            std::unordered_map<std::string, VoxColor> _teamColors;
            bool _cursorEnabled;
            std::chrono::_V2::system_clock::time_point _endGameStart;
            bool _end;
            std::string _winningTeam;
            bool _stop;

            /**
            * @brief Draw a tile
            * @param pos The position of the tile
            * @param scene The scene to draw
            * @param parameters The parameters of the tile
            */
            void drawTile(std::pair<int, int> pos, Scene &scene, std::vector<float> parameters);
            /**
            * @brief Load the buttons
            */
            void loadButtons();
            /**
            * @brief Load the sliders
            */
            void loadSliders();
            /**
            * @brief Change the menu type
            */
            void changeMenu();
            /**
            * @brief Get the id of a team by its name
            * @param teamName The name of the team
            * @return The id of the team
            */
            int getIdByTeamName(std::string teamName);
    };
};

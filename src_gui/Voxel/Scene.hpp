/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Scene
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <optional>

#include "Voxel.hpp"
#include "Entity.hpp"
#include "Character.hpp"
#include "Factory.hpp"
#include "VoxTexture.hpp"
#include "VoxGif.hpp"

namespace Voxel {
    class Scene {
        public:
            Scene();
            Scene(std::vector<std::string> modelsPath);
            ~Scene();

            /**
            * @brief Add an entity to the scene
            * @param id The id of the entity
            * @param entity The entity to add
            */
            void addEntity(int id, Voxel::Entity entity);
            /**
            * @brief Remove an entity from the scene
            * @param id The id of the entity
            */
            void removeEntity(int id);
            /**
            * @brief Draw the scene
            * @param position The position of the entity
            * @param parameters The parameters of the entity
            * @param broadcastType The type of broadcast
            * @param color The color of the entity's team
            */
            void draw(Vector3 position, std::vector<float> parameters, BroadcastType broadcastType, std::optional<VoxColor> color);
            /**
            * @brief Display the meno
            * @param position The position of the entity
            * @param type The type of the entity
            * @param state The state of the entity
            * @param scale The scale of the entity
            */
            void display(Vector2 position, int type, int state, float scale);
            /**
            * @brief Display the gif
            */
            void displayGif();
            /**
            * @brief Add a team name
            * @param teamName The name of the team
            */
            void addTeamName(std::string teamName);
            /**
            * @brief Unload the scene's models
            */
            void unloadModels();
        protected:
        private:
            std::unordered_map<int, std::shared_ptr<Voxel::Entity>> _entities;
            std::unique_ptr<Voxel::Character> _character;
            std::pair<std::shared_ptr<Voxel::Entity>, std::shared_ptr<Voxel::Entity>> _tile;
            std::pair<std::unique_ptr<Entity>, std::unique_ptr<Entity>> _broadcast;
            std::vector<std::string> _teamNames;
            std::unordered_map<int, std::shared_ptr<Voxel::VoxTexture>> _textures;
            std::unique_ptr<Voxel::VoxGif> _gif;
            Factory _factory;

            /**
            * @brief Draw the tile
            * @param x The x position of the tile
            * @param y The y position of the tile
            * @param type The type of the tile
            */
            void drawTile(int x, int y, int type);
    };
}

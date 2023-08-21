/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Factory
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <string>

#include "Voxel.hpp"
#include "Entity.hpp"
#include "Character.hpp"
#include "VoxTexture.hpp"
#include "VoxGif.hpp"

namespace Voxel {
    class Factory {
        public:
            Factory();
            ~Factory();

            /**
            * @brief Create an entity
            * @param modelPath The path to the model
            * @param type The class type of the entity
            * @param id The id of the entity
            * @param entityType The type of the entity
            */
            void createEntity(std::string modelPath, std::string type, int id, EntityType entityType);
            /**
            * @brief Create a texture
            * @param modelPath The path to the model
            * @param id The id of the texture
            */
            void createTexture(std::string modelPath, int id);
            /**
            * @brief Create a gif
            * @param modelPath The path to the model
            */
            void createGif(std::string modelPath);
            /**
            * @brief Get the entities
            * @return The entities
            */
            std::unordered_map<int, std::shared_ptr<Voxel::Entity>> getEntities();
            /**
            * @brief Get the character
            * @return The character
            */
            std::unique_ptr<Voxel::Character> getCharacter();
            /**
            * @brief Get the tile
            * @return The tile
            */
            std::pair<std::shared_ptr<Voxel::Entity>, std::shared_ptr<Voxel::Entity>> getTile();
            /**
            * @brief Get the textures
            * @return The textures
            */
            std::unordered_map<int, std::shared_ptr<Voxel::VoxTexture>> getTextures();
            /**
            * @brief Get the gif
            * @return The gif
            */
            std::unique_ptr<Voxel::VoxGif> getGif();
        private:
            std::unordered_map<std::string, void (Factory::*)(std::string, int, EntityType)> _entityFactory;
            std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> _broadcast;
            std::unordered_map<int, std::shared_ptr<Voxel::Entity>> _entities;
            std::unique_ptr<Voxel::Character> _character;
            std::pair<std::shared_ptr<Voxel::Entity>, std::shared_ptr<Voxel::Entity>> _tile;
            std::unordered_map<int, std::shared_ptr<Voxel::VoxTexture>> _textures;
            std::shared_ptr<Voxel::Entity> _incantation;
            std::unique_ptr<Voxel::VoxGif> _gif;

            /**
            * @brief Create a character
            * @param modelPath The path to the model
            * @param id The id of the character
            * @param entityType The type of the character
            */
            void character(std::string modelPath, int id, EntityType entityType);
            /**
            * @brief Create an entity
            * @param modelPath The path to the model
            * @param id The id of the texture
            * @param entityType The type of the texture
            */
            void entity(std::string modelPath, int id, EntityType entityType);
            /**
            * @brief Create a broadcast
            * @param modelPath The path to the model
            * @param id The id of the broadcast
            * @param entityType The type of the broadcast
            */
            void broadcast(std::string modelPath, int id, EntityType entityType);
            /**
            * @brief Create a tile
            * @param modelPath The path to the model
            * @param id The id of the tile
            * @param entityType The type of the tile
            */
            void tile(std::string modelPath, int id, EntityType entityType);
            /**
            * @brief Create an incantation
            * @param modelPath The path to the model
            * @param id The id of the incantation
            * @param entityType The type of the incantation
            */
            void incantation(std::string modelPath, int id, EntityType entityType);
    };
};

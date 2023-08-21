/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Entity
*/

#pragma once

#include <string>
#include <unordered_map>

#include "Voxel.hpp"

namespace Voxel {
    enum EntityType {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        TILE,
        EGG,
        NONE
    };

    class Entity {
        public:
            Entity();
            Entity(Model model, EntityType type);
            Entity(std::string modelPath, EntityType type);
            Entity(const Entity &entity);
            ~Entity();

            /**
            * @brief Set the model of the entity
            * @param model The model of the entity
            */
            void setModel(Model &model);
            /**
            * @brief Get the model of the entity
            * @return The model of the entity
            */
            Model getModel() const;
            /**
            * @brief Set the type of the entity
            * @param type The type of the entity
            */
            void setEntityType(EntityType type);
            /**
            * @brief Get the type of the entity
            * @return The type of the entity
            */
            EntityType getEntityType() const;

            /**
            * @brief Draw the entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            * @param scale The scale of the entity
            */
            void draw(float x, float y, float z, float scale);
            /**
            * @brief Draw the entity
            * @param position The position of the entity
            * @param scale The scale of the entity
            */
            void draw(Vector3 &position, float scale);
            /**
            * @brief Unload the entity's model
            */
            void unload();
        protected:
            Model _model;
            EntityType _type;
            std::unordered_map<EntityType, void (Entity::*)(float, float, float)> methodPointer;

            /**
            * @brief Draw the food entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void food(float x, float y, float z);
            /**
            * @brief Draw the linemate entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void linemate(float x, float y, float z);
            /**
            * @brief Draw the deraumere entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void deraumere(float x, float y, float z);
            /**
            * @brief Draw the sibur entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void sibur(float x, float y, float z);
            /**
            * @brief Draw the mendiane entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void mendiane(float x, float y, float z);
            /**
            * @brief Draw the phiras entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void phiras(float x, float y, float z);
            /**
            * @brief Draw the thystame entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void thystame(float x, float y, float z);
            /**
            * @brief Draw the egg entity
            * @param x The x position of the entity
            * @param y The y position of the entity
            * @param z The z position of the entity
            */
            void egg(float x, float y, float z);
    };
}

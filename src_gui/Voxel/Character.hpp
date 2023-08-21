/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Character
*/

#pragma once

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "VoxColor.hpp"

namespace Voxel {
        class Character : public Entity {
        public:
            Character();
            Character(Model model, std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> broadcast, std::shared_ptr<Entity> incantation);
            Character(std::string modelPath, std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> broadcast, std::shared_ptr<Entity> incantation);
            ~Character();

            /**
            * @brief Draw the character
            * @param position The position of the character
            * @param broadcastType The type of broadcast
            * @param orientation The orientation of the character
            * @param color The color of the character's team
            */
            void draw (Vector3 &position, BroadcastType broadcastType, std::vector<int> orientation, VoxColor &color);
            /**
            * @brief Unload the character's models
            */
            void unloadModels();
        private:
            std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> _broadcast;
            std::shared_ptr<Entity> _incantation;
            std::vector<Model> _models;
    };
}

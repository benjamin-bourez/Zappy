/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxTexture
*/

#pragma once

#include "Voxel.hpp"

#include <string>
#include <unordered_map>

namespace Voxel {
    class VoxTexture {
        public:
            VoxTexture();
            VoxTexture(std::string VoxTexture);            
            ~VoxTexture();

            /**
            * @brief Get the texture
            * @return The texture
            */
            Texture2D getVoxTexture() const;
            /**
            * @brief Draw the texture
            * @param x The x position
            * @param y The y position
            * @param state The state of the texture
            * @param scale The scale of the texture
            */
            void draw(float x, float y, int state, float scale);
            /**
            * @brief Draw the texture
            * @param position The position of the texture
            * @param state The state of the texture
            * @param scale The scale of the texture
            */
            void draw(Vector2 &position, int state, float scale);
            /**
            * @brief Unload the texture
            */
            void unload();
        private:
            Texture2D _VoxTexture;
            std::unordered_map<int, Rectangle> _rects;
    };
}
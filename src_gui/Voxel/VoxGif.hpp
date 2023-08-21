/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxGif
*/

#pragma once

#include "Voxel.hpp"

#include <string>

namespace Voxel {
    class VoxGif {
        public:
            VoxGif();
            VoxGif(std::string VoxGif);
            ~VoxGif();

            /**
            * @brief Get the gif
            * @return The gif
            */
            Texture2D getGif() const;
            /**
            * @brief Draw the gif
            */
            void draw();
            /**
            * @brief Unload the gif
            */
            void unload();
        protected:
        private:
            Image _gif;
            Texture2D _gifTexture;
            unsigned int _nextFrameDataOffset;
            int _gifFrames;
            int _currentFrame;
            int _frameCount;
    };
}

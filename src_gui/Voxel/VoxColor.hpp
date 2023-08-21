/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxColor
*/

#pragma once

#include <vector>

namespace Voxel {
    class VoxColor {
        public:
            VoxColor();
            ~VoxColor();

            /**
            * @brief Set a new color
            * @param spectrumSize The size of the spectrum
            * @param teamNbr The number of the team
            */
            void newColor(int spectrumSize, int teamNbr);
            /**
            * @brief Get the color
            * @return The color
            */
            std::vector<unsigned char> getColor();
        protected:
        private:
            unsigned char r;
            unsigned char g;
            unsigned char b;
    };
}

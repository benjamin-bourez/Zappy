/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Music
*/

#pragma once

#include "Voxel.hpp"

#include <string>

namespace Voxel {
    class VoxMusic {
        public:
            VoxMusic();
            VoxMusic(std::string path);
            ~VoxMusic();

            /**
            * @brief Load the music
            * @param path The path of the music
            */
            void load(std::string path);
            /**
            * @brief Update the music
            */
            void update();
            /**
            * @brief Pause the music
            */
            void pause();
            /**
            * @brief Restart the music
            */
            void restart();
            /**
            * @brief Stop the music
            */
            void stop();
            /**
            * @brief Set the volume of the music
            * @param volume The volume
            */
            void setVolume(float volume);
        protected:
        private:
            Music _music;
            bool _pause;
            bool _stop;
            bool _init;
    };
}

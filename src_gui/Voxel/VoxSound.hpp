/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxSound
*/

#pragma once

#include "Voxel.hpp"

#include <string>
#include <vector>

namespace Voxel {
    class VoxSound {
        public:
            VoxSound();
            VoxSound(std::string path);
            ~VoxSound();

            /**
            * @brief Load the sound
            * @param path The path of the sound
            */
            void load(std::string path);
            /**
            * @brief Play the sound
            */
            void play();
            /**
            * @brief Stop the sound
            */
            void stop();
            /**
            * @brief Pause the sound
            */
            void pause();
            /**
            * @brief Restart the sound
            */
            void restart();
            /**
            * @brief Set the volume of the sound
            * @param volume The volume
            */
            void setVolume(float volume);
            /**
            * @brief Check if the sound is playing
            * @return True if the sound is playing, false otherwise
            */
            bool isSoundPlaying();
        protected:
        private:
            std::vector<Sound> _sound;
            bool _init;
    };
}

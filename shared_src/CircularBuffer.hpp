/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CircularBuffer
*/

#pragma once

#include <iostream>

namespace Zappy
{
    class CircularBuffer {
        public:
            /**
             * @brief Construct a new Circular Buffer object
            */
            CircularBuffer();
            /**
             * @brief Destroy the Circular Buffer object
            */
            ~CircularBuffer();
            /**
             * @brief Append to buffer
             * @param str
             * @return void
            */
            void append(std::string str);
            /**
             * @brief Get the Buffer object
             * @return std::string
            */
            std::string getBuffer() const;
            /**
             * @brief Clear the buffer
             * @return void
            */
            void clearBuffer();
            /**
             * @brief Get the Command object
             * @return std::string
            */
            std::string getCommand();

        protected:
        private:
            std::string _buffer;
    };
} // namespace Zappy

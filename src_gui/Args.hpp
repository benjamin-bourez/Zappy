/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-quentin.challon
** File description:
** Args
*/

#pragma once

#include <iostream>
#include <cstdlib>
#include <regex>

namespace Zappy::GUI
{
    class Args {
        public:
            /**
             * @brief Construct a new Args object
            */
            Args();
            /**
             * @brief Destroy the Args object
            */
            ~Args();
            /**
             * @brief Get the Port object
             * @return int
            */
            int getPort() const;
            /**
             * @brief Get the Ip object
             * @return std::string
            */
            std::string getIp() const;
            /**
             * @brief Set the Port object
             * @param port
             * @return void
            */
            void setPort(int port);
            /**
             * @brief Get the Mute object
            */
            bool getMute() const;
            /**
             * @brief Set the Ip object
             * @param ip
             * @return void
            */
            void setIp(std::string ip);
            /**
             * @brief Set the mute object
            */
            void setMute();
            /**
             * @brief Set the Args object
             * @param ac
             * @param av
             * @return 1 if -help, 85 if error, 0 if ok
            */
            int setArgs(int ac, char **av);

        protected:
        private:
            int _port;
            std::string _ip;
            bool _mute;
    };
} // namespace Zappy


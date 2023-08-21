/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Client
*/

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <fcntl.h>
#include <string.h>
#include <memory>
#include "CircularBuffer.hpp"

namespace Zappy
{
    class Client {
        public:
            /**
             * @brief Construct a new Client object
             * @param ip
             * @param port
            */
            Client(std::string ip, int port);
            /**
             * @brief Destroy the Client object
            */
            ~Client();
            /**
             * @brief Connect to server
             * @return 84 if error, 0 if ok
            */
            int connectToServer();
            /**
             * @brief Send to server
             * @param str
             * @return number of bytes sent
            */
            int sendToServer(std::string str);
            /**
             * @brief Receive from server
             * @return 84 if error, 0 if ok
            */
            int receiveFromServer();
            /**
             * @brief Close the socket
            */
            void closeSocket();
            /**
             * @brief Get the Buffer object
             * @return std::string
            */
            std::string getCommand();
            /**
             * @brief Get the Socket object
             * @return int
            */
            int getSocket() const;

        protected:
        private:
            std::string _ip;
            int _socket;
            int _port;
            int _valread;
            int _client_fd;
            struct sockaddr_in _serv_addr;
            std::string _buffer;
            std::shared_ptr<CircularBuffer> _cb;
            fd_set _readfds;
    };
} // namespace Zappy

int signalMemory(int flag, int value);

/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageAI
*/

#pragma once

#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <regex>
#include <algorithm>
#include <chrono>

#include "../shared_src/Client.hpp"
#include "Enums.hpp"
#include "Agent.hpp"
#include "UtilsAI.hpp"

namespace Zappy::AI {

    class Agent;
    class ManageAI {
        public:
            ManageAI(int port, std::string team_name, std::string ip);
            ~ManageAI();
            /**
             * @brief This function will run the client.
             * 
             * @return true 
             * @return false 
             */
            int runClient(std::shared_ptr<Zappy::Client> client);
            /**
             * @brief This function will calculate the time unit.
             * 
             * @return float 
             */
            float calculTimeFrequency();
        protected:
        private:
            void verifyMatching(const std::string command);
            /**
             * @brief This function will verify matching for xy command.
             * 
             * @param command 
             */
            void verifyMatchingXY(const std::string& command);
            /**
             * @brief This function will verify matching for CL command.
             * 
             * @param command 
             */
            void verifyMatchingCL(const std::string& command);
            /**
             * @brief This function will verify matching for de command.
             * 
             * @param command
             */
            void verifyMatchingDE(const std::string &command);
            /**
             * @brief This function will process the command WELCOME.
             * 
             * @param command 
             * @return std::string 
             */
            void verifyMatchingWE(const std::string &command);
            /**
             * @brief This function will process the command WELCOME.
             * 
             * @param command 
             * @return std::string 
             */
            std::string processCommandWelcome(const std::string& command);
            /**
             * @brief This function will process the command "X Y\n".
             * 
             * @param command 
             * @return std::string 
             */
            std::string processCommandXY(const std::string& command);
            /**
             * @brief This function will process the command "dead".
             * 
             */
            std::string processCommandDead(const std::string& command);
            /**
             * @brief This function will process the command "CL".
             * 
             */
            std::string processCommandClientNum(const std::string& command);

            /**
             * @brief The port of the server.
             * 
             */
            int _port;
            /**
             * @brief The team name.
             * 
             */
            std::string _team_name;
            /**
             * @brief The ip of the server.
             * 
             */
            std::string _ip;
            /**
             * @brief The client.
             * 
             */
            std::shared_ptr<Zappy::Client> _client;
            /**
             * @brief The command handlers.
             * 
             */
            std::map<std::string, std::string (ManageAI::*)(const std::string&)> _commandHandlers;
            /**
             * @brief AI Agent.
             * 
             */
            std::unique_ptr<Agent> _agent;
            /**
             * @brief Authorization for send messages to the server.
             * 
             */
            bool _canSend;
            bool _dead;
            int _unusedSlots;
            int _x;
            int _y;
            float _time_unit;
    };
}


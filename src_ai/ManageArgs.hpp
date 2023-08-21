/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageArgs
*/

#pragma once

#include <iostream>
#include <vector>

namespace Zappy {
    namespace AI {
        class ManageArgs {
            public:
                ManageArgs(int argc, std::vector<std::string> argv);
                ~ManageArgs();
                /**
                 * @brief 
                 * This function will check if the arguments are valid
                 * @return true if the arguments are valid and false if not
                */
                bool checkArgs();
                /**
                 * @brief 
                 * This function will display the help
                */
                void displayHelp();
                /**
                 * @brief 
                 * This function will return the port
                 * @return the port
                */
                int getPort() const { return _port; };
                /**
                 * @brief 
                 * This function will return the team name
                 * @return the team name
                */
                std::string getTeamName() const { return _team_name; };
                /**
                 * @brief 
                 * This function will return the machine name
                 * @return the machine name
                */
                std::string getMachineName() const { return _machine_name; };
                /**
                 * @brief 
                 * This function will return the launch code
                 * @return the launch code
                 */
                int getLaunchCode() const { return _launch_code; };
                /**
                 * @brief 
                 * This function will set the machine name
                 * @param machine_name the new machine name
                */
                void setMachineName(std::string machine_name) { _machine_name = machine_name; };
            protected:
            private:
                /**
                 * @brief 
                 * The number of arguments
                */
                int _argc;
                /**
                 * @brief 
                 * The arguments
                */
                std::vector<std::string> _argv;
                /**
                 * @brief 
                 * The launch codes are :
                 * 0 : basic start
                 * 1 : -help
                 * 2 : with args
                 * 3 : invalid
                */
                int _launch_code;
                /**
                 * @brief 
                 * The port of the server
                */
                int _port;
                /**
                 * @brief 
                 * The name of the team
                */
                std::string _team_name = "default";
                /**
                 * @brief 
                 * The name of the machine
                */
                std::string _machine_name = "localhost";
        };
    }
}

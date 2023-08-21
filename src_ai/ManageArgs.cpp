/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageArgs
*/

#include "ManageArgs.hpp"

namespace Zappy::AI {
    ManageArgs::ManageArgs(int argc, std::vector<std::string> argv)
    {
        _argc = argc;
        _argv = argv;
        _launch_code = 0;
        _port = 4242;
        _team_name = "default";
        _machine_name = "localhost";
    }

    ManageArgs::~ManageArgs()
    {
    }

    bool ManageArgs::checkArgs()
    {
        if (_argc == 2 && _argv[1] == "-help") {
            displayHelp();
            _launch_code = 1;
            return true;
        } else if (_argc == 1) {
            std::cout << "Default launch:" << std::endl;
            _launch_code = 0;
            return true;
        } else if (_argc < 3 || _argc > 7) {
            _launch_code = 3;
            throw std::invalid_argument("Invalid number of arguments");
        }
        //Make possible to use every arguments in any order
        for (int i = 1; i < _argc; ++i) {
            if (_argv[i] == "-p" && i + 1 < _argc) {
                try {
                    _port = std::stoi(_argv[i + 1]);
                } catch (std::exception &e) {
                    std::cerr << "Invalid port" << std::endl;
                    throw std::invalid_argument("Invalid arguments used");
                }
                if (_port < 1024 || _port > 65535)
                    throw std::invalid_argument("Port must be between 1024 an 65535");
            } else if (_argv[i] == "-n" && i + 1 < _argc) {
                _team_name = _argv[i + 1];
            } else if (_argv[i] == "-h" && i + 1 < _argc) {
                _machine_name = _argv[i + 1];
            }
            _launch_code = 2;
        }
        if (_launch_code == 2)
            return true;
        _launch_code = 3;
        return false;
    }

    void ManageArgs::displayHelp()
    {
        std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
        std::cout << "\tport\tis the port number" << std::endl;
        std::cout << "\tname\tis the name of the team" << std::endl;
        std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
    }
}

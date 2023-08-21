/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-quentin.challon
** File description:
** Args
*/

#include "Args.hpp"

using namespace Zappy::GUI;

Args::Args()
{
    _port = 4242;
    _ip = "127.0.0.1";
    _mute = false;
}

Args::~Args()
{
}

int Args::getPort() const
{
    return _port;
}

std::string Args::getIp() const
{
    return _ip;
}

bool Args::getMute() const
{
    return _mute;
}

void Args::setPort(int port)
{
    _port = port;
}

void Args::setIp(std::string ip)
{
    _ip = ip;
}

void Args::setMute()
{
    _mute = true;
}

int Args::setArgs(int ac, char **av)
{
    std::string port = "4242";
    std::string machine = "localhost";

    for (int i = 1; i < ac; ++i) {
        if (std::string(av[i]) == "-help") {
            std::cout << "USAGE: " << av[0] << " -p port -h machine [-m]" << std::endl;
            std::cout << "\tport\tis the port number" << std::endl;
            std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
            std::cout << "\tm\tif present, mute the gui" << std::endl;
            return 1;
        }
    }
    for (int i = 1; i < ac; ++i) {
        if (std::string(av[i]) == "-p" && i + 1 < ac) {
            port = av[i + 1];
        } else if (std::string(av[i]) == "-h" && i + 1 < ac) {
            machine = av[i + 1];
        } else if (std::string(av[i]) == "-m") {
            setMute();
        }
    }
    if (port.empty()) {
        std::cerr << "Erreur : le numéro de port (-p) doit être spécifié." << std::endl;
        return 85;
    }
    setPort(std::stoi(port));
    setIp(machine);
    if (getPort() < 0 || getPort() > 65535) {
        std::cerr << "Erreur : le numéro de port doit être compris entre 0 et 65535." << std::endl;
        return 85;
    }
    if (getIp().empty()) {
        std::cerr << "Erreur : l'adresse IP (-h) doit être spécifiée." << std::endl;
        return 85;
    }
    if (getIp() == "localhost")
        setIp("127.0.0.1");
    if (!std::regex_match(getIp(), std::regex("^\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b$"))) {
        std::cerr << "Erreur : l'adresse IP n'est pas valide." << std::endl;
        return 85;
    }
    return 0;
}

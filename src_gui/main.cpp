/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-quentin.challon
** File description:
** Main
*/

#include <iostream>
#include "Args.hpp"
#include "../shared_src/Client.hpp"
#include "Core.hpp"

using namespace Zappy::GUI;

static void signalHandler(int signum)
{
    if (signum == SIGINT) {
        signalMemory(1, 1);
        fcntl(1, F_SETFL, fcntl(1, F_GETFL, 0) | O_NONBLOCK);
    }
}

int main(int ac, char **av)
{
    Args args;
    Core core;

    signal(SIGINT, signalHandler);
    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    Zappy::Client client(args.getIp(), args.getPort());
    if (client.connectToServer() == 84) {
        core.unloadUponServerMissing();
        return 84;
    }
    std::cout << "Connected to server" << std::endl;
    core.setArgs(std::make_shared<Args>(args));
    core.setClient(std::make_shared<Zappy::Client>(client));
    core.run();
    return 0;
}

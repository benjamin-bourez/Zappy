/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main
*/

#include "ManageArgs.hpp"
#include "ManageAI.hpp"
#include "../shared_src/Client.hpp"

static void signalHandler(int signum)
{
    if (signum == SIGINT) {
        signalMemory(1, 1);
        fcntl(1, F_SETFL, fcntl(1, F_GETFL, 0) | O_NONBLOCK);
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);
    std::vector <std::string> args;
    
    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);
    Zappy::AI::ManageArgs manage_args(argc, args);
    try {
        if (manage_args.checkArgs() == false || manage_args.getLaunchCode() == 3)
            return 84;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    if (manage_args.getMachineName() == "localhost")
        manage_args.setMachineName("127.0.0.1");
    if (manage_args.getLaunchCode() == 1)
        return 0;
    std::cout << "Port: " << manage_args.getPort() << std::endl;
    std::cout << "Team name: " << manage_args.getTeamName() << std::endl;
    std::cout << "Machine name: " << manage_args.getMachineName() << std::endl;
    Zappy::AI::ManageAI manage_ai(manage_args.getPort(), manage_args.getTeamName(), manage_args.getMachineName());
    std::shared_ptr<Zappy::Client> client = std::make_shared<Zappy::Client>(manage_args.getMachineName(), manage_args.getPort());
    try {
        return manage_ai.runClient(client);
    } catch (std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return 84;
    }
}
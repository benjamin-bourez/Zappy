/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Client
*/

#include "../shared_src/Client.hpp"

using namespace Zappy;

int signalMemory(int flag, int value)
{
    static int status = 0;

    if (flag == 1)
        status = value;
    return (status);
}

Client::Client(std::string ip, int port)
{
    _ip = ip;
    _port = port;
    _cb = std::make_shared<CircularBuffer>();
    _socket = 0;
    _valread = 0;
    _client_fd = 0;
}

Client::~Client()
{
}

int Client::connectToServer()
{
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return (84);
    }
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(_port);
    if (inet_pton(AF_INET, _ip.c_str(), &_serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return (84);
    }
    if (connect(_socket, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return (84);
    }
    fcntl(_socket, F_SETFL, O_NONBLOCK);
    return (0);
}

int Client::sendToServer(std::string str)
{
    return dprintf(_socket, "%s", str.c_str());
}

int Client::receiveFromServer()
{
    char buffer[1024] = "\0";

    _valread = read(_socket, buffer, 1024);
    if (_valread == 0)
        return (84);
    buffer[_valread] = '\0';
    _cb->append(buffer);
    return (0);
}

void Client::closeSocket()
{
    close(_socket);
}

std::string Client::getCommand()
{
    return _cb->getCommand();
}

int Client::getSocket() const
{
    return _socket;
}

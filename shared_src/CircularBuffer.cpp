/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CircularBuffer
*/

#include "CircularBuffer.hpp"

namespace Zappy
{
    CircularBuffer::CircularBuffer()
    {
        _buffer = "";
    }

    CircularBuffer::~CircularBuffer()
    {
    }

    void CircularBuffer::append(std::string str)
    {
        _buffer += str;
    }

    std::string CircularBuffer::getBuffer() const
    {
        return _buffer;
    }

    void CircularBuffer::clearBuffer()
    {
        _buffer.clear();
    }

    std::string CircularBuffer::getCommand()
    {
        std::string command;
        std::size_t pos = 0;

        if (_buffer.empty())
            return "";
        pos = _buffer.find("\n");
        if (pos == std::string::npos)
            return "";
        command = _buffer.substr(0, pos);
        _buffer.erase(0, pos + 1);
        _buffer.append("\0");
        return command;
    }
}

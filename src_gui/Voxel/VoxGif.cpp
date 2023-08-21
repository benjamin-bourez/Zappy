/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxGif
*/

#include "VoxGif.hpp"

#include <iostream>

using namespace Voxel;

Texture2D VoxGif::getGif() const
{
    return _gifTexture;
}

void VoxGif::unload()
{
    UnloadTexture(_gifTexture);
    UnloadImage(_gif);
}

void VoxGif::draw()
{
    _frameCount++;
    if (_frameCount >= 2) {
        _currentFrame++;
        if (_currentFrame >= _gifFrames)
            _currentFrame = 0;
        _nextFrameDataOffset = _gif.width * _gif.height * 4 * _currentFrame;
        UpdateTexture(_gifTexture, ((unsigned char *)_gif.data) + _nextFrameDataOffset);
        _frameCount = 0;
    }
    DrawTexture(_gifTexture, GetScreenWidth() / 2 - _gifTexture.width / 2, 80, WHITE); 
}

VoxGif::VoxGif()
{
}

VoxGif::VoxGif(std::string VoxGif)
{
    _gifFrames = 0;
    _gif = LoadImageAnim(VoxGif.c_str(), &_gifFrames);
    _gifTexture = LoadTextureFromImage(_gif);
    _nextFrameDataOffset = 0;
    _currentFrame = 0;
    _frameCount = 0;
}

VoxGif::~VoxGif()
{
}

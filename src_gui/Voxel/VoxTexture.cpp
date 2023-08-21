/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxTexture
*/

#include "VoxTexture.hpp"

using namespace Voxel;

Texture2D VoxTexture::getVoxTexture() const
{
    return _VoxTexture;
}

void VoxTexture::unload()
{
    UnloadTexture(_VoxTexture);
}

void VoxTexture::draw(float x, float y, int state, float scale)
{
    if (_rects.find(state) == _rects.end())
        DrawTextureEx(_VoxTexture, Vector2{x, y}, 0, scale, WHITE);
    else
        DrawTexturePro(_VoxTexture, _rects[state], Rectangle{x, y, _rects[state].width * scale, _rects[state].height * scale}, Vector2{0, 0}, 0, WHITE);
}

void VoxTexture::draw(Vector2 &position, int state, float scale)
{
    if (_rects.find(state) == _rects.end())
        DrawTextureEx(_VoxTexture, position, 0, scale, WHITE);
    else
        DrawTexturePro(_VoxTexture, _rects[state], Rectangle{position.x, position.y, _rects[state].width * scale, _rects[state].height * scale}, Vector2{0, 0}, 0, WHITE);
}

VoxTexture::VoxTexture()
{
    _rects = {
        {0, Rectangle{0, 0, 128, 128}},
        {1, Rectangle{128, 0, 128, 128}},
        {2, Rectangle{0, 128, 128, 128}},
    };
}

VoxTexture::VoxTexture(std::string VoxTexture)
{
    _VoxTexture = LoadTexture(VoxTexture.c_str());
    _rects = {
        {0, Rectangle{0, 0, 128, 128}},
        {1, Rectangle{128, 0, 128, 128}},
        {2, Rectangle{0, 128, 128, 128}},
    };
}

VoxTexture::~VoxTexture()
{
}

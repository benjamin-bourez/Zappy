/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxColor
*/

#include "VoxColor.hpp"

#include <iostream>

using namespace Voxel;

std::vector<unsigned char> VoxColor::getColor()
{
    return {r, g, b};
}

void VoxColor::newColor(int spectrumSize, int teamNbr)
{
    int spectrum = 255 / spectrumSize;
    int color = spectrum * teamNbr;

    if (color > 255)
        color = 255;
    if (color < 0)
        color = 0;
    r = 255;
    g = 256 - color;
    b = color;
}

VoxColor::VoxColor()
{
    r = 255;
    g = 255;
    b = 255;
}

VoxColor::~VoxColor()
{
}

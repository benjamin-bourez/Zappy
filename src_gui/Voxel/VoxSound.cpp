/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxSound
*/

#include "VoxSound.hpp"

#include <iostream>

using namespace Voxel;

bool VoxSound::isSoundPlaying()
{
    if (!_init)
        return false;
    for (auto sound : _sound)
        if (IsSoundPlaying(sound))
            return true;
    return false;
}

void VoxSound::setVolume(float volume)
{
    if (!_init)
        return;
    for (auto sound : _sound)
        SetSoundVolume(sound, volume);
}

void VoxSound::load(std::string path)
{
    _sound.push_back(LoadSound(path.c_str()));
    _init = true;
}

void VoxSound::play()
{
    if (!_init)
        return;
    PlaySound(_sound[rand() % _sound.size()]);
}

void VoxSound::stop()
{
    if (!_init)
        return;
    for (auto sound : _sound)
        StopSound(sound);
}

void VoxSound::pause()
{
    if (!_init)
        return;
    for (auto sound : _sound)
        PauseSound(sound);
}

void VoxSound::restart()
{
    if (!_init)
        return;
    for (auto sound : _sound) {
        StopSound(sound);
        PlaySound(sound);
    }
}

VoxSound::VoxSound(std::string path)
{
    _init = false;
    load(path);
}

VoxSound::VoxSound()
{
    _init = false;
}

VoxSound::~VoxSound()
{
    for (auto sound : _sound)
        UnloadSound(sound);
}

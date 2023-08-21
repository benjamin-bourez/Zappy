/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxMusic
*/

#include "VoxMusic.hpp"

using namespace Voxel;

void VoxMusic::setVolume(float volume)
{
    if (!_init)
        return;
    SetMusicVolume(_music, volume);
}

void VoxMusic::load(std::string path)
{
    if (_init)
        return;
    _music = LoadMusicStream(path.c_str());
    PlayMusicStream(_music);
    _init = true;
}

void VoxMusic::update()
{
    if (_stop || !_init)
        return;
    UpdateMusicStream(_music);
}

void VoxMusic::pause()
{
    if (_stop || !_init)
        return;
    if (_pause)
        ResumeMusicStream(_music);
    else
        PauseMusicStream(_music);
    _pause = !_pause;
}

void VoxMusic::restart()
{
    if (_stop || !_init)
        return;
    StopMusicStream(_music);
    PlayMusicStream(_music);
}

void VoxMusic::stop()
{
    StopMusicStream(_music);
    CloseAudioDevice();
    _stop = true;
}

VoxMusic::VoxMusic()
{
    InitAudioDevice();
    _init = false;
    _pause = false;
    _stop = false;
}

VoxMusic::VoxMusic(std::string path)
{
    InitAudioDevice();
    _init = false;
    _pause = false;
    _stop = false;
    load(path);
}

VoxMusic::~VoxMusic()
{
    StopMusicStream(_music);
    UnloadMusicStream(_music);
    CloseAudioDevice();
}

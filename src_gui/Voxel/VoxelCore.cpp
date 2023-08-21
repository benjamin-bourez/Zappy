/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** VoxelCore
*/

#include <iostream>
#include <memory>
#include <vector>

#include "VoxelCore.hpp"

using namespace Voxel;

void VoxelCore::setMute(bool mute)
{
    if (mute) {
        std::cout << "volume : " << 0 << std::endl;
        _window.setVolume(0);
        updateVolume();
    }
}

void VoxelCore::incantationEnd(int x, int y)
{
    _window.incantationEnd(x, y);
    if (_incantation > 0)
        _incantation -= 1;
}

void VoxelCore::incantationStart(std::vector<std::string> id)
{
    _window.incantationStart(id);
    _incantation += 1;
}

int VoxelCore::getTimeUnit() const
{
    return _window.getTimeUnit();
}

void VoxelCore::resetPosition()
{
    _camera.resetPosition();
    _window.disableCursor();
}

void VoxelCore::setLevelUp(bool levelUp)
{
    _levelUp = levelUp;
}

bool VoxelCore::shouldStart()
{
    return _window.shouldStart();
}

void VoxelCore::endGame(std::string teamName)
{
    _window.endGame(teamName);
    _win = true;
}

void VoxelCore::playerDeath(int id)
{
    _window.playerDeath(id);
    _dead = true;
}

void VoxelCore::resourceCollect(int id, int resource)
{
    _window.resourceCollect(id, resource);
}

void VoxelCore::resourceDrop(int id, int resource)
{
    _window.resourceDrop(id, resource);
}

void VoxelCore::setPlayerBroadcast(int id)
{
    _window.setPlayerBroadcast(id);
    _broadcast = true;
}

void VoxelCore::expulse(int id)
{
   _window.expulse(id);
    _eject = true;
}

void VoxelCore::setCameraPosition(float x, float y, float z)
{
    _camera.setPosition(x, y, z);
}

void VoxelCore::unloadModels()
{
    _scene.unloadModels();
}

void VoxelCore::addEgg(int x, int y, int playerId, int id)
{
    _window.addEgg(x, y, playerId, id);
    _egglaid = true;
}

void VoxelCore::eggConnection(int id)
{
    _window.eggConnection(id);
    _eggremoved = true;
}

void VoxelCore::removeEgg(int id)
{
    _window.removeEgg(id);
    _eggremoved = true;
}

void VoxelCore::setTimeUnit(int timeUnit)
{
    _window.setTimeUnit(timeUnit);
}

void VoxelCore::setPlayerTeam(int id, std::string teamName)
{
    _window.setPlayerTeam(id, teamName);
}

void VoxelCore::setPlayerInventory(int id, std::vector<int> inventory)
{
    _window.setPlayerInventory(id, inventory);
}

void VoxelCore::setPlayerLevel(int id, int level)
{
    _window.setPlayerLevel(id, level);
}

void VoxelCore::setPlayerPosition(int id, int x, int y, int orientation)
{
    _window.setPlayerPosition(id, x, y, orientation);
}

void VoxelCore::addTeamName(std::string teamName)
{
    _scene.addTeamName(teamName);
    _window.addTeamName(teamName);
}

void VoxelCore::setTileContent(int x, int y, std::vector<int> content)
{
    _window.setTileContent(x, y, content);
}

void VoxelCore::setMapSize(int x, int y)
{
    _window.setMapSize(x, y);
    setCameraPosition(0, std::max(x, y), std::max(x, y));
}

bool VoxelCore::shouldStop()
{
    return _window.shouldClose();
}

void VoxelCore::closeWindow()
{
    _window.close();
}

void VoxelCore::updateVolume()
{
    for (auto &sound : _sounds)
        sound.second->setVolume(_window.getVolume());
    _music->setVolume(_window.getVolume());
}

int VoxelCore::mainMenu()
{
    return _window.mainMenu(_scene);
}

void VoxelCore::draw()
{
    _window.draw(_scene, _camera);
}

void VoxelCore::updateAudio()
{
    int idx = 0;
    std::vector<bool *> sounds = {
        &_levelUp,
        &_broadcast,
        &_dead,
        &_egglaid,
        &_eggremoved,
        &_eject,
        &_win,
    };
    static const std::vector<std::string> soundNames = {
        "levelup",
        "broadcast",
        "dead",
        "egglaid",
        "eggremoved",
        "eject",
        "win",
    };

    _music->update();
    if (IsKeyPressed(KEY_SPACE))
        _music->pause();
    if (IsKeyPressed(KEY_R))
        _music->restart();
    for (auto sound : sounds) {
        if (*sound) {
            _sounds[soundNames[idx]]->play();
            *sound = false;
        }
        idx++;
    }
    if (_incantation and _sounds["incantation"]->isSoundPlaying() == false) {
        _sounds["incantation"]->play();
    } else if (!_incantation)
        _sounds["incantation"]->stop();
}

VoxelCore::VoxelCore() : _scene(std::vector<std::string>{
    "assets/voxels/BroadcastSend.vox",
    "assets/voxels/BroadcastReceived.vox",
    "assets/voxels/VoxelCharacter",
    "assets/voxels/VoxelFood.vox",
    "assets/voxels/VoxelCrystalBlue.vox",
    "assets/voxels/VoxelCrystalBrown.vox",
    "assets/voxels/VoxelCrystalGreen.vox",
    "assets/voxels/VoxelCrystalIndigo.vox",
    "assets/voxels/VoxelCrystalPurple.vox",
    "assets/voxels/VoxelCrystalRed.vox",
    "assets/voxels/VoxelTileDirt.vox",
    "assets/voxels/VoxelTileRock.vox",
    "assets/voxels/VoxelEgg.vox",
    "assets/sprites/Start.png",
    "assets/sprites/Options.png",
    "assets/sprites/Left.png",
    "assets/sprites/Right.png",
    "assets/sprites/DirtMap.png",
    "assets/sprites/RockMap.png",
    "assets/voxels/VoxelIncantation.vox",
    "assets/sprites/ZappyLogo.gif",
    "assets/sprites/Exit.png",
})
{
    _levelUp = false;
    _broadcast = false;
    _dead = false;
    _egglaid = false;
    _eggremoved = false;
    _eject = false;
    _win = false;
    _incantation = 0;
    _camera.setPosition(0.0f, 10.0f, 10.0f);
    _camera.setTarget(0.0f, 0.0f, 0.0f);
    _camera.setUp(0.0f, 1.0f, 0.0f);
    _camera.setFOVY(45.0f);
    _camera.setProjection(CAMERA_PERSPECTIVE);
    _music = std::make_unique<VoxMusic>("assets/audio/music.mp3");
    _sounds["levelup"] = std::make_shared<VoxSound>("assets/audio/lvlup.mp3");
    _sounds["broadcast"] = std::make_shared<VoxSound>("assets/audio/broadcast1.mp3");
    _sounds["broadcast"]->load("assets/audio/broadcast2.mp3");
    _sounds["broadcast"]->load("assets/audio/broadcast3.mp3");
    _sounds["broadcast"]->load("assets/audio/broadcast4.mp3");
    _sounds["dead"] = std::make_shared<VoxSound>("assets/audio/dead.mp3");
    _sounds["egglaid"] = std::make_shared<VoxSound>("assets/audio/egglaid.mp3");
    _sounds["eggremoved"] = std::make_shared<VoxSound>("assets/audio/eggcrack.mp3");
    _sounds["eject"] = std::make_shared<VoxSound>("assets/audio/eject.mp3"); 
    _sounds["win"] = std::make_shared<VoxSound>("assets/audio/win.mp3");
    _sounds["incantation"] = std::make_shared<VoxSound>("assets/audio/incantation.mp3");
    Image logo = LoadImage("assets/sprites/logo.png");
    SetWindowIcon(logo);
    UnloadImage(logo);
}

VoxelCore::~VoxelCore()
{
}

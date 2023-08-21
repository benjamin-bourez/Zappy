/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Character
*/

#include "Character.hpp"

using namespace Voxel;

void Character::unloadModels()
{
    for (auto model : _models)
        UnloadModel(model);
    _broadcast.first->unload();
    _broadcast.second->unload();
    _incantation->unload();
}

void Character::draw(Vector3 &position, BroadcastType broadcastType, std::vector<int> parameters, VoxColor &color)
{
    Color col = {color.getColor()[0], color.getColor()[1], color.getColor()[2], 255};

    if (parameters[0] > 0 or parameters[0] < (int)_models.size() + 1)
        DrawModel(_models[parameters[0] - 1], position, 0.25f, WHITE);
    else
        DrawModel(_models[0], position, 0.25f, WHITE);
    position.x += 0.125;
    position.y += 1.15;
    if (broadcastType == SEND) {
        DrawModel(_broadcast.first.get()[0].getModel(), position, 0.1875f, WHITE);
    } else if (broadcastType == RECEIVED) {
        DrawModel(_broadcast.second.get()[0].getModel(), position, 0.1875f, WHITE);
    }
    if (parameters[1] == 1)
        DrawModel(_incantation.get()[0].getModel(), Vector3{position.x, position.y + 0.1f, position.z}, 0.1875f, WHITE);
    position.y -= 1.15;
    position.x -= 0.125;
    for (int i = 0; i < 10; i++)
        DrawCircle3D({position.x + 0.5f, position.y, position.z + 0.5f}, 0.5 - i*0.005, {1, 0, 0}, 90.0f, col);
}

Character::Character()
{
}

Character::Character(Model model, std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> broadcast, std::shared_ptr<Entity> incantation)
{
    _models.push_back(model);
    _broadcast = broadcast;
    _incantation = incantation;
    _type = EntityType::NONE;
}

Character::Character(std::string modelPath, std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> broadcast, std::shared_ptr<Entity> incantation)
{
    _models.push_back(LoadModel((modelPath + "1.vox").c_str()));
    _models.push_back(LoadModel((modelPath + "2.vox").c_str()));
    _models.push_back(LoadModel((modelPath + "3.vox").c_str()));
    _models.push_back(LoadModel((modelPath + "4.vox").c_str()));
    _broadcast = broadcast;
    _type = EntityType::NONE;
    _incantation = incantation;
}

Character::~Character()
{
}

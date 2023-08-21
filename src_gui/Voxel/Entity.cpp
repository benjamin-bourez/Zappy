/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Entity
*/

#include "Entity.hpp"
#include <iostream>

using namespace Voxel;

void Entity::setModel(Model &model)
{
    _model = model;
}

Model Entity::getModel() const
{
    return _model;
}

void Entity::draw(float x, float y, float z, float scale)
{
    if (_type == NONE or _type == TILE)
        DrawModel(_model, {x, y, z}, scale, WHITE);
    else
        (this->*methodPointer[_type])(x, y, z);
}

void Entity::draw(Vector3 &position, float scale)
{
    if (_type == NONE or _type == TILE)
        DrawModel(_model, {position.x, position.y, position.z}, scale, WHITE);
    else
        (this->*methodPointer[_type])(position.x, position.y, position.z);
}

void Entity::setEntityType(EntityType type)
{
    _type = type;
}

EntityType Entity::getEntityType() const
{
    return _type;
}

void Entity::food(float x, float y, float z)
{
    DrawModel(_model, {x + 0.125f, y, z}, 0.062f, WHITE);
}

void Entity::linemate(float x, float y, float z)
{
    DrawModel(_model, {x + 0.625f, y, z}, 0.062f, WHITE);
}

void Entity::deraumere(float x, float y, float z)
{
    DrawModel(_model, {x + 0.125f, y, z + 0.25f}, 0.062f, WHITE);
}

void Entity::sibur(float x, float y, float z)
{
    DrawModel(_model, {x + 0.625f, y, z + 0.25f}, 0.062f, WHITE);
}

void Entity::mendiane(float x, float y, float z)
{
    DrawModel(_model, {x + 0.125f, y, z + 0.5f}, 0.062f, WHITE);
}

void Entity::phiras(float x, float y, float z)
{
    DrawModel(_model, {x + 0.625f, y, z + 0.5f}, 0.062f, WHITE);
}

void Entity::thystame(float x, float y, float z)
{
    DrawModel(_model, {x + 0.125f, y, z + 0.75f}, 0.062f, WHITE);
}

void Entity::egg(float x, float y, float z)
{
    DrawModel(_model, {x + 0.625f, y, z + 0.70f}, 0.062f, WHITE);
}

void Entity::unload()
{
    UnloadModel(_model);
}

Entity::Entity()
{
    _type = NONE;
    methodPointer = {
        {FOOD, &Entity::food},
        {LINEMATE, &Entity::linemate},
        {DERAUMERE, &Entity::deraumere},
        {SIBUR, &Entity::sibur},
        {MENDIANE, &Entity::mendiane},
        {PHIRAS, &Entity::phiras},
        {THYSTAME, &Entity::thystame},
        {EGG, &Entity::egg},
    };
}

Entity::Entity(Model model, EntityType type)
{
    _model = model;
    _type = type;
    methodPointer = {
        {FOOD, &Entity::food},
        {LINEMATE, &Entity::linemate},
        {DERAUMERE, &Entity::deraumere},
        {SIBUR, &Entity::sibur},
        {MENDIANE, &Entity::mendiane},
        {PHIRAS, &Entity::phiras},
        {THYSTAME, &Entity::thystame},
        {EGG, &Entity::egg},
    };
}

Entity::Entity(std::string modelPath, EntityType type)
{
    _model = LoadModel(modelPath.c_str());
    _type = type;
    methodPointer = {
        {FOOD, &Entity::food},
        {LINEMATE, &Entity::linemate},
        {DERAUMERE, &Entity::deraumere},
        {SIBUR, &Entity::sibur},
        {MENDIANE, &Entity::mendiane},
        {PHIRAS, &Entity::phiras},
        {THYSTAME, &Entity::thystame},
        {EGG, &Entity::egg},
    };
}

Entity::Entity(const Voxel::Entity &other)
{
    _model = other._model;
    _type = other._type;
}

Entity::~Entity()
{
}

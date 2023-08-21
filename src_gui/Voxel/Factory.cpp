/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Factory
*/

#include "Factory.hpp"

#include <iostream>

using namespace Voxel;

std::unique_ptr<Voxel::VoxGif> Factory::getGif()
{
    return std::move(_gif);
}

std::unordered_map<int, std::shared_ptr<Voxel::Entity>> Factory::getEntities()
{
    return _entities;
}

std::unique_ptr<Voxel::Character> Factory::getCharacter()
{
    return std::move(_character);
}

std::pair<std::shared_ptr<Voxel::Entity>, std::shared_ptr<Voxel::Entity>> Factory::getTile()
{
    return _tile;
}

std::unordered_map<int, std::shared_ptr<Voxel::VoxTexture>> Factory::getTextures()
{
    return _textures;
}

void Factory::character(std::string modelPath, [[maybe_unused]] int id, [[maybe_unused]] EntityType entityType)
{
    _character = std::make_unique<Character>(modelPath, std::make_pair(_broadcast.first, _broadcast.second), _incantation);
}

void Factory::entity(std::string modelPath, int id, EntityType entityType)
{
    _entities[id] = std::make_unique<Entity>(modelPath, entityType);
}

void Factory::broadcast(std::string modelPath, int id, [[maybe_unused]] EntityType entityType)
{
    if (id == 0)
        _broadcast.first = std::make_shared<Entity>(modelPath, Voxel::EntityType::NONE);
    else
        _broadcast.second = std::make_shared<Entity>(modelPath, Voxel::EntityType::NONE);
}

void Factory::incantation(std::string modelPath, [[maybe_unused]] int id, EntityType entityType)
{
    _incantation = std::make_shared<Entity>(modelPath, entityType);
}

void Factory::tile(std::string modelPath, int id, EntityType entityType)
{
    if (!id)
        _tile.first = std::make_shared<Entity>(modelPath, entityType);
    else
        _tile.second = std::make_shared<Entity>(modelPath, entityType);
}

void Factory::createEntity(std::string modelPath, std::string type, int id, EntityType entityType)
{
    (this->*_entityFactory[type])(modelPath, id, entityType);
}

void Factory::createTexture(std::string modelPath, int id)
{
    _textures[id] = std::make_shared<VoxTexture>(modelPath);
}

void Factory::createGif(std::string modelPath)
{
    _gif = std::make_unique<VoxGif>(modelPath);
}

Factory::Factory()
{
    _entityFactory["broadcast"] = &Factory::broadcast;
    _entityFactory["character"] = &Factory::character;
    _entityFactory["entity"] = &Factory::entity;
    _entityFactory["tile"] = &Factory::tile;
    _entityFactory["incantation"] = &Factory::incantation;
}

Factory::~Factory()
{
}

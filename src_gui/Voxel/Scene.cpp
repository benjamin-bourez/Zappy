/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Scene
*/

#include "Scene.hpp"

#include <iostream>

using namespace Voxel;

void Scene::unloadModels()
{
    _character->unloadModels();
    _tile.first->unload();
    _tile.second->unload();
    _gif->unload();
    for (auto &entity : _entities)
        entity.second->unload();
}

void Scene::addTeamName(std::string teamName)
{
    if (std::find(_teamNames.begin(), _teamNames.end(), teamName) != _teamNames.end())
        _teamNames.push_back(teamName);
}

void Scene::addEntity(int id, Voxel::Entity entity)
{
    _entities[id] = std::make_unique<Voxel::Entity>(entity.getModel(), entity.getEntityType());
}

void Scene::removeEntity(int id)
{
    _entities.erase(id);
}

void Scene::drawTile(int x, int y, int type)
{
    for (int i = -x/2; i < x/2; i++)
        for (int j = -y/2; j < y/2; j++)
            type == 0 ? _tile.first->draw(i, -1, j, 0.25) : _tile.second->draw(i, -1, j, 0.25);
}

void Scene::draw(Vector3 position, std::vector<float> parameters, BroadcastType broadcastType, std::optional<VoxColor> color)
{
    std::vector<int> params = {(int)parameters[1], (int)parameters[2]};

    switch ((int) parameters[0]) {
        case 1:
            drawTile(parameters[1], parameters[2], parameters[3]);
            break;
        case 2:
            _character->draw(position, broadcastType, params, color.value());
            break;
        default:
            if (parameters[3] >= 0 and parameters[3] <= 7)
                _entities[parameters[3]]->draw(position, parameters[1]);
            break;
    }
}

void Scene::display(Vector2 position, int type, int state, float scale)
{
    _textures[type]->draw(position, state, scale);
}

void Scene::displayGif()
{
    _gif->draw();
}

Scene::Scene()
{
}

Scene::Scene(std::vector<std::string> modelsPath)
{
    _factory.createEntity(modelsPath[0], "broadcast", 0, Voxel::EntityType::NONE);
    _factory.createEntity(modelsPath[1], "broadcast", 1, Voxel::EntityType::NONE);
    _factory.createEntity(modelsPath[19], "incantation", 0, Voxel::EntityType::NONE);
    _factory.createEntity(modelsPath[2], "character", 0, Voxel::EntityType::NONE);
    _factory.createEntity(modelsPath[3], "entity", 0, Voxel::EntityType::FOOD);
    _factory.createEntity(modelsPath[4], "entity", 1, Voxel::EntityType::LINEMATE);
    _factory.createEntity(modelsPath[5], "entity", 2, Voxel::EntityType::DERAUMERE);
    _factory.createEntity(modelsPath[6], "entity", 3, Voxel::EntityType::SIBUR);
    _factory.createEntity(modelsPath[7], "entity", 4, Voxel::EntityType::MENDIANE);
    _factory.createEntity(modelsPath[8], "entity", 5, Voxel::EntityType::PHIRAS);
    _factory.createEntity(modelsPath[9], "entity", 6, Voxel::EntityType::THYSTAME);
    _factory.createEntity(modelsPath[10], "tile", 0, Voxel::EntityType::TILE);
    _factory.createEntity(modelsPath[11], "tile", 1, Voxel::EntityType::TILE);
    _factory.createEntity(modelsPath[12], "entity", 7, Voxel::EntityType::EGG);
    _factory.createTexture(modelsPath[13], 0);
    _factory.createTexture(modelsPath[14], 1);
    _factory.createTexture(modelsPath[15], 2);
    _factory.createTexture(modelsPath[16], 3);
    _factory.createTexture(modelsPath[17], 4);
    _factory.createTexture(modelsPath[18], 5);
    _factory.createGif(modelsPath[20]);
    _factory.createTexture(modelsPath[21], 6);
    _character = _factory.getCharacter();
    _entities = _factory.getEntities();
    _tile = _factory.getTile();
    _textures = _factory.getTextures();
    _gif = _factory.getGif();
}

Scene::~Scene()
{
}

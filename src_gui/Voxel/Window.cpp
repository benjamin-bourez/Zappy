/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Window
*/

#include "Window.hpp"

#include <iostream>

using namespace Voxel;

void Window::setVolume(float volume)
{
    _volume = volume;
    for (auto &s : _sliders)
        if (s.option == "Volume")
            s.value = 0;
}

int Window::getIdByTeamName(std::string teamName)
{
    for (int idx = 0; idx < (int)_teamNames.size(); idx++)
        if (_teamNames[idx] == teamName)
            return idx;
    return 0;
}

void Window::incantationEnd(int x, int y)
{
    for (auto &p : _players) {
        if (p.second.x == x && p.second.y == y) {
            p.second.incantation = false;
        }
    }
}

void Window::incantationStart(std::vector<std::string> id)
{
    for (auto &p : _players) {
        for (auto &i : id) {
            if (p.first == std::stoi(i)) {
                p.second.incantation = true;
                break;
            }
        }
    }
}

void Window::disableCursor()
{
    DisableCursor();
    _cursorEnabled = false;
}

void Window::enableCursor()
{
    EnableCursor();
    _cursorEnabled = true;
}

int Window::getTimeUnit() const
{
    return _timeUnit;
}

float Window::getVolume() const
{
    return _volume;
}

bool Window::shouldStart()
{
    return _shouldStart;
}

void Window::addTeamName(std::string teamName)
{
    int idx = 0;

    _teamNames.push_back(teamName);
    for (auto _teamName : _teamNames) {
        VoxColor col;
        col.newColor(_teamNames.size(), idx);
        _teamColors[_teamName] = col;
        _teamSizes.push_back(0);
        idx++;
    }
}

void Window::setTimeUnit(int timeUnit)
{
    for (auto &s : _sliders)
        if (s.option == "Time unit")
            s.value = timeUnit / 1000.0f;
    _timeUnit = timeUnit;
}

void Window::endGame(std::string teamName)
{
    _winningTeam = teamName;
    _endGameStart = std::chrono::system_clock::now();
    _end = true;
}

void Window::playerDeath(int id)
{
    int idx = 0;

    for (auto &p : _players) {
        if (p.first == id) {
            _teamSizes[getIdByTeamName(p.second.team)] -= 1;
            _players.erase(id);
            return;
        }
        idx++;
    }
}

void Window::resourceCollect(int id, int resource)
{
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.inventory[resource] += 1;
            return;
        }
    }
}

void Window::resourceDrop(int id, int resource)
{
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.inventory[resource] -= 1;
            _map.tiles[p.second.y][p.second.x][resource] += 1;
            return;
        }
    }
}

void Window::setPlayerBroadcast(int id)
{
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.broadcastStart = std::chrono::system_clock::now();
            p.second.broadcastType = SEND;
        } else {
            p.second.broadcastStart = std::chrono::system_clock::now();
            p.second.broadcastType = RECEIVED;
        }
    }
}

void Window::expulse(int id)
{
    Voxel::player expulser;

    for (auto &p : _players)
        if (p.first == id)
            expulser = p.second;
    for (auto &p : _players) {
        if (p.first == id or expulser.x != p.second.x or expulser.y != p.second.y)
            continue;
        switch (p.second.direction) {
            case 0:
                p.second.y -= 1;
                break;
            case 1:
                p.second.x += 1;
                break;
            case 2:
                p.second.y += 1;
                break;
            case 3:
                p.second.x -= 1;
                break;
            default:
                break;
        }
    }
}

void Window::addEgg(int x, int y, int playerId, int id)
{
    std::string teamName;

    for (auto &p : _players) {
        if (p.first == playerId) {
            teamName = p.second.team;
            break;
        }
    }
    if (teamName.empty() and abs(playerId) <= _teamNames.size())
        _eggs[id] = egg(x, y, _teamNames[abs(playerId) - 1], id);
    else if (teamName.empty())
        _eggs[id] = egg(x, y, "None", id);
    else
        _eggs[id] = egg(x, y, teamName, id);
}

void Window::eggConnection(int id)
{
    for (auto &e : _eggs) {
        if (e.first == id) {
            player p = player();
            p.id = id;
            p.x = e.second.x;
            p.y = e.second.y;
            p.team = e.second.team;
            p.color = _teamColors[p.team];
            p.direction = 3;
            _players[id] = p;
            _eggs.erase(id);
            _teamSizes[getIdByTeamName(p.team)] += 1;
            break;
        }
    }
}

void Window::removeEgg(int id)
{
    for (auto &e : _eggs) {
        if (e.first == id) {
            _eggs.erase(id);
            break;
        }
    }
}

void Window::setPlayerTeam(int id, std::string teamName)
{
    int idx = 0;

    for (auto &team : _teamNames) {
        if (team == teamName)
            break;
        idx++;
    }
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.team = teamName;
            p.second.color.newColor(_teamNames.size(), idx);
            return;
        }
    }
}

void Window::setPlayerInventory(int id, std::vector<int> inventory)
{
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.inventory = inventory;
            return;
        }
    }
}

void Window::setPlayerLevel(int id, int level)
{
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.level = level;
            return;
        }
    }
}

void Window::setPlayerPosition(int id, int x, int y, int orientation)
{
    for (auto &p : _players) {
        if (p.first == id) {
            p.second.x = x;
            p.second.y = y;
            p.second.direction = orientation;
            return;
        }
    }
    player p = player();
    p.id = id;
    p.x = x;
    p.y = y;
    p.direction = orientation;
    _players[id] = p;
    _teamSizes[getIdByTeamName(p.team)] += 1;
}

void Window::setMap(std::vector<std::vector<std::vector<int>>> tiles)
{
    _map.tiles.clear();
    _map.tiles = tiles;
}

void Window::setMapSize(int x, int y)
{
    _map.x = x;
    _map.y = y;
    for (int i = 0; i < y; i++) {
        _map.tiles.push_back(std::vector<std::vector<int>>());
        for (int j = 0; j < x; j++) {
            _map.tiles[i].push_back(std::vector<int>{0, 0, 0, 0, 0, 0, 0});
        }
    }
}

void Window::setTileContent(int x, int y, std::vector<int> content)
{
    _map.tiles[y][x] = content;
}

bool Window::shouldClose()
{
    return !WindowShouldClose();
}

void Window::drawTile(std::pair<int, int> pos, Scene &scene, std::vector<float> parameters)
{
    int idx = 0;

    if (pos.second > (int) _map.tiles.size() - 1 or pos.first > (int) _map.tiles[pos.second].size() - 1)
        return;
    for (auto &quantity : _map.tiles[pos.second][pos.first]) {
        if (quantity > 0) {
            parameters[3] = idx;
            scene.draw(Vector3{(float)pos.first - _map.x / 2, 0, (float)pos.second - _map.y / 2}, parameters, NO, {});
        }
        idx++;
    }
}

void Window::draw(Scene &scene, Voxel::Camera &camera)
{
    int tmpY = 0;
    std::vector<float> parameters = {1, (float)_map.x, (float)_map.y, (float)_tileType};
    std::chrono::_V2::system_clock::time_point now;
    std::chrono::milliseconds diff;
    std::vector<unsigned char> tmp;

    camera.updateCamera();
    if (IsKeyPressed(KEY_L)) {
        if (_cursorEnabled)
            disableCursor();
        else
            enableCursor();
    }
    for (auto &p : _players) {
        if (p.second.broadcastType == NO)
            continue;
        now = std::chrono::system_clock::now();
        diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - p.second.broadcastStart);
        if (diff.count() > 1000) {
            p.second.broadcastType = NO;
        }
    }
    BeginDrawing();
    ClearBackground(BLUE);
    BeginMode3D(camera.getCamera());
    scene.draw(Vector3{0, 0, 0}, parameters, NO, {});
    parameters[0] = 0;
    parameters[1] = 0.25;
    parameters[2] = 0;
    for (int i = 0; i < _map.y; i++) {
        for (int j = 0; j < _map.x; j++) {
            drawTile(std::make_pair(j, i), scene, parameters);
        }
    }
    parameters[3] = 7;
    for (auto &e : _eggs) {
        scene.draw(Vector3{(float)e.second.x - (_map.x / 2), 0, (float)e.second.y - (_map.y / 2)}, parameters, NO, {});
    }
    parameters[0] = 2;
    parameters[3] = 2;
    for (auto &p : _players) {
        parameters[1] = (float)p.second.direction;
        parameters[2] = (float)p.second.incantation;
        scene.draw(Vector3{(float)p.second.x - (_map.x / 2), 0, (float)p.second.y - (_map.y / 2)}, parameters, p.second.broadcastType, p.second.color);
    }
    EndMode3D();
    for (auto &teamName : _teamNames) {
        tmp = _teamColors[teamName].getColor();
        DrawText((teamName + " - " + std::to_string(_teamSizes[getIdByTeamName(teamName)])).c_str(), 150, 100 + tmpY * 20, 20, Color{tmp[0], tmp[1], tmp[2], 255});
        DrawCircle(130, 100 + tmpY * 20 + 10, 10, Color{tmp[0], tmp[1], tmp[2], 255});
        tmpY++;
    }
    if (!_end) {
        EndDrawing();
        return;
    }
    for (auto &teamName : _teamNames)
        if (teamName == _winningTeam)
            tmp = _teamColors[teamName].getColor();
    DrawText(("Team " + _winningTeam + " won the game !").c_str(), 10, 10, 20, Color{tmp[0], tmp[1], tmp[2], 255});
    diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - _endGameStart);
    if (diff.count() > 10000)
        _end = false;
    EndDrawing();
}

void Window::changeMenu()
{
    if (_menuType == MAIN_MENU) {
        for (int i = 0; i < 4; i++) {
            _buttons[i].displayed = true;
        }
        _buttons[4].displayed = false;
        for (auto &s : _sliders) {
            s.displayed = false;
        }
    } else {
        for (int i = 0; i < 4; i++) {
            _buttons[i].displayed = false;
        }
        _buttons[4].displayed = true;
        for (auto &s : _sliders) {
            s.displayed = true;
        }
    }
}

int Window::mainMenu(Scene &scene)
{
    bool changed = 0;

    _mousePos = GetMousePosition();
    BeginDrawing();
    ClearBackground(Color{0, 168, 254, 255});
    for (auto &btn : _buttons) {
        if (!btn.displayed)
            continue;
        btn.btnAction = false;
        if (CheckCollisionPointRec(_mousePos, btn.rect)) {
            btn.btnState = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 2 : 1;
            btn.btnAction = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        } else
            btn.btnState = 0;
        if (btn.btnAction and btn.startGame)
            _shouldStart = true;
        else if (btn.btnAction and btn.menuType != DEFAULT) {
            _menuType = btn.menuType;
            changeMenu();
        } else if (btn.btnAction and btn.changeMap)
            _tileType = !_tileType;
        else if (btn.btnAction and btn.stop)
            _stop = true;
        scene.display(btn.pos, btn.type, btn.btnState, btn.scale);
    }
    scene.displayGif();
    if (_menuType == MAIN_MENU)
        scene.display({800, 250}, 4 + _tileType, -1, 0.75);
    for (auto &s : _sliders) {
        if (!s.displayed)
            continue;
        s.held = false;
        if (CheckCollisionPointRec(_mousePos, s.rect)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                s.held = true;
                s.value = (_mousePos.x - s.rect.x) / s.rect.width;
                if (s.option == "Volume")
                    changed = 1;
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                s.held = false;
                s.value = (_mousePos.x - s.rect.x) / s.rect.width;
                changed = 1;
            }
            if (changed == 1 and s.option == "Volume")
                _volume = s.value;
            else if (changed and s.option == "Time unit")
                _timeUnit = std::clamp((int)(s.value * 1000), 2, 1000);
        }
        DrawRectangle(s.rect.x, s.rect.y, s.rect.width, s.rect.height, LIGHTGRAY);
        DrawRectangle(s.rect.x, s.rect.y, s.rect.width * s.value, s.rect.height, RED);
        DrawText(s.option.c_str(), s.rect.x + s.rect.width + 20, s.rect.y + 15, 20, BLACK);
        std::string sliderValue = std::to_string(s.option == "Volume" ? s.value : std::clamp((int)(s.value * 1000), 2, 1000));
        sliderValue.erase(sliderValue.find_last_not_of("0") + 1, std::string::npos);
        if (sliderValue.back() == '.')
            sliderValue.pop_back();
        DrawText(sliderValue.c_str(), s.rect.x + s.rect.width * s.value - sliderValue.length() * 5, s.rect.y - s.rect.height / 2, 20, BLACK);
    }
    EndDrawing();
    if (_stop)
        return 2;
    return changed;
}

void Window::close()
{
    CloseWindow();
}

void Window::loadButtons()
{
    button start;
    button option;
    button left;
    button right;
    button back;
    button exit;

    start.startGame = true;
    start.rect = {250, 350, 350, 130};
    start.type = 0;
    start.pos = {100, 100};
    start.scale = 5;
    _buttons.push_back(start);
    option.menuType = MenuType::OPTIONS_MENU;
    option.rect = {250, 520, 350, 130};
    option.type = 1;
    option.pos = {100, 250};
    option.scale = 5;
    _buttons.push_back(option);
    left.changeMap = true;
    left.rect = {950, 850, 190, 78};
    left.type = 2;
    left.pos = {850, 700};
    left.scale = 3;
    _buttons.push_back(left);
    right.changeMap = true;
    right.rect = {1350, 850, 190, 78};
    right.type = 3;
    right.pos = {1250, 700};
    right.scale = 3;
    _buttons.push_back(right);
    back.menuType = MenuType::MAIN_MENU;
    back.rect = {190, 150, 190, 78};
    back.type = 2;
    back.pos = {100, 0};
    back.scale = 3;
    back.displayed = false;
    _buttons.push_back(back);
    exit.rect = {250, 700, 350, 90};
    exit.type = 6;
    exit.pos = {100, 450};
    exit.scale = 5;
    exit.stop = true;
    _buttons.push_back(exit);
}

void Window::loadSliders()
{
    slider volume;
    slider timeUnit;

    volume.pos = {400, 400};
    volume.rect = {400, 400, 200, 50};
    volume.value = 0.5;
    volume.option = "Volume";
    _sliders.push_back(volume);
    timeUnit.pos = {400, 600};
    timeUnit.rect = {400, 600, 200, 50};
    timeUnit.value = 0.5;
    timeUnit.option = "Time unit";
    _sliders.push_back(timeUnit);
}

Window::Window()
{
    _shouldStart = false;
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(1920, 1080, "Zappy Raylib");
    SetTargetFPS(60);
    _tileType = 0;
    _menuType = MAIN_MENU;
    loadButtons();
    loadSliders();
    _cursorEnabled = true;
    _end = false;
    _winningTeam = "";
    _stop = false;
}

Window::~Window()
{
}

slider::slider()
{
    this->pos = {0, 0};
    this->rect = {0, 0, 0, 0};
    this->value = 0;
    this->displayed = false;
    this->held = false;
}

button::button()
{
    this->btnAction = false;
    this->btnState = 0;
    this->changeMap = false;
    this->displayed = true;
    this->menuType = DEFAULT;
    this->startGame = false;
    this->pos = {0, 0};
    this->scale = 1;
    this->stop = false;
}

egg::egg(int x, int y, std::string team, int id)
{
    this->x = x;
    this->y = y;
    this->team = team;
    this->id = id;
}

egg::egg()
{
}

player::player()
{
    broadcastType = NO;
    inventory = std::vector<int>{0, 0, 0, 0, 0, 0, 0};
    x = 0;
    y = 0;
    direction = 0;
    level = 1;
    team = "";
    incantation = false;
}

map::map()
{
}

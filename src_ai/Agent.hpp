/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Agent
*/

#ifndef AGENT_HPP_
#define AGENT_HPP_

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <regex>
#include <uuid/uuid.h>

#include "ManageFood.hpp"
#include "ManageStone.hpp"
#include "Broadcast.hpp"
#include "ManageIncantation.hpp"

namespace Zappy::AI
{

    class ManageFood;
    class ManageStone;
    class Broadcast;
    class ManageIncantation;

    class Agent {
    public:
        /**
         * @brief Construct a new Agent object
         * @param mapSize std::pair<int, int>(width, heigth)
         * @param id id of the agent
         * @param verbose     (default: false)
         */
        Agent(std::pair<int, int> mapSize, int connectNbr, bool verbose);
        ~Agent();

        /**
         * @brief set the inventory of the agent
         * @param inventory
         */
        void setInventory(std::map<Ressource, int> inventory);

        /**
         * @brief set the number of a ressource in the inventory
         * @param r
         * @param nb
         */
        void setRessource(Ressource r, int nb);

        /**
         * @brief set the vision of the agent
         * @param vision
         */
        void setVision(std::vector<std::vector<Ressource>> vision);

        /**
         * @brief set the level of the agent
         * @param level
         */
        void setLevel(int level);
        
        /**
         * @brief set the x position of the agent
         * @param x
         */
        void setX(int x);

        /**
         * @brief set the y position of the agent
         * @param y
         */
        void setY(int y);

        /**
         * @brief set the orientation of the agent
         * @param orientation
         */
        void setOrientation(int orientation);

        /**
         * @brief set the position of the agent
         * @param position
         */
        void setOrientation(std::pair<int, int> orientation);

        /**
         * @brief set the position of the agent
         * @param position
         */
        void setPosition(std::pair<int, int> position);

        /**
         * @brief get the inventory of the agent
         * @return std::map<ressource, int>
         */
        std::map<Ressource, int> getInventory() const;

        /**
         * @brief get the number of a ressource in the inventory
         * @param r
         * @return int
         */
        int getRessource(Ressource r) const;

        /**
         * @brief get the vision of the agent
         * @return std::vector<std::vector<ressource>> 
         * @note the first vector are the square of the vision, the second vector are the ressources in the square
         */
        std::vector<std::vector<Ressource>> getVision() const;

        /**
         * @brief get the level of the agent
         * @return int
         */
        int getLevel() const;

        /**
         * @brief get the x position of the agent
         * @return int
         */
        int getX() const;

        /**
         * @brief get the y position of the agent
         * @return int
         */
        int getY() const;

        /**
         * @brief get the position of the agent
         * @return std::pair<int, int>
         */
        std::pair<int, int> getPosition() const;

        /**
         * @brief get the orientation of the agent
         * @return enum {NORTH, EAST, SOUTH, WEST}
         */
        int getOrientation() const;

        /**
         * @brief get the id of the agent
         * @return int
         */
        std::string getId() const;

        /**
         * @brief get hunger
         * @return bool
         */
        bool getHunger() const;

        /**
         * @brief get the lastcommand of the agent
         * @return std::string
         */
        std::string getLastCommand() const;

        /**
         * @brief update the Agent, and return the message to send to the server
         * @param message received from the server
         * @return std::string
         */
        std::string update(std::string &message);

        /**
         * @brief used to make the next command to send to the server
         * @param enum {FORWARD, RIGHT, LEFT, LOOK, INVENTORY, BROADCAST, CONNECT_NBR, FORK, EJECT, TAKE, SET, INCANTATION, UNKNOWN}
         * @param message parameter of the command
         * @return std::string command to send to the server
         */
        std::string askServer(Commands command, std::string message = "");

        /**
         * @brief interpret the answer of the server
         * @param message message received from the server
         * @return true if message is a broadcast
         */
        bool interpretAnswer(std::string &message);

        /**
         * @brief execute the first command in the buffer of commands
         */
        std::string executeBuffer();

        std::vector<std::pair<Commands, std::string>> setAllRessources();

        bool forward(std::string &message);
        bool right(std::string &message);
        bool left(std::string &message);
        bool look(std::string &message);
        bool inventory(std::string &message);
        bool broadcast(std::string &message);
        bool connectNbr(std::string &message);
        bool fork(std::string &message);
        bool eject(std::string &message);
        bool take(std::string &message);
        bool set(std::string &message);
        bool incantation(std::string &message);

        void addBroadcastCommand(std::string &message);
        bool popBroadcastCommand(void);

        bool manageBroadcast(void);
        void broadcastCommands(std::string &message);

        void sendId();
        void receiveId(std::string broadcast);
        void askId(void);
        bool responseToIncantate(std::string broadcast);
        void receiveIncantate(std::string broadcast);
        
    protected:
    private:
        std::map<Ressource, int> _inventory;
        std::vector<std::vector<Ressource>> _vision;
        int _level;
        std::pair<int, int> _position;
        std::pair<int, int> _orientation;
        const std::string _team;
        std::string _id;
        int _connectNbr;
        bool _verbose;
        std::pair<int, int> _mapSize;
        std::vector<std::string> _ressources; // pair with enum 'ressource' to get the ressource as a string
        std::map<Commands, bool (Agent::*)(std::string &)> _commandsFuncs;
        std::vector<std::string> _commandsStr; // pair with enum 'commands' to get the corresponding command as a string to send
        std::pair<Commands, std::string> _lastCommand; // last command sent to the server for context purposes
        Ressource _lastRessource; // last ressource taken or set for context purposes
        std::shared_ptr<ManageFood> _foodManager;
        std::shared_ptr<ManageStone> _stoneManager;
        std::shared_ptr<Broadcast> _broadcast;
        std::shared_ptr<ManageIncantation> _incantationManager;
        int _lastLook;
        int _lastInv;
        bool _isHungry;
        bool _isIncantating;

        /* Broadcast stuff */

        int _waitForId;
        bool _sended_id;
        IncantationStatus _incantation;
        int _needed_players;
        int _player_ready;
        bool _previous_going;
        bool _follow_incantator;
        std::vector<std::string> _incanterId;
        bool _another_incantation;
        int _tick_other_incantation;

        bool _waiting_for_player;
        bool _following_player;
        std::string _waiting_string;

        bool _turn;

        /*Fork stuff*/

        std::vector<std::string> _playersId;
        int _tick_fork;
        
        std::map<std::string, Ressource> _ressourceMap;
        std::vector<std::pair<Commands, std::string>> _bufferOfCommands;
        std::vector<std::string> _broadcastCommands;
    };
}

std::ostream &operator<<(std::ostream &os, const Zappy::AI::Agent &agent);
void operator+=(std::pair<int, int> &a, std::pair<int, int> &b);


#endif /* !AGENT_HPP_ */

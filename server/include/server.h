/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** server
*/

#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "circular_buffer.h"
#include "square.h"

typedef enum resource resource_t;
typedef struct square_s square_t;
typedef square_t **tilesmap_t;
typedef struct total_object_s total_object_t;
typedef struct timeval timeout_t;

enum resource{
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    FOOD
};

enum user_type{
    NONE,
    PLAYER,
    GUI
};

enum orientation{
    NORTH = 1,
    WEST = 3,
    SOUTH = 5,
    EAST = 7
};

typedef struct map_s {
    int x;
    int y;
    int freq;
    int nb_p_player;
    total_object_t *total_object;
    tilesmap_t *tilesmap;
} map_t;

typedef struct team_s {
    char *name;
    int nb_player;
    struct team_s *next;
    struct team_s *first;
} team_t;

typedef struct egg_s {
    int id;
    int x;
    int y;
    int orientation;
    int food;
    long int time;
    char *team_name;
    struct egg_s *next;
    struct egg_s *first;
} egg_t;

typedef struct data_ai_s {
    int id;
    int x;
    int y;
    int level;
    int orientation;
    int inventory[7];
    long int time;
    long int save_time;
    long int last_food_eaten;
    bool is_incanting;
} data_ai_t;

typedef struct user_s {
    int socket;
    int type;
    char *team_name;
    char *buffer;
    circular_buffer_t *cb;
    int nb_cmd;
    data_ai_t *player;
    struct user_s *next;
    struct user_s *first;
} user_t;

typedef struct wait_node_s {
    user_t *user;
    struct wait_node_s *next;
} wait_node_t;

typedef struct wait_list_s {
    wait_node_t *first;
    int size;
} wait_list_t;

typedef struct server_s {
    int port;
    int master_socket;
    int new_socket;
    int activity;
    int sd;
    int max_sd;
    int opt;
    int nb_client;
    struct sockaddr_in address;
    int addrlen;
    long int last_update;
    fd_set readfds;
    map_t *map;
    team_t *team;
    wait_list_t *wait_list;
    egg_t *eggs;
} server_t;

server_t *init_server(void);
user_t *init_user(user_t *first);
team_t *init_team(char *name, int nb_p_player, team_t *first);
void destroy_server(server_t *server);
void destroy_user(user_t *user);
void destroy_team(team_t *team);
void destroy_eggs(egg_t *egg);
egg_t *remove_egg(egg_t *egg, int id);
int getargs(int ac, char **av, server_t *server, int opt);
int start_server(server_t *server);
void accept_user(server_t *server, user_t *user);
void set_socket(server_t *server, user_t *user);
void set_fd(server_t *server, user_t *user, timeout_t *timeout);
int signal_memory(int flag, int value);
int signal_pipe(int flag, int value);
void check_cmd(server_t *server, user_t *user);
int check_team(server_t *server, user_t *tmp);
int check_player(server_t *server, user_t *tmp);
int check_gui(server_t *server, user_t *tmp);
int help(void);
int verif_args(server_t *server);
egg_t *generate_eggs(server_t *server);
egg_t *create_egg(egg_t *egg, int pos[2], char *team_name, int frequence);
int update_select(server_t *server, user_t *users, timeout_t *timeout);
int update_time(server_t *server, user_t *user, timeout_t *timeout,
long int total_timeout);
timeout_t *create_timeout(void);
int update_total_object(server_t *server, map_t *map, user_t *user);
int update_eggs_life(server_t *server, egg_t *egg, long int remaining_timeout,
user_t *user);
void print_first_info(server_t *server);
int transform_orientation(int orientation);
int get_team_id(server_t *server, char *team_name);
/*  Wait lists  */

wait_list_t *create_list(void);
wait_node_t *create_node(user_t *user);
int add_to_list(wait_list_t *list, user_t *user);

bool is_in_list(wait_list_t *list, user_t *user);

int remove_user(wait_list_t *list, user_t *user);
int remove_first(wait_list_t *list);
int destroy_list(wait_list_t *list);
int destroy_node(wait_node_t *node);

void reset_cb(circular_buffer_t *cb);

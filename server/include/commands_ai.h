/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** comands_ai
*/

#pragma once

typedef struct server_s server_t;
typedef struct user_s user_t;
typedef struct square_s square_t;

/* move command */

void ai_forward(server_t *server, user_t *user, [[maybe_unused]] char *arg);
void ai_right(server_t *server, user_t *user, [[maybe_unused]] char *arg);
void ai_left(server_t *server, user_t *user, [[maybe_unused]] char *arg);

/* info command */

void ai_look_north(server_t *server, user_t *user);
void ai_look_east(server_t *server, user_t *user);
void ai_look_south(server_t *server, user_t *user);
void ai_look_west(server_t *server, user_t *user);
void get_players_at_pos(server_t *server, int x, int y, user_t *user);
void print_ressources(square_t *square, server_t *server);
void ai_look(server_t *server, user_t *user, [[maybe_unused]] char *arg);
void ai_inventory(server_t *server, user_t *user, [[maybe_unused]] char *arg);
int get_orientation(server_t *server, user_t *from, user_t *to);
void ai_broadcast(server_t *server, user_t *user, char *arg);

/* command multi */

void ai_connect_nbr(server_t *server, user_t *user, [[maybe_unused]] char *arg);
void ai_fork_return(server_t *server, user_t *user, int slot);
void ai_fork(server_t *server, user_t *user, [[maybe_unused]] char *arg);
bool ai_forking(user_t *user, char *);
void ai_back(server_t *server, user_t *user);
int ai_eject_eggs(server_t *server, user_t *user, egg_t *tmp_e);
void ai_eject(server_t *server, user_t *user, [[maybe_unused]] char *arg);
void ai_death(server_t *server, user_t *user);

/* action command */

int check_obj_name(char *arg);
void ai_take(server_t *server, user_t *user, char *arg);
void ai_set(server_t *server, user_t *user, char *arg);
void add_time
(server_t *server, user_t *user, int nb_player, user_t *player_list[]);
int success_incantation(user_t *player, int win);
int check_incantation_fail(int flag, int value, int sd);
void incantation_end(server_t *server, user_t *user, [[maybe_unused]] char *);
bool ai_incantation(server_t *server, user_t *user, [[maybe_unused]] char *arg);

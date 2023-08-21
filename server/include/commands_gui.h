/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** commands_gui
*/

#pragma once

typedef struct server_s server_t;
typedef struct user_s user_t;
typedef struct team_s team_t;

void map_size(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void content_tile(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void content_map(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void name_teams(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void player_pos(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void player_level(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void player_inv(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void time_unit_request(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);
void time_unit_modif(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command);

void send_to_gui(user_t *user, char *str);
void send_map_tile(server_t *server, user_t *user, int x, int y);
void send_new_player(user_t *user);
void send_player_pos(user_t *user);
void send_player_level(user_t *user);
void send_player_inv(user_t *user);
void send_expulse_gui(user_t *user);
void send_broadcast_gui(user_t *user, char *msg);
void send_incantation_start(user_t *user);
void send_incantation_end(user_t *user, int result);
void send_egg_laying(user_t *user);
void send_drop(user_t *user, int res);
void send_collect(user_t *user, int res);
void send_player_death(user_t *user);
void send_egg_laid(server_t *server, user_t *user);
void send_egg_connection(user_t *user, int id);
void send_egg_dead(user_t *user, int id);
void send_time_unit(server_t *server, user_t *user);
void send_time_modif(server_t *server, user_t *user);
void send_end_game(user_t *user, char *team_name);
void send_message(user_t *user, char *msg);
int player_connection(server_t *server, user_t *tmp, team_t *team);

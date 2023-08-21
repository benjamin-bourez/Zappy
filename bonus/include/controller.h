/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** controller
*/

#pragma once

#include <SFML/Graphics.h>
#include <stdbool.h>

typedef enum state_e state_t;
typedef enum sprites_e sprites_t;
typedef struct tile_s tile_t;
typedef struct client_s client_t;
typedef struct button_s button_t;
typedef struct command_node_s command_node_t;
typedef struct command_queue_s command_queue_t;
typedef struct player_s player_t;
typedef tile_t **tilesmap_t;

typedef enum sprites_e {
    ARROW_FORWARD,
    ARROW_RIGHT,
    ARROW_LEFT,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME_0,
    THYSTAME_1,
    THYSTAME_2,
    THYSTAME_3,
    THYSTAME_4,
    THYSTAME_5,
    THYSTAME_6,
    CHEST,
    LEVEL_UP,
    CASE_HOVER,
    CASE,
    EYE,
    EGG,
    KICK,
    TAKE,
    GRASS,
    GRASS_HOVER
} sprites_t;

typedef enum state_e {
    WAITING_WELCOME,
    WAITING_NBR_CLIENTS,
    WAITING_MAP_SIZE,
    CLIENT_PLAYING
} state_t;

typedef enum direction_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct tile_s {
    int x;
    int y;
    sfVector2f scale;
    int size;
    bool is_hover;
    int nbr_objects[7];
    int nbr_players;
    int nbr_eggs;
} tile_t;

typedef struct sfml_tools_s {
    sfRenderWindow *window;
    sfSprite *sprite;
    sfFont *font;
    sfText *text;
    sfTexture **texture;
} sfml_tools_t;

typedef struct client_s {
    int fd;
    int port;
    char *ip;
    char *last_command;
    int map_size[2];
    int level;
    state_t state;
    tilesmap_t *tilesmap;
    command_queue_t *queue;
    sfml_tools_t *sfml;
} client_t;

typedef struct button_s {
    const char *name;
    sfVector2f pos;
    sfVector2u size;
    sfTexture *texture;
    bool (*is_pressed)(button_t *this, sfEvent event, client_t *client);
    int (*pressed)(button_t *this, client_t *client);
} button_t;

typedef struct command_node_s {
    char *command;
    struct command_node_s *next;
} command_node_t;

typedef struct command_queue_s {
    command_node_t *first;
    int size;
} command_queue_t;

typedef struct player_s {
    sfVector2f pos;
    direction_t direction;
    int nbr_objects[7];
    sprites_t sprites[7];
    sprites_t actual;
} player_t;

// Client management

client_t *create_client(void);
int delete_client(client_t *client);

// Socket management

int lauch_client(client_t *client);
int select_client_terminal(client_t *client, button_t **buttons,
player_t *player);

// SFML management

sfml_tools_t *load_sfml_tools(void);
int manage_sfml_inputs(client_t *client, button_t **buttons,
player_t *player);
int display_last_command(client_t *client);
int destroy_sfml_tools(sfml_tools_t *tools);

// Button management

button_t **generate_buttons(client_t *client);
button_t *create_button(sprites_t type, client_t *client,
int (*pressed)(button_t *this, client_t *client), const char *name);
int draw_button(button_t *button, client_t *client);
int delete_buttons(button_t **buttons);

// Commands

int forward(button_t *this, client_t *client);
int left(button_t *this, client_t *client);
int right(button_t *this, client_t *client);
int look(button_t *this, client_t *client);
int inventory(button_t *this, client_t *client);
int take_object(button_t *this, client_t *client);
int set_object(button_t *this, client_t *client);
int incantation(button_t *this, client_t *client);
int fork_client(button_t *this, client_t *client);

// Inventory management

player_t *create_inventory(void);
int display_inventory(player_t *player, client_t *client);
int delete_player(player_t *player);

// Command queue management

int add_command(command_queue_t *queue, char *command);
command_node_t *create_command_node(char *command);
command_queue_t *create_command_queue(void);
char *get_command(command_queue_t *queue);
int delete_command_queue(command_queue_t *queue);

// Response management

int read_socket(client_t *client, player_t *);

// Tiles management

tile_t *create_tile(void);
int destroy_tilesmap(tilesmap_t *tilesmap);
tilesmap_t *generate_tilesmap(int width, int height);
int manage_tile_hover(client_t *client, sfEvent event);
int display_map(client_t *client);

// Flemme

int get_inventory(client_t *client, char *buffer, player_t *player);
int get_look(client_t *client, char *buffer, player_t *player);
char **my_str_to_word_array(char *str, char *delim);
int nbr_words(char *str, char *delim);
int free_array(char **array);

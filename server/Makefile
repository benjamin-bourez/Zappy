##
## EPITECH PROJECT, 2023
## B-YEP-400-TLS-4-1-zappy-quentin.challon
## File description:
## Makefile
##

MAIN		=	src/main.c

FILESSERVER	=	accept.c				\
				ai_broadcast_tools.c	\
				ai_eject_tools.c		\
				ai_fork.c				\
				ai_incantation_tools.c	\
				ai_incantation.c		\
				ai_look.c				\
				chrono_management.c		\
				circular_buffer.c		\
				cmd_ai_action.c			\
				cmd_ai_info.c			\
				cmd_ai_move.c			\
				cmd_ai_multi.c			\
				cmd_ai.c				\
				cmd_gui.c				\
				cmd_manager.c			\
				connection.c			\
				destroy_struct.c		\
				eggs_destruction.c		\
				eggs_generation.c		\
				gui_map.c				\
				gui_player.c			\
				gui_time.c				\
				init_struct.c			\
				manage_args.c			\
				send_egg_gui.c			\
				send_incantation_gui.c	\
				send_information_gui.c	\
				send_interaction_gui.c	\
				send_map_gui.c			\
				send_player_gui.c		\
				signal.c				\
				square_creation.c		\
				start_server.c			\
				str_to_word_array.c		\
				team_id.c				\
				tile_info.c				\
				update_egg_life.c		\
				verif_args.c			\
				wait_list_creation.c	\
				wait_list_destroy.c		\
				world_creation.c		\

CONNECT = tests/connect.c

TESTS		=	tests/test_square.c				\
				tests/test_world.c				\
				tests/test_struct_init.c		\
				tests/test_circular_buffer.c	\

SRCSERVER 	= $(FILESSERVER:%=src/%)

OBJSERVER	=	$(SRCSERVER:.c=.o) $(MAIN:.c=.o)

OBJCONNECT	=	$(CONNECT:.c=.o)

NAMESERVER	=	zappy_server

NAMECONNECT	=	connect

CFLAGS = -I./include -Wall -Wextra -lm

all: $(NAMESERVER) $(NAMECONNECT)

$(NAMESERVER): $(OBJSERVER)
	gcc -o $(NAMESERVER) $(OBJSERVER) $(CFLAGS)
	cp $(NAMESERVER) ../

$(NAMECONNECT): $(OBJCONNECT)
	gcc -o $(NAMECONNECT) $(OBJCONNECT) $(CFLAGS)
	cp $(NAMECONNECT) ../

clean:
	rm -f $(OBJSERVER)
	rm -f $(OBJCONNECT)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	rm -f ../$(NAMESERVER)
	rm -f ../$(NAMECONNECT)
	rm -f $(NAMESERVER)
	rm -f $(NAMECONNECT)
	rm -f unit_tests

re: fclean all

tests_run:
	gcc -o unit_tests $(SRCSERVER) $(TESTS) $(CFLAGS) --coverage -lcriterion
	./unit_tests

debug: CFLAGS += -g3
debug: re

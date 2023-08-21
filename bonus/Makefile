##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

SRC_FILES	=	button_t.c				\
				client_creation.c		\
				client_destruction.c	\
				client_launch.c			\
				command_queue.c			\
				commands.c				\
				commands2.c				\
				display_commands.c		\
				event_management.c		\
				inventory.c				\
				look.c					\
				main.c					\
				manage_sfml_inputs.c	\
				player.c				\
				response_management.c	\
				select_client.c			\
				sfml_tools.c			\
				str_to_word_array.c		\
				tiles_management.c		\

SRC_DIR		=	src/

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ			=	$(SRC:.c=.o)
DEPENDS		=	$(SRC:.c=.d)

NAME		=	client_controller

CFLAGS		=	-Wall -Wextra -I./include -MMD

LDFLAGS		=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(DEPENDS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug:	CFLAGS += -g3
debug:	re

-include $(DEPENDS)

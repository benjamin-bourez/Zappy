##
## EPITECH PROJECT, 2023
## B-YEP-400-TLS-4-1-zappy-quentin.challon
## File description:
## Makefile
##

SRC	=	main.cpp					\
		ManageAI.cpp				\
		ManageArgs.cpp 				\
		Agent.cpp					\
		ManageFood.cpp				\
		ManageStone.cpp				\
		ManageIncantation.cpp		\
		UtilsAI.cpp					\
		Broadcast.cpp 				\
		../shared_src/Client.cpp			\
		../shared_src/CircularBuffer.cpp	\

OBJ	=	$(SRC:%.cpp=%.o)

NAME	=	zappy_ai

CXXFLAGS	=	-W -Wall -Wextra -Werror -I./include -luuid

all:	$(NAME)
	cp $(NAME) ../

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)
	rm -f *~
	rm -f *#
	rm -f vgcore*

re:	fclean all

debug:	CXXFLAGS += -g3
debug:	re

.PHONY:	all clean fclean re debug

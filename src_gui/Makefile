##
## EPITECH PROJECT, 2023
## B-YEP-400-TLS-4-1-zappy-quentin.challon
## File description:
## Makefile
##

MAIN =	main.cpp

SRC	=	Args.cpp					\
		Core.cpp					\
		../shared_src/Client.cpp			\
		../shared_src/CircularBuffer.cpp	\

TESTS = tests/test_args.cpp			\
		tests/test_core.cpp			\

OBJ	=	$(SRC:%.cpp=%.o) $(MAIN:%.cpp=%.o)

VOXELSRC	=	Voxel/Camera.cpp		\
				Voxel/Entity.cpp		\
				Voxel/Scene.cpp			\
				Voxel/Window.cpp		\
				Voxel/VoxelCore.cpp		\
				Voxel/Character.cpp		\
				Voxel/Factory.cpp		\
				Voxel/VoxColor.cpp		\
				Voxel/VoxSound.cpp		\
				Voxel/VoxMusic.cpp		\
				Voxel/VoxTexture.cpp	\
				Voxel/VoxGif.cpp		\

VOXELOBJ	=	$(VOXELSRC:%.cpp=%.o)

NAME	=	zappy_gui

CXXFLAGS	=	-W -Wall -Wextra -Werror -I./Voxel -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:	$(NAME)
	cp $(NAME) ../

$(NAME):	$(OBJ) $(VOXELOBJ)
	g++ -o $(NAME) $(OBJ) $(VOXELOBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(VOXELOBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)
	rm -f *.gc*
	rm -f unit_tests
	rm -f *~
	rm -f *#
	rm -f vgcore*

re:	fclean all

tests_run:
	g++ -o unit_tests $(TESTS) $(SRC) --coverage -lcriterion -I .
	./unit_tests
	gcovr --exclude tests/

debug:	CXXFLAGS += -g3
debug:	re

.PHONY:	all clean fclean re debug

##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

all:
	@make -C server
	@cd src_gui && make all && cd ..
	@cd src_ai && make all && cd ..

clean:
	@make clean -C server
	@cd src_gui && make clean && cd ..
	@cd src_ai && make clean && cd ..
	rm -f vgcore*

fclean:
	@make fclean -C server
	@cd src_gui && make fclean && cd ..
	@cd src_ai && make fclean && cd ..
	rm -f vgcore*

re:
	@make re -C server
	@cd src_gui && make re && cd ..
	@cd src_ai && make re && cd ..

debug:
	@make debug -C server
	@cd src_gui && make debug && cd ..
	@cd src_ai && make debug && cd ..

tests_run:
	@cd src_gui && make tests_run && cd ..

zappy_server:
	@make -C server

zappy_ai:
	@cd src_ai && make && cd ..

zappy_gui:
	@cd src_gui && make && cd ..

##
## Makefile for Makefile in /home/renaud/Documents/Tech2/C++/cpp_arcade
## 
## Made by Renaud de Ganay
## Login   <renaud@epitech.net>
## 
## Started on  Sat Apr  8 19:43:19 2017 Renaud de Ganay
## Last update Sun Apr  9 18:30:33 2017 Renaud de Ganay
##

all:	games

arcade:	games graphs core

core:
	make -C core/

games:
	make -C games/snake/
	make -C games/pacman/

graphs:
	make -C Graph/

clean:
	make clean -C games/snake/
	make clean -C games/pacman/
	make clean -C Graph/
	make clean -C core/

fclean:
	make fclean -C games/snake/
	make fclean -C games/pacman/
	make fclean -C Graph/
	make fclean -C core/

re:	fclean all

.PHONY:	all games graphs core clean fclean re

##
## Makefile for Makefile in /home/renaud/Documents/Tech2/C++/cpp_arcade/games/pacman
## 
## Made by Renaud de Ganay
## Login   <renaud@epitech.net>
## 
## Started on  Sun Apr  9 01:19:42 2017 Renaud de Ganay
## Last update Sun Apr  9 21:04:14 2017 Renaud de Ganay
##

NAME		= ../lib_arcade_pacman.so

INT		= ../

SCORES		= ../scores/

SRC		= ACharacter.cpp \
		AGhost.cpp \
		GhostBlue.cpp \
		GhostRed.cpp \
		GhostYellow.cpp \
		GhostPink.cpp \
		Packi.cpp \
		Pacman.cpp \
		Pacman_drawer.cpp \
		Pacman_move.cpp \
		$(SCORES)Scores.cpp

OBJS		= $(SRC:.cpp=.o)

CXXFLAGS	+= -W -Wall -Werror -std=c++14 -fPIC

CXXFLAGS	+= -I includes

CXXFLAGS	+= -I $(SCORES)includes

CXXFLAGS	+= -I $(INT)includes

CXX		= g++

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -shared -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean all

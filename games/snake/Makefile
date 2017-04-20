##
## Makefile for Makefile in /home/renaud/Documents/Tech2/C++/cpp_arcade/games
## 
## Made by Renaud de Ganay
## Login   <renaud@epitech.net>
## 
## Started on  Sat Apr  8 18:55:18 2017 Renaud de Ganay
## Last update Sun Apr  9 21:04:33 2017 Renaud de Ganay
##

NAME		= ../lib_arcade_nibbler.so

INT		= ../

SCORES		= ../scores/

SRC		= Snake.cpp \
		Snake_drawer.cpp \
		Snake_move.cpp \
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

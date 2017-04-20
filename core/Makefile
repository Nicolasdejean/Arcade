##
## Makefile for Makefile in /home/renaud/Documents/Tech2/C++/cpp_arcade/core
## 
## Made by Renaud de Ganay
## Login   <renaud@epitech.net>
## 
## Started on  Sun Apr  9 18:09:09 2017 Renaud de Ganay
## Last update Sun Apr  9 18:24:07 2017 Renaud de Ganay
##

NAME		= ../arcade

DL		= ../dlopen/

SRC		= arcade.cpp \
		Core.cpp \
		$(DL)DLLoader.cpp \
		$(DL)exception.cpp \
		$(DL)Menu.cpp

OBJS		= $(SRC:.cpp=.o)

CXXFLAGS	+= -W -Wall -Werror -std=c++14

CXXFLAGS	+= -I includes

CXXFLAGS	+= -I $(DL)includes

CXX		= g++

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) -ldl

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean all

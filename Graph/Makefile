##
## Makefile for Makefile in /home/renaud/Documents/Tech2/C++/cpp_arcade/Graph
## 
## Made by Renaud de Ganay
## Login   <renaud@epitech.net>
## 
## Started on  Sat Apr  8 20:51:28 2017 Renaud de Ganay
## Last update Sun Apr  9 21:03:15 2017 Renaud de Ganay
##

#
# NAMES
#

SFML		= ../lib/lib_arcade_sfml.so

NCURSES		= ../lib/lib_arcade_ncurses.so

OPENGL		= ../lib/lib_arcade_opengl.so

#
# SOURCES
#

SFML_SRC	= Sfml.cpp

NCURSES_SRC	= Ncurses.cpp

OPENGL_SRC	= Opengl.cpp

#
# OBJECTS
#

SFML_OBJ	= $(SFML_SRC:.cpp=.o)

NCURSES_OBJ	= $(NCURSES_SRC:.cpp=.o)

OPENGL_OBJ	= $(OPENGL_SRC:.cpp=.o)

#
# COMMON FLAGS
#

CXXFLAGS	+= -W -Wall -Wextra -std=c++14 -fPIC

CXXFLAGS	+= -I includes

CXXFLAGS	+= -I ../games/includes

#
# LIB FLAGS
#

SFML_LFLAGS	+= -lsfml-window -lsfml-graphics -lsfml-window

NCURSES_LFLAGS	+= -lncurses

OPENGL_LFLAGS	+= -lGL -lGLU

#
# SYSTEM
#

CXX		= g++

RM		= rm -f

#
# RULES
#

all: $(SFML) $(NCURSES) $(OPENGL)

$(SFML): $(SFML_OBJ)
	$(CXX) -shared -o $(SFML) $(SFML_OBJ) $(SFML_LFLAGS)

$(NCURSES): $(NCURSES_OBJ)
	$(CXX) -shared -o $(NCURSES) $(NCURSES_OBJ) $(NCURSES_LFLAGS)

$(OPENGL): $(OPENGL_OBJ)
	$(CXX) -shared -o $(OPENGL) $(OPENGL_OBJ) $(OPENGL_LFLAGS) $(SFML_LFLAGS)

clean:
	$(RM) $(SFML_OBJ) $(NCURSES_OBJ) $(OPENGL_OBJ)

fclean: clean
	$(RM) $(SFML) $(NCURSES) $(OPENGL)

re: fclean all

.PHONY: re clean fclean all

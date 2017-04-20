//
// Core.cpp for Core in /home/renaud/Documents/Tech2/C++/cpp_arcade/dlopen
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Sun Apr  9 15:05:20 2017 Renaud de Ganay
// Last update Sun Apr  9 22:52:14 2017 benjamin girard
//

#include "includes/Core.hpp"

//
// *TOR
//

Core::Core(std::string const &lib_name) :
  _menu(lib_name)
{
  this->_graph = this->_menu.getCurrentGraph();
  this->_game = this->_menu.getCurrentGame();
  this->_input = _UNDEFINED_;
  this->_status = ALIVE;
}

//
// MB FUNCS
//

void			Core::startMenu(void)
{
  this->_menu.startMenu();
  this->_graph = this->_menu.getCurrentGraph();
  this->_game = this->_menu.getCurrentGame();
}

void			Core::updateInput(void)
{
  this->_input = this->_graph->checkInput();
}

void			Core::updateGraph(void)
{
  this->_graph = this->_menu.getCurrentGraph();
}

void			Core::updateGame(void)
{
  this->_game = this->_menu.getCurrentGame();
}

void			Core::checkDirection(void)
{
  if ((this->_input >= _UP_ && this->_input <= _RIGHT_))
    this->_game->change_direction(this->_input);
}

void			Core::checkGraph(void)
{
  ((this->_input == _TWO_ && this->_menu.prevGraph(this->_menu.getUsername())) ||
   (this->_input == _THREE_ && this->_menu.prevGraph(this->_menu.getUsername())));
  this->_graph = this->_menu.getCurrentGraph();
}

void			Core::checkGame(void)
{
  ((this->_input == _FOUR_ && this->_menu.prevGame(this->_menu.getUsername())) ||
   (this->_input == _FIVE_ && this->_menu.prevGame(this->_menu.getUsername())));
  this->_game = this->_menu.getCurrentGame();
}

bool			Core::checkOpen(void)
{
  return (this->_graph->isOpen());
}

void			Core::checkClose(void)
{
  if (this->_input == _ESCAPE_)
    this->_graph->close_window();
}

void			Core::checkPause(void)
{
  if (this->_input == _SPACE_)
    this->_game->change_direction(this->_input);
}

void			Core::checkRestart(void)
{
  if (this->_input == _EIGHT_)
    {
      this->_menu.restartGame(this->_menu.getUsername());
      this->_graph = this->_menu.getCurrentGraph();
      this->_game = this->_menu.getCurrentGame();
    }
}

void			Core::checkMenu(void)
{
  if (this->_input == _NINE_)
    {
      this->_menu.backMenu();
      this->_graph = this->_menu.getCurrentGraph();
      this->_game = this->_menu.getCurrentGame();
    }
}

void			Core::c_play(void)
{
  this->_game->play(*this->_graph);
}

void			Core::c_clear(void)
{
  this->_graph->a_clear();
}

void			Core::c_refresh(void)
{
  this->_graph->a_refresh();
}

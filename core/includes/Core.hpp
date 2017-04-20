//
// Core.hpp for Core in /home/renaud/Documents/Tech2/C++/cpp_arcade/dlopen
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Sun Apr  9 15:05:27 2017 Renaud de Ganay
// Last update Sun Apr  9 19:00:47 2017 Renaud de Ganay
//

#ifndef _CORE_HPP_
# define _CORE_HPP_

#include "../../dlopen/includes/Menu.hpp"

class			Core
{
private:
  Menu			_menu;
  IGraph		*_graph;
  IGame			*_game;
  Input			_input;
  e_status		_status;

  Core(Core const & /*other */);
  Core operator=(Core const & /* other */)
  { return (*this); }

public:
  Core(const std::string &lib_name);
  ~Core(void) {}

  void			startMenu(void);

  void			checkDirection(void);

  void			checkGraph(void);
  void			checkGame(void);
  bool			checkOpen(void);
  void			checkClose(void);
  void			checkPause(void);

  void			checkRestart(void);
  void			checkMenu(void);

  void			updateInput(void);
  void			updateGraph(void);
  void			updateGame(void);

  void			c_play(void);

  void			c_clear(void);
  void			c_refresh(void);
};

#endif /* !_CORE_HPP_ */

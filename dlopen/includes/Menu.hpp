//
// Menu.hpp for Menu in /home/renaud/Documents/Tech2/C++/cpp_arcade
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Mon Apr  3 16:24:04 2017 Renaud de Ganay
// Last update Sun Apr  9 20:47:46 2017 Renaud de Ganay
//

#ifndef _MENU_HPP_
# define _MENU_HPP_

#include <regex>
#include "DLLoader.hpp"

static const std::regex REGEX_USERNAME("^([A-Za-z0-9_])+$");

class			Menu : public DLLoader
{
private:
  std::string		_username;
  std::pair<uint16_t, uint16_t> _size;

  Menu(Menu const &/* other */) : DLLoader(NULL)
  {}
  Menu operator=(Menu const &/* other */)
  { return (*this); }

public:
  Menu(std::string const &lib_path);
  virtual ~Menu(void) {}

  void			startMenu(void);
  void			backMenu(void);

  void			askUsername(void);
  uint16_t		askGraphicLibrary(void);
  uint16_t		askGameLibrary(void);

  IGraph		*checkMoveGraph(Input &input);

  std::string const	&getUsername(void) const;

  void			drawControls(t_a_color &color) const;
};

#endif /* !_MENU_HPP_ */

//
// Menu.cpp for Menu in /home/renaud/Documents/Tech2/C++/cpp_arcade/dlopen
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Tue Apr  4 15:02:25 2017 Renaud de Ganay
// Last update Sun Apr  9 20:58:25 2017 Renaud de Ganay
//

#include <chrono>
#include <thread>
#include "includes/Menu.hpp"

Menu::Menu(std::string const &lib_path) : DLLoader(lib_path)
{
  askUsername();
}

void				Menu::startMenu(void)
{
  uint16_t			off = 0;

  this->_size = this->_curr_graph->create_window(WIDTH, HEIGHT);
  while (this->_curr_graph->isOpen())
    {
      off = askGraphicLibrary();
      this->nbGraph(off, this->_username);
      off = askGameLibrary();
      this->_curr_game = this->nbGame(off, this->_username);
      break;
    }
}

void				Menu::backMenu(void)
{
  this->_curr_graph->close_window();
  this->startMenu();
}

void				Menu::askUsername(void)
{
  Except			username;

  std::cout << "> Please enter your username : ";
  std::getline(std::cin, this->_username);
  try {
  if (std::regex_match(this->_username, REGEX_USERNAME) == false)
    throw username;
  }
  catch(const Except &e) {
    e.badusername();
  }
}

uint16_t			Menu::askGameLibrary(void)
{
  Input				input;
  t_a_color			color;
  uint16_t			off;

  input = _UNDEFINED_;
  off = 2;
  while (input != _ENTER_)
    {
      this->_curr_graph->a_clear();
      color = {167,0,7, _RED_};
      this->_curr_graph->draw_text(arcade::Position{0, 0}, ("Hello " + this->_username + ", please choose a game library : "), 35, color);
      color = {255, 255 , 255, _WHITE_};
      this->drawControls(color);
      color = {185, 27, 127, _BLUE_};
      for (uint16_t i = 0; i < this->_game_names.size(); i++)
	this->_curr_graph->draw_text(arcade::Position {1, static_cast<uint16_t>(i + 2)},
		      this->_game_names[i].substr((this->_game_names[i].find_first_of('_', 0) + 1), this->_game_names[i].length() - 7), 35, color);
      color = {255, 255, 255, _WHITE_};
      this->_curr_graph->draw_rectangle(arcade::Position {0, off}, color);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      this->_curr_graph->a_refresh();
      input = this->_curr_graph->checkInput();
      this->checkMoveGraph(input);
      ((input == _DOWN_ && (off += 1)) || (input == _UP_ && (off -= 1)));
      off = off > (this->_game_names.size() + 1) ? 2 :
	off < 2 ?  (this->_game_names.size() + 1) : off;
    }
  return (off - 2);
}

uint16_t			Menu::askGraphicLibrary(void)
{
  Input				input;
  t_a_color			color;
  uint16_t			off;

  input = _UNDEFINED_;
  off = 2;
  while (input != _ENTER_)
    {
      this->_curr_graph->a_clear();
      color = {167,0,7, _RED_};
      this->_curr_graph->draw_text(arcade::Position{0, 0}, ("Hello " + this->_username + ", please choose a graphic library : "), 35, color);
      color = {255, 255 , 255, _WHITE_};
      this->drawControls(color);
      color = {185, 27, 127, _BLUE_};
      for (uint16_t i = 0; i < this->_graph_names.size(); i++)
	this->_curr_graph->draw_text(arcade::Position {1, static_cast<uint16_t>(i + 2)},
				     this->_graph_names[i].substr((this->_graph_names[i].find_first_of('_', 0) + 1), this->_graph_names[i].length() - 7), 35, color);
      color = {255, 255, 255, _WHITE_};
      this->_curr_graph->draw_rectangle(arcade::Position {0, off}, color);
      this->_curr_graph->a_refresh();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      input = this->_curr_graph->checkInput();
      this->checkMoveGraph(input);
      ((input == _DOWN_ && (off += 1)) || (input == _UP_ && (off -= 1)));
      off = off > (this->_graph_names.size() + 1) ? 2 :
	off < 2 ?  (this->_graph_names.size() + 1) : off;
    }
  return (off - 2);
}

IGraph				*Menu::checkMoveGraph(Input &input)
{
  if (input == _TWO_)
    return (this->prevGraph(this->_username));
  else if (input == _THREE_)
    return (this->nextGraph(this->_username));
  else
    return (this->getCurrentGraph());
}

std::string const		&Menu::getUsername(void) const
{
  return (this->_username);
}

void				Menu::drawControls(t_a_color &color) const
{
    this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 18)}, "Controls :", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 16)}, "> '2': Previous graphic library.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 14)}, "> '3': Next graphic library.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 12)}, "> '4': Previous game.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 10)}, "> '5': Next graphic library.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 8)}, "> '8': Restart game.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 6)}, "> '9': Go back to menu.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 4)}, "> 'Escape': Exit.", 35, color);
  this->_curr_graph->draw_text(arcade::Position{0, static_cast<uint16_t>(this->_size.second - 2)}, "> 'Space': Pause game.", 35, color);

}

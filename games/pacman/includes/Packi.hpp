//
// Packi.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 12:33:38 2017 benjamin girard
// Last update Sun Apr  9 14:05:23 2017 benjamin girard
//

#ifndef PACKI_HPP_
# define PACKI_HPP_

#include "ACharacter.hpp"

static const t_drawer		PACKI_DRAWER = {
  {250, 196, 0, _YELLOW_},
  'c'
};

class				Packi : public ACharacter
{
private:
  bool				_powup;

  Input				_buffer;

public:
  Packi(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  Packi(const Packi &cp);

  Packi				&operator=(const Packi &cp);

  virtual ~Packi(void) {}

  virtual void			move(const std::vector<arcade::TileType> &map);

  void				setPowUp(bool status) {this->_powup = status;}
  void				setBuffer(Input input) {this->_buffer = input;}
  Input				getBuffer(void) const {return (this->_buffer);}
  bool				isPowUp(void) const {return (this->_powup);}
  // change dir already implemented in parent
};

#endif /* !PACKI_HPP_ */

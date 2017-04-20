//
// AGhost.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 13:05:40 2017 benjamin girard
// Last update Sun Apr  9 14:00:38 2017 benjamin girard
//

#ifndef AGHOST_HPP_
# define AGHOST_HPP_

#include "ACharacter.hpp"

class					AGhost : public ACharacter
{
protected:
  uint16_t				_slow;
  uint16_t				_dead;

  AGhost					&operator=(const AGhost &/* cp */)
    {return (*this);}

public:
  AGhost(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  AGhost(const AGhost &cp);
  virtual ~AGhost(void) {}

  virtual void				move(const std::vector<arcade::TileType> &map) = 0;
  virtual void				slow(void) {this->_slow = TIME_SLOW;}
  virtual void				kill(void);

  virtual char				getSlow(void) const {return (this->_slow);}
  virtual char				getDead(void) const {return (this->_dead);}
};

#endif /* !AGHOST_HPP_ */

//
// GhostRed.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman/includes
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 16:01:43 2017 benjamin girard
// Last update Sun Apr  9 14:03:35 2017 benjamin girard
//

#ifndef GHOSTRED_HPP_
# define GHOSTRED_HPP_

#include "AGhost.hpp"

static const t_drawer		GHOSTRED_DRAWER = {
  {253, 59, 17, _RED_},
  'U'
};

class				GhostRed : public AGhost
{
private:
  GhostRed			&operator=(const GhostRed &/* cp */)
    {return (*this);}

public:
  GhostRed(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  GhostRed(const GhostRed &cp);
  virtual ~GhostRed(void) {}

  virtual void			move(const std::vector<arcade::TileType> &map);
};

#endif /* GHOSTRED_HPP_ */

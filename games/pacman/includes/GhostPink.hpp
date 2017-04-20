//
// GhostPink.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman/includes
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 16:01:43 2017 benjamin girard
// Last update Sun Apr  9 14:02:34 2017 benjamin girard
//

#ifndef GHOSTPINK_HPP_
# define GHOSTPINK_HPP_

#include "AGhost.hpp"

static const t_drawer		GHOSTPINK_DRAWER = {
  {253, 195, 212, _MAGENTA_},
  'U'
};

class				GhostPink : public AGhost
{
private:
  GhostPink			&operator=(const GhostPink &/* cp */)
    {return (*this);}

public:
  GhostPink(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  GhostPink(const GhostPink &cp);
  virtual ~GhostPink(void) {}

  virtual void			move(const std::vector<arcade::TileType> &map);
};

#endif /* GHOSTPINK_HPP_ */

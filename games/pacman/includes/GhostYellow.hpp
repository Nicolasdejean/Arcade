//
// GhostYellow.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman/includes
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 16:01:43 2017 benjamin girard
// Last update Sun Apr  9 14:04:31 2017 benjamin girard
//

#ifndef GHOSTYELLOW_HPP_
# define GHOSTYELLOW_HPP_

#include "AGhost.hpp"

static const t_drawer		GHOSTYELLOW_DRAWER = {
  {255, 160, 0, _YELLOW_},
  'U'
};

class				GhostYellow : public AGhost
{
private:
  GhostYellow			&operator=(const GhostYellow &/* cp */)
    {return (*this);}

public:
  GhostYellow(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  GhostYellow(const GhostYellow &cp);
  virtual ~GhostYellow(void) {}

  virtual void			move(const std::vector<arcade::TileType> &map);
};

#endif /* GHOSTYELLOW_HPP_ */

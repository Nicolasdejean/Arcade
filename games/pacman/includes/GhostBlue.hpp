//
// GhostBlue.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman/includes
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 16:01:43 2017 benjamin girard
// Last update Sun Apr  9 14:01:38 2017 benjamin girard
//

#ifndef GHOSTBLUE_HPP_
# define GHOSTBLUE_HPP_

#include "AGhost.hpp"

static const t_drawer		GHOSTBLUE_DRAWER = {
  {73, 223, 202, _CYAN_},
  'U'
};

class				GhostBlue : public AGhost
{
private:
  GhostBlue			&operator=(const GhostBlue &/* cp */)
    {return (*this);}

public:
  GhostBlue(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  GhostBlue(const GhostBlue &cp);
  virtual ~GhostBlue(void) {}

  virtual void			move(const std::vector<arcade::TileType> &map);
};

#endif /* GHOSTBLUE_HPP_ */

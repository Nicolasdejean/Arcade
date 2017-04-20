//
// GhostRed.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 16:06:26 2017 benjamin girard
// Last update Sun Apr  9 14:04:13 2017 benjamin girard
//

#include <map>
#include <random>
#include "includes/GhostRed.hpp"

GhostRed::GhostRed(const arcade::Position &pos, const t_drawer &sprite, const std::string &path) :
  AGhost(pos, sprite, path) {}

GhostRed::GhostRed(const GhostRed &cp) : AGhost(cp.getPos(), cp.getSprite(), cp.getPath()) {}

void					GhostRed::move(const std::vector<arcade::TileType> &map)
{
  uint16_t				x = this->_pos.x;
  uint16_t				y = this->_pos.y;

  static std::map<size_t, Input>	rtok = {
    {0, _UP_},
    {1, _LEFT_},
    {2, _DOWN_},
    {3, _RIGHT_}
  };

  std::map<Input, arcade::Position> next_pos = {
    {_LEFT_, arcade::Position{static_cast<uint16_t>(x == 0 ? (PACMAP_WIDTH - 1) : (x - 1)), y}},
    {_RIGHT_, arcade::Position{static_cast<uint16_t>((x + 1) == (PACMAP_WIDTH - 1) ? 0 : (x + 1)), y}},
    {_UP_, arcade::Position{x, static_cast<uint16_t>(y - 1)}},
    {_DOWN_, arcade::Position{x, static_cast<uint16_t>(y + 1)}}
  };

  if (this->_dead == 0 && this->_slow % 2 == 0)
  {
    if (map[next_pos[this->_dir].y * PACMAP_WIDTH + next_pos[this->_dir].x] == arcade::TileType::BLOCK) {{
	std::random_device		rd;
	std::mt19937			generator(rd());
	std::uniform_int_distribution<size_t> distribution(0, 3);

	size_t				idx = distribution(generator);
	while ((next_pos[rtok[idx]].y == GHOST_ENTRY_POS.y && next_pos[rtok[idx]].x == GHOST_ENTRY_POS.x) ||
	       (map[next_pos[rtok[idx]].y * PACMAP_WIDTH + next_pos[rtok[idx]].x] == arcade::TileType::BLOCK))
	  idx = distribution(generator);
	this->_dir = rtok[idx];
    }}
    this->_pos.x = next_pos[this->_dir].x;
    this->_pos.y = next_pos[this->_dir].y;
  }
  this->_dead = this->_dead > 0 ? this->_dead - 1 : 0;
  this->_slow = this->_slow > 0 ? this->_slow - 1 : 0;
}

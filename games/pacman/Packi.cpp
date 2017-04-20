//
// Packi.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 12:42:48 2017 benjamin girard
// Last update Sun Apr  9 14:05:53 2017 benjamin girard
//

#include "includes/Packi.hpp"

Packi::Packi(const arcade::Position &pos, const t_drawer &sprite, const std::string &path) :
  ACharacter(pos, sprite, path),
  _buffer(_DOWN_)
{}

Packi::Packi(const Packi &cp) :
  ACharacter(cp.getPos(), cp.getSprite(), cp.getPath()),
  _buffer(cp.getBuffer())
{}

Packi					&Packi::operator=(const Packi &cp)
{
  if (this != &cp) {
    this->_pos.x = cp.getPos().x;
    this->_pos.y = cp.getPos().y;
    this->_dir = cp.getDir();
    this->_powup = cp.isPowUp();
    this->_buffer = cp.getBuffer();
  }
  return (*this);
}

#include <iostream>
void					Packi::move(const std::vector<arcade::TileType> &map)
{
  auto					x = this->_pos.x;
  auto					y = this->_pos.y;

  ((this->_dir == _LEFT_ && (x == 0 || map[y * PACMAP_WIDTH + (x - 1)] != arcade::TileType::BLOCK) &&
    (this->_pos.x = (x == 0 ? PACMAP_WIDTH - 1: x - 1))) ||
   (this->_dir == _RIGHT_ && (x == PACMAP_WIDTH - 1 || map[y * PACMAP_WIDTH + (x + 1)] != arcade::TileType::BLOCK) &&
    (this->_pos.x = (x == PACMAP_WIDTH - 1 ? 0 : x + 1))) ||
   (this->_dir == _UP_ && map[(y - 1) * PACMAP_WIDTH + x] != arcade::TileType::BLOCK &&
    (this->_pos.y = this->_pos.y - 1)) ||
   (this->_dir == _DOWN_ && (x != GHOST_ENTRY_POS.x || y != GHOST_ENTRY_POS.y) && map[(y + 1) * PACMAP_WIDTH + x] != arcade::TileType::BLOCK &&
    (this->_pos.y = this->_pos.y + 1)));
}

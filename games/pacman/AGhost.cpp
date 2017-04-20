//
// AGhost.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  8 13:13:31 2017 benjamin girard
// Last update Sun Apr  9 14:01:11 2017 benjamin girard
//

#include "includes/AGhost.hpp"

AGhost::AGhost(const arcade::Position &pos, const t_drawer &sprite, const std::string &path) :
  ACharacter(pos, sprite, path)
{
  _dir = _UP_;
  _slow = 0;
  _dead = TIME_DEAD;
}

AGhost::AGhost(const AGhost &cp) :
  ACharacter(cp.getPos(), cp.getSprite(), cp.getPath()),
  _slow(cp.getSlow()),
  _dead(cp.getDead())
{}

void					AGhost::kill(void)
{
  this->_dead = TIME_DEAD;
  this->_slow = 0;
  this->_dir = _UP_;
  this->_pos = GHOST_START_POS;
}

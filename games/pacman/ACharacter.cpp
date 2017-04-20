//
// ACharacter.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Fri Apr  7 22:10:36 2017 benjamin girard
// Last update Sun Apr  9 13:59:59 2017 benjamin girard
//

#include "includes/ACharacter.hpp"


ACharacter::ACharacter(const arcade::Position &pos, const t_drawer &sprite, const std::string &path) :
  _dir(_DOWN_),
  _sprite(sprite)
{
  this->_pos.x = pos.x;
  this->_pos.y = pos.y;
  this->_path_s = path;
}

ACharacter::ACharacter(const ACharacter &cp) :
  _dir(cp.getDir())
{
  _pos.x = cp.getPos().x;
  _pos.y = cp.getPos().y;
  _path_s = cp.getPath();
}

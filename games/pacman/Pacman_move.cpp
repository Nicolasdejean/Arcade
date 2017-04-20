//
// Pacman_move.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Fri Apr  7 21:59:57 2017 benjamin girard
// Last update Sun Apr  9 20:18:25 2017 benjamin girard
//

#include <iostream>
#include "includes/Pacman.hpp"

void					Pacman::change_direction(Input input)
{
  auto					x = this->_packi.getPos().x;
  auto					y = this->_packi.getPos().y;

  if (input == _SPACE_) {
    this->_pause = !this->_pause;
    return ;
  }

  if (this->_pause == false) {
  std::map<Input, arcade::TileType>	next_pos = {
    {_UP_, this->_map[(y - 1) * WIDTH_PACMAP + x]},
    {_DOWN_, this->_map[(y + 1) * WIDTH_PACMAP + x]},
    {_LEFT_, this->_map[(y * WIDTH_PACMAP) + (x == 0 ? WIDTH_PACMAP - 1 : x - 1)]},
    {_RIGHT_, this->_map[(y * WIDTH_PACMAP) + (x == WIDTH_PACMAP - 1 ? 0 : x + 1)]}
  };

  if (next_pos[input] != arcade::TileType::BLOCK &&
      (input != _DOWN_ || (x != GHOST_ENTRY_POS.x || y + 1 != GHOST_ENTRY_POS.y))) {
    this->_packi.changeDir(input);
    this->_packi.setBuffer(input);
  }
  else
    this->_packi.setBuffer(input);
  }
}

void					Pacman::go_up(void) {
  this->_packi.move(this->_map);
}

void					Pacman::go_down(void) {
  this->_packi.move(this->_map);
}

void					Pacman::go_left(void) {
  this->_packi.move(this->_map);
}


void					Pacman::go_right(void) {
  this->_packi.move(this->_map);
}


void					Pacman::go_forward(void) const {}

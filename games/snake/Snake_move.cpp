//
// Snake_move.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Mon Apr  3 16:32:31 2017 benjamin girard
// Last update Sun Apr  9 20:14:42 2017 benjamin girard
//

#include "includes/Snake.hpp"

void					Snake::go_up(void)
{
  this->_me.push_front(arcade::Position{this->_me.front().x,
	static_cast<uint16_t>(this->_me.front().y - 1)});

  if (this->_me.front().x != this->_food_pos.x || this->_me.front().y != this->_food_pos.y)
    this->_me.pop_back();
  else {
    generate_food();
    this->_scores += 1;
  }
}

void					Snake::go_down(void)
{
  this->_me.push_front(arcade::Position{this->_me.front().x,
	static_cast<uint16_t>(this->_me.front().y + 1)});

  if (this->_me.front().x != this->_food_pos.x || this->_me.front().y != this->_food_pos.y)
    this->_me.pop_back();
  else {
    generate_food();
    this->_scores += 1;
  }
}

void					Snake::go_left(void)
{
  this->_me.push_front(arcade::Position{static_cast<uint16_t>(this->_me.front().x - 1),
	this->_me.front().y});

  if (this->_me.front().x != this->_food_pos.x || this->_me.front().y != this->_food_pos.y)
    this->_me.pop_back();
  else {
    generate_food();
    this->_scores += 1;
  }
}

void					Snake::go_right(void)
{
  this->_me.push_front(arcade::Position{static_cast<uint16_t>(this->_me.front().x + 1),
	this->_me.front().y});

  if (this->_me.front().x != this->_food_pos.x || this->_me.front().y != this->_food_pos.y)
    this->_me.pop_back();
  else {
    generate_food();
    this->_scores += 1;
  }
}

void					Snake::change_direction(Input input)
{
  if (input == _SPACE_)
    this->_pause = this->_pause == true ? false : true;
  else if (input == _LEFT_ && this->_dir != _RIGHT_ && this->_pause == false)
    this->_dir = input;
  else if (input == _RIGHT_ && this->_dir != _LEFT_ && this->_pause == false)
    this->_dir = input;
  else if (input == _UP_ && this->_dir != _DOWN_ && this->_pause == false)
    this->_dir = input;
  else if (input == _DOWN_ && this->_dir != _UP_ && this->_pause == false)
    this->_dir = input;
}

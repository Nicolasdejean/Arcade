//
// Snake.cpp for Snake in /home/renaud/Documents/Tech2/C++/cpp_arcade
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Wed Mar 29 16:42:16 2017 benjamin girard
// Last update Sun Apr  9 22:51:27 2017 benjamin girard
//

#include "includes/Snake.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <random>

Snake::Snake(void)
{
  this->_dir = _RIGHT_;
  this->_food_pos.x = 0;
  this->_food_pos.y = 0;
  this->_pause = false;
}

Snake::~Snake(void) {}

void					Snake::init(uint16_t width, uint16_t height,
						    const std::string &name)
{
  this->_width = width;
  this->_height = height;
  this->_me.clear();
  this->_map.clear();
  this->_pause = false;
  for (auto pos = 2; pos > -2; pos--)
    this->_me.push_back(arcade::Position{static_cast<uint16_t>((width / 2) + pos),
	  static_cast<uint16_t>(this->_height / 2)});
  for (auto i = 0; i < (width * this->_height); i++) {
    if (i < width)
      this->_map.push_back(arcade::TileType::EMPTY);
    else if ((i > (this->_width * (this->_height / 4) + ((this->_width / 2) - 10)) &&
	      i < (this->_width * (this->_height / 4) + ((this->_width / 2) + 10))) ||
	     (i > (this->_width * (this->_height / 2 + 4) + ((this->_width / 2) - 10)) &&
	      i < (this->_width * (this->_height / 2 + 4) + ((this->_width / 2) + 10))))
      this->_map.push_back(arcade::TileType::BLOCK);
    else
      this->_map.push_back(
	(i < width * 2 || i % width == 0 || i % width == width -1 || i >= width * this->_height - width) ?
	arcade::TileType::BLOCK : arcade::TileType::EMPTY);
  }
  this->_dir = _RIGHT_;
  this->_food_pos.x = 0;
  this->_food_pos.y = 0;
  generate_food();
  this->_scores.init(name, (PATH_SNAKE_SCORES + name + SCORE_EXT));
}

const arcade::WhereAmI			*Snake::where_am_i(void) const
{
  auto					wai = (arcade::WhereAmI *) ::operator new
    (sizeof(arcade::WhereAmI) + sizeof(arcade::Position) * this->_me.size());
  auto					i = 0;
  for (auto &it : this->_me)
    wai->position[i++] = it;
  wai->type = arcade::CommandType::WHERE_AM_I;
  wai->lenght = this->_me.size();
  return (wai);
}

const arcade::GetMap			*Snake::get_map(void) const
{
  auto map = (arcade::GetMap *) ::operator new
    (sizeof(arcade::GetMap) + (sizeof(arcade::TileType) * _width * _height));
  map->type = arcade::CommandType::GET_MAP;
  map->width = this->_width;
  map->height = this->_height;

  auto i = 0;
  for (auto &it : _map)
    map->tile[i++] = it;
  return (map);
}

double					Snake::count_time(std::chrono::high_resolution_clock::time_point t1)
{
  double				t_to_sleep =
    BASIC_TIME_S - (std::chrono::duration_cast<std::chrono::duration<long double> >
		  (std::chrono::high_resolution_clock::now() - t1)).count();

  return (t_to_sleep);
}

void					Snake::play(IGraph &graph)
{
  draw_snake(graph);
  if (is_over() == DEAD)
    draw_end_game(graph);
  else if (this->_pause == false) {
    _dir == _UP_ ? go_up() : _dir == _DOWN_ ? go_down() :
      _dir == _RIGHT_ ? go_right() : go_left();
  }
  else
    display_pause(graph);
  auto					level_time = BASIC_TIME_S - ((this->_scores.getScore() / 10) * 10);
  std::this_thread::sleep_for(std::chrono::milliseconds(level_time < 30 ? 30 : level_time));
}

bool					Snake::is_pos_in_me(uint16_t x, uint16_t y) const
{
  for (auto &it : this->_me)
    if (it.x == x && it.y == y)
      return (true);
  return (false);
}

e_status				Snake::generate_food(void)
{
  // get empty slots
  std::vector<arcade::Position>		empty_slots;
  auto					i = 0;

  for (auto &it : this->_map) {
    if (it == arcade::TileType::EMPTY && i >= this->_width && !is_pos_in_me(i % this->_width, i / this->_width))
      empty_slots.push_back(arcade::Position {static_cast<uint16_t>(i % this->_width),
	    static_cast<uint16_t>(i / this->_width)});
    i++;
  }

  if (empty_slots.size() == 0)
    return (WINNER);

  // generate pos
  {
    std::random_device				rd;
    std::mt19937				generator(rd());
    std::uniform_int_distribution<size_t>	distribution(0, empty_slots.size() - 1);
    size_t					idx = distribution(generator);

    if (this->_food_pos.x != 0 && this->_food_pos.y != 0)
      this->_map[this->_width * this->_food_pos.y + this->_food_pos.x] = arcade::TileType::EMPTY;
    this->_map[this->_width * empty_slots[idx].y + empty_slots[idx].x] = arcade::TileType::POWERUP;
    this->_food_pos = arcade::Position {empty_slots[idx].x, empty_slots[idx].y};
  }

  // generate id
  {
    std::random_device				rd;
    std::mt19937				generator(rd());
    std::uniform_int_distribution<size_t>	distribution(0, NIBBLER_FOOD.size() - 1);
    size_t					idx = distribution(generator);

    this->_idx_food = idx;
  }
  return (ALIVE);
}

e_status					Snake::is_over(void)
{
  auto					head = this->_me.front();

  for (auto it = ++(this->_me.begin()); it != this->_me.end(); it++)
    if ((*it).x == head.x && (*it).y == head.y) {
      this->_scores.updateHighScore();
      return (DEAD);
    }
  if (this->_map[head.y * this->_width + head.x] == arcade::TileType::BLOCK) {
    this->_scores.updateHighScore();
    return (DEAD);
  }
  return (ALIVE);
}

Input					Snake::getDir(void) const
{
  return (this->_dir);
}

void					Snake::setDir(Input dir)
{
  this->_dir = dir;
}

uint16_t				Snake::getWidth(void) const
{
  return (this->_width);
}

uint16_t				Snake::getHeight(void) const
{
  return (this->_width);
}

const std::list<arcade::Position>	&Snake::getMe(void) const
{
  return (this->_me);
}

extern "C" void					Play(void)
{
  Snake					snake;
  uint16_t				cmd;

  snake.init(20, 20, "");
  while (read(0, &cmd, sizeof(arcade::CommandType)))
  {
    const arcade::WhereAmI			*wai = snake.where_am_i();
    const arcade::GetMap			*gmap = snake.get_map();
    auto					size_map =
      (sizeof(arcade::GetMap) + (sizeof(arcade::TileType) * snake.getWidth() * snake.getHeight()));
    auto					size_wai =
      (sizeof(struct arcade::WhereAmI) + sizeof(struct arcade::Position) * snake.getMe().size());

    if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::WHERE_AM_I)
      write(1, wai, size_wai);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GET_MAP)
      write(1, gmap, size_map);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_UP)
      snake.setDir(_UP_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_DOWN)
      snake.setDir(_DOWN_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_LEFT)
      snake.setDir(_LEFT_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_RIGHT)
      snake.setDir(_RIGHT_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::PLAY)
    {
      snake.getDir() == _UP_ ? snake.go_up() : snake.getDir() == _DOWN_ ? snake.go_down() :
    snake.getDir() == _RIGHT_ ? snake.go_right() : snake.go_left();

    }
    if (wai)
      delete wai;
    if (gmap)
      delete gmap;
  }

}

extern "C" IGame				*create_igame(void)
{
  return new Snake();
}

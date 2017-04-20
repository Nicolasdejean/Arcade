//
// Pacman.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/Game
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Wed Mar 29 16:42:16 2017 benjamin girard
// Last update Sun Apr  9 22:49:28 2017 benjamin girard
//

#include "includes/Pacman.hpp"
#include "includes/GhostBlue.hpp"
#include "includes/GhostRed.hpp"
#include "includes/GhostYellow.hpp"
#include "includes/GhostPink.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>
#include <random>

Pacman::Pacman(void) :
  _packi(START_PACKI_POS, PACKI_DRAWER, PACMAN_HEAD)
{
  init_map();
  _level = 1;
  _pause = false;
}

Pacman::~Pacman(void) {}

void					Pacman::init_map(void)
{
  this->_ghosts.clear();
  _ghosts.push_back(std::unique_ptr<AGhost>(new GhostBlue(GHOST_START_POS, GHOSTBLUE_DRAWER, PACMAN_GHOST_BLUE)));
  _ghosts.push_back(std::unique_ptr<AGhost>(new GhostRed(GHOST_START_POS, GHOSTRED_DRAWER, PACMAN_GHOST_RED)));
  _ghosts.push_back(std::unique_ptr<AGhost>(new GhostYellow(GHOST_START_POS, GHOSTYELLOW_DRAWER, PACMAN_GHOST_YELLOW)));
  _ghosts.push_back(std::unique_ptr<AGhost>(new GhostPink(GHOST_START_POS, GHOSTPINK_DRAWER, PACMAN_GHOST_PINK)));
}

void					Pacman::init(uint16_t width, uint16_t height,
						    const std::string &name)
{
  this->_width = width;
  this->_height = height;
  this->_scores.init(name, name + SCORE_EXT);
  this->_map = MAP;
  this->_packi = Packi(START_PACKI_POS, PACKI_DRAWER, PACMAN_HEAD);
  this->_level = 1;
  this->_pause = false;
  init_map();
}

const arcade::WhereAmI			*Pacman::where_am_i(void) const
{
  auto me = (arcade::WhereAmI *) ::operator new
    (sizeof(arcade::WhereAmI) + (sizeof(arcade::Position)));

  me->type = arcade::CommandType::WHERE_AM_I;
  me->lenght = 1;
  me->position[0].x = this->_packi.getPos().x;
  me->position[0].y = this->_packi.getPos().y;
  return (me);
}

const arcade::GetMap			*Pacman::get_map(void) const
{
  auto map = (arcade::GetMap *) ::operator new
    (sizeof(arcade::GetMap) + (sizeof(arcade::TileType) * this->_map.size()));
  map->type = arcade::CommandType::GET_MAP;
  map->width = this->_width;
  map->height = this->_height;

  auto i = 0;
  for (auto &it : _map)
    map->tile[i++] = it;
  return (map);
}

double					Pacman::count_time(std::chrono::high_resolution_clock::time_point t1)
{
  double				t_to_sleep =
    BASIC_TIME_P - (std::chrono::duration_cast<std::chrono::duration<double> >
		  (std::chrono::high_resolution_clock::now() - t1)).count();

   return (t_to_sleep);
}

bool					Pacman::isPackiDead(void)
{
  auto					packi_pos = this->_packi.getPos();
  arcade::Position			ghost_pos;

  for (auto &it : this->_ghosts) {
    ghost_pos = it->getPos();
    if (packi_pos.x == ghost_pos.x && packi_pos.y == ghost_pos.y && it->getSlow() == 0)
      return (true);
    else if (packi_pos.x == ghost_pos.x && packi_pos.y == ghost_pos.y && it->getSlow() > 0) {
      this->_scores += TIME_DEAD;
      it->kill();
    }
  }
  return (false);
}

void					Pacman::eatPacGum(void)
{
  auto					packi_pos = this->_packi.getPos();
  auto					idx = packi_pos.y * WIDTH_PACMAP + packi_pos.x;

  if (this->_map[idx] == arcade::TileType::OTHER) {
    this->_scores += 1;
    this->_map[idx] = arcade::TileType::EMPTY;
  }
  else if (this->_map[idx] == arcade::TileType::POWERUP) {
    this->_map[idx] = arcade::TileType::EMPTY;
    this->_scores += 10;
    for (auto &it : this->_ghosts)
      it->slow();
  }
}

bool					Pacman::no_more_pacgum(void)
{
  for (auto &it : this->_map)
    if (it == arcade::TileType::OTHER || it == arcade::TileType::POWERUP)
      return (false);
  return (true);
}

void					Pacman::next_level(void)
{
  auto save_score = this->_scores.getScore();
  auto save_level = this->_level;

  this->_scores.updateHighScore();
  this->init(this->_width, this->_height, this->_scores.getUserName());
  this->_scores += save_score;
  this->_level = save_level + 1;
}

void					Pacman::play(IGraph &graph)
{
  display_pacman(graph);
  if (isPackiDead()) {
      this->_scores.updateHighScore();
      display_game_over(graph);
  }
  else if (this->_pause == false) {
    eatPacGum();
    if (this->_packi.getBuffer() != this->_packi.getDir())
      this->change_direction(this->_packi.getBuffer());
    this->_packi.move(this->_map);
    if (!isPackiDead()) {
      if (no_more_pacgum())
	next_level();
      else
	for (auto &it : this->_ghosts)
	  it->move(this->_map);
    }
  }
  else
    display_pause(graph);
  auto						level_time = BASIC_TIME_P - (this->_level * 10);
  std::this_thread::sleep_for(std::chrono::milliseconds(level_time < 30 ? 30 : level_time));
}

e_status				Pacman::is_over(void)
{
  return (ALIVE);
}

extern "C" void					Play(void)
{
  Pacman					pacman;
  uint16_t					cmd;

  pacman.init(200, 200, "");
  while (read(0, &cmd, sizeof(arcade::CommandType)))
  {
    const arcade::WhereAmI			*wai = pacman.where_am_i();
    const arcade::GetMap			*gmap = pacman.get_map();
    auto					size_map =
      (sizeof(arcade::GetMap) + (sizeof(arcade::TileType) * pacman.getWidth() * pacman.getHeight()));
    auto					size_wai =
      (sizeof(struct arcade::WhereAmI) + sizeof(struct arcade::Position));

    if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::WHERE_AM_I)
      write(1, wai, size_wai);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GET_MAP)
      write(1, gmap, size_map);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_UP)
      pacman.setDir(_UP_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_DOWN)
      pacman.setDir(_DOWN_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_LEFT)
      pacman.setDir(_LEFT_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::GO_RIGHT)
      pacman.setDir(_RIGHT_);
    else if (static_cast<arcade::CommandType>(cmd) == arcade::CommandType::PLAY) {
      pacman.getDir() == _UP_ ? pacman.go_up() : pacman.getDir() == _DOWN_ ? pacman.go_down() :
	pacman.getDir() == _RIGHT_ ? pacman.go_right() : pacman.go_left();
    }
    if (wai)
      delete wai;
    if (gmap)
      delete gmap;
  }
}

extern "C" IGame				*create_igame(void)
{
  return new Pacman();
}

//
// Pacman_new.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Wed Mar 29 12:09:15 2017 benjamin girard
// Last update Sun Apr  9 22:49:06 2017 benjamin girard
//

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Pacman_map.hpp"
#include "Packi.hpp"
#include "AGhost.hpp"
#include "../../includes/Protocol.hpp"
#include "../../includes/IGame.hpp"
#include "../../scores/includes/Scores.hpp"

static std::map<arcade::TileType, t_drawer> COLOR_MAP = {
  {arcade::TileType::BLOCK, {79, 117, 255, _BLUE_, ' '}},
  {arcade::TileType::OTHER, {255, 255, 255, _WHITE_, '.'}},
  {arcade::TileType::POWERUP, {251, 179, 255, _GREEN_, 'o'}},
  {arcade::TileType::EMPTY, {0, 0, 0, _BLACK_, ' '}}
};


static const char				GAMEOVER_P[10] = "Game Over";
static const char				LEVEL_P[6] = "Level";
static const char				PAUSE_P[6] = "Pause";

static const char				RETRY_P[19] = "Press 8 to retry !";
static const std::string			PATH_PACMAN_SCORES = "./scores/";

static const uint16_t				WIDTH_PACMAP = 27;

static const arcade::Position			START_PACKI_POS = {13, 17};

static const int				BASIC_TIME_P = 100;

class							Pacman : public IGame
{
private:
  Packi							_packi;
  std::vector<arcade::TileType>				_map;
  std::vector< std::unique_ptr<AGhost> >		_ghosts;

  uint16_t						_width;
  uint16_t						_height;

  Scores						_scores;
  uint16_t						_level;

  bool							_pause;

  Pacman(const Pacman & /* cp */);
  Pacman							&operator=(const Pacman & /* cp */) { return *this; }

  double						count_time (std::chrono::high_resolution_clock::time_point t1);
public:
  Pacman(void);
  virtual ~Pacman(void);

  virtual void						init(uint16_t width, uint16_t height, const std::string &name);

  virtual const arcade::WhereAmI			*where_am_i(void) const;
  virtual const arcade::GetMap				*get_map(void) const;

  virtual void						shoot(void) {}
  virtual void						illegal(void) {}
  virtual void						play(IGraph &graph);

  virtual e_status					is_over(void);

  /*
  ** Move functions
  */

  virtual void						change_direction(Input input);
  virtual void						go_up(void);
  virtual void						go_down(void);
  virtual void						go_left(void);
  virtual void						go_right(void);
  virtual void						go_forward(void) const;

  /*
  ** Drawing functions
  */

  void							draw_scores(IGraph &graph) const;
  void							draw_characters(IGraph &graph) const;
  void							draw_map(IGraph &graph) const;
  void							display_pacman(IGraph &graph) const;

  void							display_game_over(IGraph &graph) const;

  void							display_pause(IGraph &graph) const;

  /*
  ** Member functions
  */

  void							init_map(void);

  bool							isPackiDead(void);
  bool							no_more_pacgum(void);
  void							next_level(void);
  void							eatPacGum(void);


  Input							getDir(void) const {return (this->_packi.getDir());}
  void							setDir(Input input) {this->_packi.changeDir(input);}

  uint16_t						getWidth(void) const {return (this->_width);}
  uint16_t						getHeight(void) const {return (this->_height);}
};

#endif /* !PACMAN_HPP_ */

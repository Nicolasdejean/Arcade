//
// Snake_new.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Wed Mar 29 12:09:15 2017 benjamin girard
// Last update Sun Apr  9 22:50:19 2017 benjamin girard
//

#ifndef SNAKE_HPP_
# define SNAKE_HPP_

#include <list>
#include <vector>
#include <map>
#include <stddef.h>
#include <chrono>
#include "../../includes/Ressources.hpp"
#include "../../includes/IGame.hpp"
#include "../../scores/includes/Scores.hpp"

static const char				SIZE_SNAKE_DEF = 4;
static const char				LEVEL[6] = "Level";
static const char				PAUSE_S[6] = "Pause";
static const char				GAMEOVER[10] = "Game Over";
static const char				RETRY[19] = "Press 8 to retry !";
static const std::string			PATH_SNAKE_SCORES = "./scores/";

static const int				BASIC_TIME_S = 120;

static const std::vector<t_a_color>		RAINBOW = {
  {148, 0, 211, _RED_}, {137, 0, 199, _RED_}, {127, 0, 187, _RED_},
  {116, 0, 176, _RED_}, {106, 0, 164, _RED_}, {95, 0, 153, _RED_},
  {85, 0, 141, _RED_}, {66, 0, 143, _RED_}, {58, 0, 157, _RED_}, {50, 0, 171, _RED_},
  {41, 0, 185, _YELLOW_}, {33, 0, 199, _YELLOW_}, {25, 0, 213, _YELLOW_},
  {16, 0, 227, _YELLOW_}, {8, 0, 241, _YELLOW_}, {0, 0, 255, _YELLOW_},
  {0, 56, 255, _YELLOW_}, {0, 113, 255, _YELLOW_}, {0, 169, 255, _YELLOW_}, {0, 226, 255, _YELLOW_},
  {0, 255, 226, _GREEN_}, {0, 255, 169, _GREEN_}, {0, 255, 113, _GREEN_},
  {0, 255, 56, _GREEN_}, {0, 255, 0, _GREEN_}, {28, 255, 0, _GREEN_},
  {56, 255, 0, _GREEN_}, {85, 255, 0, _GREEN_}, {113, 255, 0, _GREEN_}, {141, 255, 0, _GREEN_},
  {170, 255, 0, _CYAN_}, {198, 255, 0, _CYAN_}, {226, 255, 0, _CYAN_},
  {255, 255, 0, _CYAN_}, {255, 240, 0, _CYAN_}, {255, 226, 0, _CYAN_},
  {255, 212, 0, _CYAN_}, {255, 198, 0, _CYAN_}, {255, 183, 0, _CYAN_}, {255, 169, 0, _CYAN_},
  {255, 155, 0, _BLUE_}, {255, 141, 0, _BLUE_},{255, 127, 0, _BLUE_},
  {255, 112, 0, _BLUE_}, {255, 98, 0, _BLUE_}, {255, 84, 0, _BLUE_},
  {255, 70, 0, _BLUE_}, {255, 56, 0, _BLUE_}, {255, 42, 0, _BLUE_}, {255, 28, 0, _BLUE_},
  {255, 14, 0, _MAGENTA_}, {255, 0, 0, _MAGENTA_}, {255, 0, 18, _MAGENTA_}, {255, 0, 36, _MAGENTA_},
  {255, 0, 54, _MAGENTA_}, {255, 0, 72, _MAGENTA_}, {255, 0, 90, _MAGENTA_}, {255, 0, 108, _MAGENTA_},
  {255, 0, 126, _MAGENTA_}, {255, 0, 144, _MAGENTA_}, {255, 0, 163, _MAGENTA_}
};

static std::map<arcade::TileType, t_drawer>		MAP_COLOR = {
  {arcade::TileType::BLOCK, {{MAX_PRIMARY, MAX_PRIMARY, MAX_PRIMARY, _WHITE_}, '|'}},
  {arcade::TileType::POWERUP, {{211, 142, 145, _MAGENTA_}, '|'}}
};

class							Snake : public IGame
{
private:
  std::list<arcade::Position>				_me;
  std::vector<arcade::TileType>				_map;
  arcade::Position					_food_pos;

  uint16_t						_width;
  uint16_t						_height;

  Input							_dir;

  bool							_pause;

  Scores						_scores;

  uint16_t						_idx_food;

  Snake(const Snake & /* cp */) {}
  Snake							&operator=(const Snake & /* cp */) { return *this; }

  double						count_time(std::chrono::high_resolution_clock::time_point t1);
public:
  Snake(void);
  virtual ~Snake(void);

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
  virtual void						go_forward(void) const {}

  /*
  ** Drawing functions
  */

  void							draw_map(IGraph &graph) const;
  void							draw_scores(IGraph &graph) const;
  void							draw_body(IGraph &graph) const;
  void							draw_snake(IGraph &graph) const;

  void							draw_game_over(IGraph &graph) const;
  void							draw_retry(IGraph &graph) const;
  e_status						draw_end_game(IGraph &graph) const;

  void							display_pause(IGraph &graph) const;

  /*
  ** Member functions
  */

  bool							is_pos_in_me(uint16_t y, uint16_t x) const;
  e_status						generate_food(void);

  void							setDir(Input dir);
  Input							getDir(void) const;
  uint16_t						getWidth(void) const;
  uint16_t						getHeight(void) const;
  const std::list<arcade::Position>			&getMe(void) const;

};

#endif /* !SNAKE_HPP_ */

//in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Mon Apr  3 16:29:19 2017 benjamin girard
// Last update Sun Apr  9 20:12:22 2017 benjamin girard
//

#include <random>
#include "includes/Snake.hpp"

void					Snake::draw_map(IGraph &graph) const
{
    t_drawer				draw = { { 0, 0, 0, _BLACK_ }, ' '};
    auto					size = this->_map.size();

    for (uint16_t i = 0; i < size; i++) {
	draw.color = MAP_COLOR[this->_map[i]].color;
	if (this->_map[i] == arcade::TileType::POWERUP) {{
	    graph.draw_sprite(arcade::Position {static_cast<uint16_t>(i % this->_width),
		static_cast<uint16_t>(i / this->_width)},
	    draw, NIBBLER_FOOD[this->_idx_food]);
	}}
	else if (this->_map[i] != arcade::TileType::EMPTY)
	  graph.draw_sprite(arcade::Position {static_cast<uint16_t>(i % this->_width),
		static_cast<uint16_t>(i / this->_width)}, draw, NIBBLER_WALL);
	else if (this->_map[i] == arcade::TileType::EMPTY && i > this->_width)
	  graph.draw_sprite(arcade::Position {static_cast<uint16_t>(i % this->_width),
		static_cast<uint16_t>(i / this->_width)}, draw, NIBBLER_BACKGROUND);

    }
}

void					Snake::draw_body(IGraph &graph) const
{
  auto					size = this->_me.size();
  auto					rainbow_size = RAINBOW.size();
  t_drawer				draw = { { 0, 0, 0, _BLACK_}, ' '};
  size_t inc				= (rainbow_size / size) == 0 ?
    (1) : (rainbow_size / size);

  auto					i = 0;
  for (auto it = this->_me.begin(); it != this->_me.end(); ++it)
  {
      draw.color = RAINBOW[i];
      i = (i + inc) >= rainbow_size ?
	  ((i + inc) % rainbow_size) : (i + inc);
      if (it == this->_me.begin())
      {
	  if (this->_dir == _UP_)
	      graph.draw_sprite(*it, draw, NIBBLER_HEAD_UP);
	  if (this->_dir == _DOWN_)
	      graph.draw_sprite(*it, draw, NIBBLER_HEAD_DOWN);
	  if (this->_dir == _RIGHT_)
	      graph.draw_sprite(*it, draw, NIBBLER_HEAD_RIGHT);
	  if (this->_dir == _LEFT_)
	      graph.draw_sprite(*it, draw, NIBBLER_HEAD_LEFT);
      }
      else
	graph.draw_sprite(*it, draw, NIBBLER_BODY[(this->_scores.getScore() / 10) % (NIBBLER_BODY.size() -1)]);
  }
}

void					Snake::draw_scores(IGraph &graph) const
{
  static const t_a_color		text_color = {255, 255, 255, _WHITE_};
  static const arcade::Position		username_pos = arcade::Position {1, 0};
  static const arcade::Position		score_pos =
    arcade::Position {static_cast<uint16_t>((this->_width / 2 - 11)), 0};
  static const arcade::Position		nscore_pos =
    arcade::Position {static_cast<uint16_t>((this->_width / 2 - 16)), 0};
  static const arcade::Position		highscore_pos =
    arcade::Position {static_cast<uint16_t>(this->_width / 2 + 7), 0};
  static const arcade::Position		nhighscore_pos =
    arcade::Position {static_cast<uint16_t>(this->_width / 2 -1), 0};
  static const arcade::Position		level_pos =
    arcade::Position {static_cast<uint16_t>(this->_width / 2 + 23), 0};
  static const arcade::Position		nlevel_pos =
    arcade::Position {static_cast<uint16_t>(this->_width / 2 + 18), 0};


  graph.draw_text(username_pos, this->_scores.getUserName(), 0, text_color);
  graph.draw_text(nscore_pos, SCORE, 0, text_color);
  graph.draw_text(score_pos, std::to_string(this->_scores.getScore()), 0, text_color);
  graph.draw_text(nhighscore_pos, HIGHSCORE, 0, text_color);
  graph.draw_text(highscore_pos,
		   std::stoi(this->_scores.getHighScore()) < this->_scores.getScore() ?
		   std::to_string(this->_scores.getScore()) : (this->_scores.getHighScore()),
		   0, text_color);
  graph.draw_text(nlevel_pos, LEVEL, 0, text_color);
  graph.draw_text(level_pos, std::to_string(this->_scores.getScore() / 10 + 1), 0, text_color);
}

void					Snake::draw_snake(IGraph &graph) const
{
  draw_map(graph);
  draw_scores(graph);
  draw_body(graph);
}

void					Snake::display_pause(IGraph &graph) const
{
  auto					x = (this->_width / 2) - (sizeof(PAUSE_S) / 2);
  std::string				tmp(" ");

  for (size_t i = 0; i < sizeof(PAUSE_S) - 1; i++) {
    tmp[0] = PAUSE_S[i];
    graph.draw_text(
      arcade::Position {static_cast<uint16_t>(x + i),
	  static_cast<uint16_t>((this->_height / 2) - 1)},
      std::string(&tmp[0]),
      0,
      RAINBOW[i * ((RAINBOW.size() / (sizeof(PAUSE_S) - 1)))]
    );
  }

}

void					Snake::draw_game_over(IGraph &graph) const
{
  auto					x = (this->_width / 2) - (sizeof(GAMEOVER) / 2);
  std::string				tmp(" ");

  for (size_t i = 0; i < sizeof(GAMEOVER) - 1; i++) {
    tmp[0] = GAMEOVER[i];
    graph.draw_text(
      arcade::Position {static_cast<uint16_t>(x + i),
	  static_cast<uint16_t>((this->_height / 2) - 1)},
      std::string(&tmp[0]),
      0,
      RAINBOW[i * ((RAINBOW.size() / (sizeof(GAMEOVER) - 1)))]
    );
  }

}

void					Snake::draw_retry(IGraph &graph) const
{
  auto					x = (this->_width / 2) - (sizeof(RETRY) / 2);
  std::string				tmp(" ");


  for (size_t i = 0; i < sizeof(RETRY) - 1; i++) {
    tmp[0] = RETRY[i];
    graph.draw_text(
      arcade::Position {static_cast<uint16_t>(x + i),
	  static_cast<uint16_t>((this->_height / 2) + 1)},
      std::string(&tmp[0]),
      0,
      RAINBOW[i * ((RAINBOW.size() / (sizeof(RETRY) - 1)))]
    );
  }
}

e_status				Snake::draw_end_game(IGraph &graph) const
{
  draw_game_over(graph);
  draw_retry(graph);
  return (DEAD);
}

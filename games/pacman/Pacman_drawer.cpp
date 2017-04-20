//
// pacman_drawer.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Fri Apr  7 11:10:09 2017 benjamin girard
// Last update Sun Apr  9 20:36:59 2017 benjamin girard
//

#include "includes/Pacman.hpp"

void					Pacman::draw_map(IGraph &graph) const
{
  auto					size = this->_map.size();

  for (uint16_t i = 0; i < size; i++) {
      if (this->_map[i] == arcade::TileType::BLOCK)
	graph.draw_sprite(arcade::Position {static_cast<uint16_t>(i % (WIDTH_PACMAP)),
		    static_cast<uint16_t>(i / (WIDTH_PACMAP))}, COLOR_MAP[this->_map[i]],
	    PACMAN_WALL);

      else if (this->_map[i] == arcade::TileType::POWERUP)
	      graph.draw_sprite(arcade::Position {static_cast<uint16_t>(i % (WIDTH_PACMAP)),
			  static_cast<uint16_t>(i / (WIDTH_PACMAP))}, COLOR_MAP[this->_map[i]],
		  PACMAN_POWERUP);

      else if (this->_map[i] == arcade::TileType::OTHER)
	  graph.draw_sprite(arcade::Position {static_cast<uint16_t>(i % (WIDTH_PACMAP)),
		      static_cast<uint16_t>(i / (WIDTH_PACMAP))}, COLOR_MAP[this->_map[i]],
	      PACMAN_FOOD);

  }
}

void					Pacman::draw_characters(IGraph &graph) const
{
  const std::string			path_dir =
    this->_packi.getDir() == _RIGHT_ ? PACMAN_RIGHT :
    this->_packi.getDir() == _UP_ ? PACMAN_UP :
    this->_packi.getDir() == _DOWN_ ? PACMAN_DOWN : PACMAN_LEFT;

  graph.draw_sprite(this->_packi.getPos(),
		      this->_packi.getSprite(), path_dir);

    for (auto &it : this->_ghosts) {
	graph.draw_sprite(it->getPos(),
			  it->getSlow() > 0 ? WEAK_GHOST_DRAWER : it->getSprite(),
			  it->getSlow() > 0 ? PACMAN_GHOST_SLOW : it->getPath());
  }
}

void					Pacman::draw_scores(IGraph &graph) const
{
  static const t_a_color                text_color = {255, 255, 255, _WHITE_};
  static const arcade::Position         score_pos =
    arcade::Position {static_cast<uint16_t>((WIDTH_PACMAP / 2 - 3)), 0};
  static const arcade::Position         nscore_pos =
    arcade::Position {static_cast<uint16_t>((WIDTH_PACMAP / 2 - 7)), 0};
  static const arcade::Position         highscore_pos =
    arcade::Position {static_cast<uint16_t>(WIDTH_PACMAP / 2 + 7), 0};
  static const arcade::Position         nhighscore_pos =
    arcade::Position {static_cast<uint16_t>(WIDTH_PACMAP / 2), 0};
  static const arcade::Position         username_pos = arcade::Position {1, 0};
  static const arcade::Position         level_pos =
    arcade::Position {static_cast<uint16_t>(WIDTH_PACMAP / 2 + 15), 0};
  static const arcade::Position         nlevel_pos =
    arcade::Position {static_cast<uint16_t>(WIDTH_PACMAP / 2 + 10), 0};

  graph.draw_text(username_pos, this->_scores.getUserName(), 0, text_color);
  graph.draw_text(nscore_pos, SCORE, 0, text_color);
  graph.draw_text(score_pos, std::to_string(this->_scores.getScore()), 0, text_color);
  graph.draw_text(nhighscore_pos, HIGHSCORE, 0, text_color);
  graph.draw_text(highscore_pos,
  		  std::stoi(this->_scores.getHighScore()) < this->_scores.getScore() ?
  		  std::to_string(this->_scores.getScore()) : (this->_scores.getHighScore()),
  		  0, text_color);
  graph.draw_text(nlevel_pos, LEVEL_P, 0, text_color);
  graph.draw_text(level_pos, std::to_string(this->_level), 0, text_color);
}

void					Pacman::display_pacman(IGraph &graph) const
{
  draw_map(graph);
  draw_characters(graph);
  draw_scores(graph);
}

void					Pacman::display_pause(IGraph &graph) const
{
  static const t_a_color		PAUSE_COLOR = {250, 41, 10, _RED_};
  static const arcade::Position		PAUSE_PACMAN_POS = {11, 17};
  std::string				tmp(" ");

  for (size_t i = 0; i < sizeof(PAUSE_P) - 1; i++) {
    tmp[0] = PAUSE_P[i];
    graph.draw_text(
      arcade::Position{static_cast<uint16_t>(PAUSE_PACMAN_POS.x + i), PAUSE_PACMAN_POS.y},
      std::string(&tmp[0]),
      0,
      PAUSE_COLOR
      );
  }
}

void					Pacman::display_game_over(IGraph &graph) const
{
  static const t_a_color		GAMEOVER_COLOR = {250, 41, 10, _RED_};
  static const arcade::Position		GAMEOVER_PACMAN_POS = {9, 17};
  std::string                           tmp(" ");

  for (size_t i = 0; i < sizeof(GAMEOVER_P) - 1; i++) {
    tmp[0] = GAMEOVER_P[i];
    graph.draw_text(
      arcade::Position{static_cast<uint16_t>(GAMEOVER_PACMAN_POS.x + i), GAMEOVER_PACMAN_POS.y},
      std::string(&tmp[0]),
      0,
      GAMEOVER_COLOR
      );
  }
}

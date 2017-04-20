//
// Score.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/scores
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Tue Apr  4 10:13:37 2017 benjamin girard
// Last update Thu Apr  6 10:48:26 2017 benjamin girard
//

#include "includes/Scores.hpp"

Scores::Scores(void) {}

void					Scores::init(const std::string &name, const std::string &path)
{
  this->_path = path;
  _username = name;
  _highScore = loadHighScore();
  _score = 0;
}

Scores::~Scores(void) {}

std::string				Scores::loadHighScore(void)
{
  std::ifstream				file(this->_path);
  std::string				tmp;

  if (file.is_open())
  {
    getline(file, tmp);
    return (tmp == "" ? "0" : tmp);
  }
  return ("0");
}

int					Scores::getScore(void) const
{
  return (this->_score);
}

void					Scores::incScore(size_t inc)
{
  this->_score += inc;
}

Scores					&Scores::operator+=(size_t inc)
{
  this->_score += inc;
  return (*this);
}

void					Scores::updateHighScore(void)
{
  std::ofstream				file(this->_path);
  std::string				tmp;

  tmp = this->_score > std::stoi(this->_highScore) ? std::to_string(this->_score) : this->_highScore;
  file << tmp;
}

//
// Scores.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/scores/includes
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Tue Apr  4 10:13:59 2017 benjamin girard
// Last update Fri Apr  7 11:04:57 2017 benjamin girard
//

#ifndef SCORE_HPP_
# define SCORE_HPP_

#include <fstream>
#include <string>

static const std::string		HIGHSCORE = "Highscore: ";
static const std::string		SCORE = "Score: ";
static const std::string		SCORE_EXT = ".pacman";

class					Scores
{
private:
  std::string				_username;
  int					_score;
  std::string				_highScore;
  std::string				_path;

private:
  Scores				&operator=(Scores const & /* cp */) {return *this;};
  Scores(const Scores &/* cp */) {}

public:
  Scores(void);
  ~Scores(void);

  void					init(const std::string &name, const std::string &path);

  std::string				loadHighScore(void);

  const std::string			&getHighScore(void) const { return (this->_highScore); }
  const std::string			&getUserName(void) const { return (this->_username); }
  int					getScore(void) const;


  void					incScore(size_t inc);
  Scores				&operator+=(size_t inc);

  void					updateHighScore(void);

};

# endif /* !SCORE_HPP_ */

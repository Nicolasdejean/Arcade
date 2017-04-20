//
// ACharacter.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/games/pacman/includes
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Fri Apr  7 22:10:57 2017 benjamin girard
// Last update Sun Apr  9 18:55:41 2017 benjamin girard
//


#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

#include "../../includes/Protocol.hpp"
#include "../../../Graph/includes/IGraph.hpp"
#include "../../includes/IGame.hpp"
#include "../../includes/Ressources.hpp"

static const uint16_t			PACMAP_WIDTH = 27;
static const char			NB_GHOSTS = 4;

static const arcade::Position		GHOST_START_POS = {13, 14};
static const arcade::Position		GHOST_ENTRY_POS = {13, 13};

static const uint16_t			TIME_SLOW = 80;
static const uint16_t			TIME_DEAD = 25;

static const t_drawer			WEAK_GHOST_DRAWER = {
  {0, 75, 130, _GREEN_},
  'u'
};

enum					e_char_type
{
  PACMAN,
  GHOST
};

class					ACharacter
{

protected:
  arcade::Position			_pos;
  Input					_dir;

  t_drawer				_sprite;
  std::string				_path_s;

  ACharacter				&operator=(const ACharacter &/* cp */)
    {return (*this);}


public:
  ACharacter(const arcade::Position &pos, const t_drawer &sprite, const std::string &path);
  ACharacter(const ACharacter &cp);
  virtual ~ACharacter(void) {}

  const arcade::Position		&getPos(void) const {return (this->_pos);}

  virtual void				move(const std::vector<arcade::TileType> &map) = 0;

  virtual void				changeDir(Input input) {this->_dir = input;}

  virtual const std::string		&getPath(void) const {return (this->_path_s);}
  virtual Input				getDir(void) const {return (this->_dir);}
  virtual t_drawer			getSprite(void) const {return (this->_sprite);}
};

#endif /* !ACHARACTER_HPP_ */

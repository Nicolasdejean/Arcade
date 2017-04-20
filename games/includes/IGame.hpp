//
// IGame.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Wed Mar 29 11:43:07 2017 benjamin girard
// Last update Sun Apr  9 22:48:04 2017 benjamin girard
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include "Protocol.hpp"
#include "../../Graph/includes/IGraph.hpp"

enum					e_status
{
  ALIVE,
  DEAD,
  WINNER
};



class					IGame
{
public:
  virtual ~IGame(void) {}

  virtual const arcade::WhereAmI	*where_am_i(void) const = 0;
  virtual const arcade::GetMap		*get_map(void) const = 0;

  virtual void				go_up(void) = 0;
  virtual void				go_down(void) = 0;
  virtual void				go_left(void) = 0;
  virtual void				go_right(void) = 0;
  virtual void				go_forward(void) const = 0;

  virtual void				shoot(void) = 0;
  virtual void				illegal(void) = 0;
  virtual void				play(IGraph &graph) = 0;


  // last updates
  virtual void				change_direction(Input input) = 0;
  virtual e_status			is_over(void) = 0;

  virtual void				init(uint16_t width, uint16_t height, const std::string &name) = 0;
};

#endif /* !IGAME_HPP_ */

//
// Igraph.hpp for arcade in /home/margue_m/rendu/cpp_arcade/include
//
// Made by Mattéo Margueritte
// Login   <margue_m@epitech.net>
//
// Started on  Fri Mar 17 17:01:29 2017 Mattéo Margueritte
// Last update Sat Apr  1 20:35:28 2017 benjamin girard
//

#ifndef IGRAPH_HPP_
# define IGRAPH_HPP_

# include <stddef.h>
# include <vector>
# include <string>
# include "../../games/includes/Protocol.hpp"



static const unsigned char MAX_PRIMARY = 255;

static const char SIZE_CELL = 30;

/*
** Pair object represents a Cell in the window
** The size of a Cell is up to you (the size must be descent)
** Example : A character for ASCII Library || A 5pixels square in graphical libraries
*/

typedef enum				Input
  {
    _ONE_,
    _TWO_,
    _THREE_,
    _FOUR_,
    _FIVE_,
    _SIX_,
    _SEVEN_,
    _EIGHT_,
    _NINE_,
    _ENTER_,
    _SPACE_,
    _ESCAPE_,
    _UP_,
    _LEFT_,
    _DOWN_,
    _RIGHT_,
    _UNDEFINED_
  }					Input;

typedef enum				color_type
  {
    _BLACK_ = 0,
    _RED_,
    _GREEN_,
    _YELLOW_,
    _BLUE_,
    _MAGENTA_,
    _CYAN_,
    _WHITE_
  }					color_type;

struct					t_a_color
{
  unsigned char				R;
  unsigned char				G;
  unsigned char				B;
  color_type				color;
};

struct					t_drawer
{
  t_a_color				color;
  unsigned char				character;
};

class					IGraph
{
public:
  virtual ~IGraph(void) {}

  /*
  ** Windows methods methods
  */

  virtual std::pair<uint16_t, uint16_t>	create_window(uint16_t width, uint16_t height) = 0;
  virtual void				close_window(void) = 0;

  /*
  ** Draw methods
  */

  virtual void				draw_rectangle(const arcade::Position &point,
						       const t_a_color &color) = 0;

  virtual void				draw_text(const arcade::Position &point,
						  const std::string &text,
						  const size_t size,
						  const t_a_color &color) = 0;

  /*
  ** Vectors are drawn with lines between two points. (first Point == last Point)
  */

  virtual void				draw_shape(const std::vector<arcade::Position> &lpoint,
						   const t_a_color &color) = 0;


  /*
  ** Screen frames methods
  */

  virtual void				a_clear(void) = 0;
  virtual void				a_refresh(void) = 0;

  /*
  ** Window status
  */

  virtual bool				isOpen(void) const = 0;

  /*
  ** Input Handling
  */

  virtual Input				checkInput(void) = 0;

  virtual void				draw_sprite(const arcade::Position &point,
						    const t_drawer& draw,
						    const std::string &path) = 0;

};

#endif //IGRAPH_HPP_

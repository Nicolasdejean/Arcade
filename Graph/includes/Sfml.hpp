//
// Sfml.hpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Mar 18 17:37:52 2017 benjamin girard
// Last update Sat Apr  1 20:01:35 2017 benjamin girard
//

#ifndef SFML_HPP_
# define SFML_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "IGraph.hpp"
#include "../../games/includes/Ressources.hpp"

class					Sfml : public IGraph
{
private:
  size_t				_width;
  size_t				_height;
  size_t				_width_cell;
  size_t				_height_cell;

  sf::RenderWindow			*_win;
  sf::Event				_event;
  sf::Font				_font;

    std::unordered_map<std::string, sf::Texture>	_sprite;


    Sfml(Sfml const &/* cp */) {}
  Sfml					&operator=(Sfml const &/* cp */)
    {return (*this);}


public:
  Sfml(void) {}
  virtual ~Sfml(void);

  /*
  ** Windows methods
  */

  virtual std::pair<uint16_t, uint16_t>	create_window(uint16_t width, uint16_t height);
  virtual void				close_window(void);


  /*
  ** Draw methods
  */

  virtual void				draw_rectangle(const arcade::Position &point,
						       const t_a_color &color);

  virtual void				draw_text(const arcade::Position &point,
						  const std::string &text,
						  const size_t size,
						  const t_a_color &color);

  /*
  ** Vectors are drawn with lines between two points. (first Point == last Point)
  */

  virtual void				draw_shape(const std::vector<arcade::Position> &lpoint,
						   const t_a_color &color);

  /*
  ** Screen frames methods
  */

  virtual void				a_clear(void);
  virtual void				a_refresh(void);

  /*
  ** Window status
  */

  virtual bool				isOpen(void) const;

  /*
  ** Input Handling
  */

  virtual Input				checkInput(void);

  /*
  ** Sprite
  */

    virtual void			draw_sprite(const arcade::Position &point,
						    const t_drawer& draw,
						    const std::string &path);
};

#endif /* SFML_HPP_ */

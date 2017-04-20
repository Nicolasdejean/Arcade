#ifndef OPENGL_HPP_
#define OPENGL_HPP_

#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <map>
#include <unordered_map>
#include "../../games/includes/Ressources.hpp"
#include "IGraph.hpp"

class						Opengl : public IGraph
{
private:
    uint16_t					_height;
    uint16_t					_width;
    sf::RenderWindow				*_win;
    sf::Font					_font;
    bool					is_open;

    Opengl(Opengl const &/* cp */) {}
    Opengl                                  &operator=(Opengl const &/* cp */)
	{return (*this);}

public:
    virtual std::pair<uint16_t, uint16_t>	create_window(uint16_t width, uint16_t height);
    virtual void				close_window(void);

    virtual void				draw_rectangle(const arcade::Position &point,
       							       const t_a_color &color);
    virtual void				draw_text(const arcade::Position &point,
    							  const std::string &text,
    							  const size_t size,
    							  const t_a_color &color);

    virtual void				draw_shape(const std::vector<arcade::Position> &lpoint,
    							   const t_a_color &color);

    virtual void				a_clear(void);
    virtual void				a_refresh(void);

    virtual bool				isOpen(void) const;

    virtual Input				checkInput(void);

    virtual void				draw_sprite(const arcade::Position &point,
								const t_drawer& draw,
								const std::string &path);

public:
    Opengl(void) {};
    virtual ~Opengl(void);
};

#endif /* !OPENGL_HPP_ */

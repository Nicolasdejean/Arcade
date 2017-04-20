#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <map>
#include <ncurses.h>
#include "IGraph.hpp"

#define _KEY_ESC_ 27

class						Ncurses : public IGraph
{
private:
    WINDOW					*win;
    bool					is_open;

    Ncurses(Ncurses const &/* cp */) {}
    Ncurses                                  &operator=(Ncurses const &/* cp */)
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
    Ncurses(void) {};
    virtual ~Ncurses(void) {};
};

#endif /* !NCURSES_HPP_ */

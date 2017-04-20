//
// Ncurses.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/Graph
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  1 17:38:15 2017 benjamin girard
// Last update Sun Apr  9 17:19:27 2017 benjamin girard
//

#include "includes/Ncurses.hpp"

std::pair<uint16_t, uint16_t>		Ncurses::create_window(uint16_t /* width */,
							       uint16_t /* height */)
{
    std::pair<uint16_t, uint16_t>	window_size;
    uint16_t				row;
    uint16_t				col;

    initscr();
    is_open = true;
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    start_color();
    curs_set(0);
    getmaxyx(stdscr,row,col);
    this->win = newwin(row, col - (col % 2), 0, 0);
    nodelay(this->win, TRUE);
    a_refresh();
    window_size = std::make_pair(col / 2, row);
    return (window_size);
}

void					Ncurses::draw_sprite(const arcade::Position &point,
							     const t_drawer& draw,
							     const std::string &/* image */)
{
    return draw_rectangle(point, draw.color);
}

void					Ncurses::draw_rectangle(const arcade::Position &point,
								const t_a_color &color)
{
    uint8_t				id_pair = (color.color + 1);

    init_pair(id_pair, color.color, color.color);
    wattron(this->win, COLOR_PAIR(id_pair));
    mvwprintw(this->win, point.y, point.x * 2, "%c", ' ');
    mvwprintw(this->win, point.y, point.x * 2 + 1, "%c", ' ');
    wattroff(this->win, COLOR_PAIR(id_pair));
}

void					Ncurses::draw_text(const arcade::Position &point,
							   const std::string &text,
							   const size_t /* size */,
							   const t_a_color &color)
{
  uint16_t				id_pair = (color.color + 1) * 8;

    init_pair(id_pair, color.color, _BLACK_);
    wattron(this->win, COLOR_PAIR(id_pair));
    mvwprintw(this->win, point.y, point.x * 2, "%s", text.c_str());
    wattroff(this->win, COLOR_PAIR(id_pair));
}

void					Ncurses::draw_shape(const std::vector<arcade::Position> &lpoint,
                                                               const t_a_color &color)
{
    for (auto i = lpoint.begin(); i < lpoint.end(); ++i)
	draw_rectangle(*i,  color);
}

void					Ncurses::a_clear()
{
    wclear(this->win);
}

void					Ncurses::a_refresh()
{
    wrefresh(this->win);
}

bool					Ncurses::isOpen() const
{
    return is_open;
}

Input					Ncurses::checkInput()
{
    int					key = 0;
    static const std::map<char, Input>		_map =
    {
	{ '1', _ONE_ },
	{ '2', _TWO_ },
	{ '3', _THREE_ },
	{ '4', _FOUR_ },
	{ '5', _FIVE_ },
	{ '6', _SIX_ },
	{ '7', _SEVEN_ },
	{ '8', _EIGHT_ },
	{ '9', _NINE_ },
	{ '\n', _ENTER_ },
	{ ' ', _SPACE_ },
	{ _KEY_ESC_, _ESCAPE_ },
	{ 'A', _UP_ },
	{ 'B', _DOWN_ },
	{ 'D', _LEFT_ },
	{ 'C', _RIGHT_ },
	{ ERR, _UNDEFINED_ }
    };
    if ((key = wgetch(this->win)) == '\033') {
      if ((key = wgetch(this->win)) == '[') {
	    key = wgetch(this->win);
	    auto it = _map.find(key);
	    if (it != _map.end())
		return (it->second);
	}
      return (_ESCAPE_);
    }
    auto it2 = _map.find(key);
    if (it2 == _map.end() || it2->second > _ESCAPE_)
	return (_UNDEFINED_);
    return (it2->second);
}

void					Ncurses::close_window()
{
    is_open = false;
    delwin(this->win);
    endwin();
}

extern "C" IGraph			*create_igraph(void)
{
  return new Ncurses();
}

//
// Opengl.cpp for  in /home/tetard/EPITECH_Y2/CPP/cpp_arcade/Graph
//
// Made by benjamin girard
// Login   <tetard@epitech.net>
//
// Started on  Sat Apr  1 17:38:15 2017 benjamin girard
// Last update Sat Apr  8 12:22:19 2017 Renaud de Ganay
//

#include "includes/Opengl.hpp"

Opengl::~Opengl(void) {
    if (this->_win)
	delete this->_win;
}

std::pair<uint16_t, uint16_t>		Opengl::create_window(uint16_t width,
							       uint16_t height)
{
    this->_win = NULL;
    this->_height = height -  (height % SIZE_CELL);
    this->_width = width - (width % SIZE_CELL);
    this->is_open = true;
    this->_win = new sf::RenderWindow(sf::VideoMode(this->_width, this->_height), "Arcade");
    this->_win->setActive(true);
    this->_font.loadFromFile(LIB_FONT);
    return (std::make_pair(this->_width / SIZE_CELL, this->_height / SIZE_CELL));
}

void					Opengl::draw_sprite(const arcade::Position &point,
							    const t_drawer&  draw,
							    const std::string &/*sprite*/)
{
    draw_rectangle(point, draw.color);
}

void					Opengl::draw_rectangle(const arcade::Position &point,
								const t_a_color &color)
{
    float				width = static_cast<float>(this->_width) / 10.0;
    float				height = static_cast<float>(this->_height) / 10.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-((static_cast<float>(SIZE_CELL) / 10.0) / 2.0),
	    width, height, -((static_cast<float>(SIZE_CELL) / 10.0) / 2.0),
	    -1.0, 1.0);
    glPointSize(SIZE_CELL);
    glLineWidth(SIZE_CELL);
    glColor3ub(color.R, color.G, color.B);
    glBegin(GL_POINTS);
    glVertex2d((static_cast<float>(point.x * SIZE_CELL)) / 10.0,
	       (static_cast<float>(point.y * SIZE_CELL)) / 10.0);
    glEnd();
}

void					Opengl::draw_text(const arcade::Position &point,
							  const std::string &text,
							  const size_t /* size */,
							  const t_a_color &color)
{
    sf::Text                              new_text(text, this->_font);

    this->_win->pushGLStates();
    new_text.setCharacterSize(SIZE_CELL);
    new_text.setPosition(sf::Vector2f(point.x * SIZE_CELL, point.y * SIZE_CELL));
    new_text.setColor(sf::Color(color.R, color.G, color.B));
    this->_win->draw(new_text);
    this->_win->draw(new_text);
    this->_win->popGLStates();
}

void					Opengl::draw_shape(const std::vector<arcade::Position> &lpoint,
                                                               const t_a_color &color)
{
    for (auto it = lpoint.begin(); it != lpoint.end(); it++)
	draw_rectangle((*it), color);
}

void					Opengl::a_clear()
{
    this->_win->clear();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void					Opengl::a_refresh()
{
    this->_win->display();
}

bool					Opengl::isOpen() const
{
    return this->_win->isOpen();
}

Input					Opengl::checkInput()
{
    static const std::vector<std::pair<Input, sf::Keyboard::Key> > key_interface = {
	{_ONE_,     sf::Keyboard::Num1},
	{_TWO_,     sf::Keyboard::Num2},
	{_THREE_,   sf::Keyboard::Num3},
	{_FOUR_,    sf::Keyboard::Num4},
	{_FIVE_,    sf::Keyboard::Num5},
	{_SIX_,     sf::Keyboard::Num6},
	{_SEVEN_,   sf::Keyboard::Num7},
	{_EIGHT_,   sf::Keyboard::Num8},
	{_NINE_,    sf::Keyboard::Num9},
	{_ENTER_,   sf::Keyboard::Return},
	{_SPACE_,   sf::Keyboard::Space},
	{_ESCAPE_,  sf::Keyboard::Escape},
	{_UP_,      sf::Keyboard::Up},
	{_DOWN_,    sf::Keyboard::Down},
	{_LEFT_,    sf::Keyboard::Left},
	{_RIGHT_,   sf::Keyboard::Right},
	{_UNDEFINED_,       sf::Keyboard::Unknown}
    };
    sf::Event                             event;

    while (this->_win->pollEvent(event))
    {
	if (event.type == sf::Event::Closed)
	    close_window();
	if (event.type == sf::Event::KeyPressed)
	    for (auto it = key_interface.begin(); it != key_interface.end(); it++)
		if (event.key.code == (*it).second)
		    return (*it).first;
    }
    return (Input::_UNDEFINED_);
}

void					Opengl::close_window()
{
    this->is_open = false;
    this->_win->close();
}

extern "C" IGraph			*create_igraph(void)
{
  return new Opengl();
}

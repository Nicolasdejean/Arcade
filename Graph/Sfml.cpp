//
// Sfml.cpp for Sfml in /home/renaud/Documents/Tech2/C++/cpp_arcade
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Wed Apr  5 15:01:06 2017 Renaud de Ganay
// Last update Wed Apr  5 16:17:42 2017 Renaud de Ganay
//

#include "includes/Sfml.hpp"

Sfml::~Sfml(void) {
  if (this->_win)
    delete this->_win;
}

std::pair<uint16_t, uint16_t>		Sfml::create_window(uint16_t width, uint16_t height)
{
    this->_width = width - (width % SIZE_CELL);
    this->_height = height - (height % SIZE_CELL);

  this->_width_cell = this->_width / SIZE_CELL;
  this->_height_cell = this->_height / SIZE_CELL;
  this->_win = new sf::RenderWindow(sf::VideoMode(this->_width, this->_height), "Arcade");
  this->_win->setKeyRepeatEnabled(false);
  this->_win->clear(sf::Color(0, 0, 0));
  this->_font.loadFromFile(LIB_FONT);
  return (std::make_pair(this->_width / SIZE_CELL, this->_height / SIZE_CELL));
}

void					Sfml::close_window(void) {
  this->_win->close();
}

void                                    Sfml::draw_sprite(const arcade::Position &point,
							  const t_drawer& /* draw */,
							  const std::string &image)
{
    sf::Sprite				sprite;
    sf::Vector2f			pos;
    sf::Vector2f			scale;

    if (_sprite.find(image) == _sprite.end())
	_sprite[image].loadFromFile(image);
    _sprite[image].setSmooth(true);

    pos.x = ((static_cast<float>(point.x * SIZE_CELL)));
    pos.y = ((static_cast<float>(point.y * SIZE_CELL)));
    sprite.setPosition(pos);
    sprite.setTexture(_sprite[image]);
    scale.x = static_cast<float>(SIZE_CELL) / static_cast<float>(_sprite[image].getSize().x);
    scale.y = static_cast<float>(SIZE_CELL) / static_cast<float>(_sprite[image].getSize().y);
    sprite.scale(scale.x, scale.y);
    this->_win->draw(sprite);
}

void					Sfml::draw_rectangle(const arcade::Position &point,
							     const t_a_color &color)
{
  sf::RectangleShape			cell(sf::Vector2f(SIZE_CELL, SIZE_CELL));

  cell.setPosition(sf::Vector2f(point.x * SIZE_CELL, point.y * SIZE_CELL));
  cell.setFillColor(sf::Color(color.R, color.G, color.B));
  this->_win->draw(cell);
}

void					Sfml::draw_text(const arcade::Position &point,
							const std::string &text,
							const size_t /* size */,
							const t_a_color &color)
{
  sf::Text				new_text(text, this->_font);

  new_text.setCharacterSize(SIZE_CELL);
  new_text.setPosition(sf::Vector2f(point.x * SIZE_CELL, point.y * SIZE_CELL));
  new_text.setColor(sf::Color(color.R, color.G, color.B));
  this->_win->draw(new_text);
}

void					Sfml::draw_shape(const std::vector<arcade::Position> &lpoint,
							 const t_a_color &color)
{
  for (auto it = lpoint.begin(); it != lpoint.end(); it++)
    draw_rectangle((*it), color);
}

void					Sfml::a_clear(void)
{
  this->_win->clear(sf::Color(0,0,0));
}

void					Sfml::a_refresh(void)
{
  this->_win->display();
}

bool					Sfml::isOpen(void) const
{
  return (this->_win->isOpen());
}

Input					Sfml::checkInput(void)
{
  static const std::vector<std::pair<Input, sf::Keyboard::Key> > key_interface = {
    {_ONE_,	sf::Keyboard::Num1},
    {_TWO_,	sf::Keyboard::Num2},
    {_THREE_,	sf::Keyboard::Num3},
    {_FOUR_,	sf::Keyboard::Num4},
    {_FIVE_,	sf::Keyboard::Num5},
    {_SIX_,	sf::Keyboard::Num6},
    {_SEVEN_,	sf::Keyboard::Num7},
    {_EIGHT_,	sf::Keyboard::Num8},
    {_NINE_,	sf::Keyboard::Num9},
    {_ENTER_,	sf::Keyboard::Return},
    {_SPACE_,	sf::Keyboard::Space},
    {_ESCAPE_,	sf::Keyboard::Escape},
    {_UP_,	sf::Keyboard::Up},
    {_DOWN_,	sf::Keyboard::Down},
    {_LEFT_,	sf::Keyboard::Left},
    {_RIGHT_,	sf::Keyboard::Right},
    {_UNDEFINED_,	sf::Keyboard::Unknown}
  };
  sf::Event				event;

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

extern "C" IGraph				*create_igraph(void)
{
  return new Sfml();
}

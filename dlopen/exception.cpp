//
// exception.cpp for exception in /home/renaud/Documents/Tech2/C++/cpp_arcade/dlopen
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Fri Apr  7 18:33:23 2017 Renaud de Ganay
// Last update Sun Apr  9 19:37:26 2017 Renaud de Ganay
//

#include "includes/exception.hpp"

Except::Except() : std::exception()
{}

void Except::opendirfail() const throw()
{
  std::cerr << "Couldn't open directory." << std::endl;
  std::exit(EXIT_FAILURE);
}


void Except::dlopenfail() const throw()
{
  std::cerr << "Couldn't open one of the dynamic libraries." << std::endl;
  std::exit(EXIT_FAILURE);
}

void Except::emptyvec() const throw()
{
  std::cerr << "No libraries available." << std::endl;
  std::exit(EXIT_FAILURE);
}

void Except::noarg() const throw()
{
  std::cerr << "Usage : ./arcade ./lib/lib_arcade_*.so" << std::endl;
  std::exit(EXIT_FAILURE);
}

void Except::badusername() const throw()
{
  std::cerr << "Your username must only consist of alphanumeric characters and underscores." << std::endl;
  std::exit(EXIT_FAILURE);
}

//
// exception.hpp for exception in /home/renaud/Documents/Tech2/C++/cpp_arcade/dlopen
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Fri Apr  7 18:34:16 2017 Renaud de Ganay
// Last update Sun Apr  9 19:35:10 2017 Renaud de Ganay
//

#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

#include <exception>
#include <iostream>

class		Except : public std::exception
{
public:
  Except();
  ~Except(){}

  void		opendirfail() const throw();
  void		dlopenfail() const throw();
  void		emptyvec() const throw();
  void		noarg() const throw();
  void		badusername() const throw();

private:
  Except		&operator=(Except & /* other */){return *this;}
};

#endif /* !EXCEPTION_HPP_ */

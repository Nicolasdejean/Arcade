//
// arcade.cpp for arcade in /home/renaud/Documents/Tech2/C++/cpp_arcade/core
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Sun Apr  9 16:51:03 2017 Renaud de Ganay
// Last update Sun Apr  9 19:52:56 2017 benjamin girard
//

#include "includes/Core.hpp"

int			main(int ac, char **av)
{
  Except		arg;

  try {
    if (ac != 2)
      throw arg;
  }
  catch (const Except &e) {
    e.noarg();
  }

  Core			core(av[1]);

  core.startMenu();

  while (core.checkOpen())
    {
      core.updateInput();
      core.checkDirection();
      core.checkPause();
      core.checkGraph();
      core.checkGame();
      core.checkRestart();
      core.checkMenu();
      core.c_clear();
      core.c_play();
      core.c_refresh();
      core.checkClose();
    }

  return (EXIT_SUCCESS);
}

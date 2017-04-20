//
// DLLoader.cpp for DlLLoader in /home/renaud/Documents/Tech2/C++/cpp_arcade/dl/bootstrap
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Wed Mar 29 17:28:30 2017 Renaud de Ganay
// Last update Sun Apr  9 19:05:15 2017 Renaud de Ganay
//

#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include "includes/DLLoader.hpp"
#include <iostream>

bool			DLLoader::is_name_end(std::string const &name, std::string const &end)
{
  if (name.length() >= end.length())
    return (name.compare(name.length() - end.length(), end.length(), end) == 0);
  else
    return (false);
}

DLLoader::DLLoader(std::string const &lib_path)
{
  size_t	slash;

  slash = lib_path.find_last_of("/");
  this->_lib_path = lib_path.substr(0, slash + 1);
  loadAll(this->_lib_path, lib_path.substr(slash + 1, lib_path.back()),
	  &this->_curr_graph, this->_graphs, this->_it_graphs, this->_graph_names);
  loadAll("./games/", "test",
	  &this->_curr_game, this->_games, this->_it_games, this->_game_names);
}

DLLoader::~DLLoader(void)
{
  for (auto &it : this->_graphs)
    dlclose(it.first);
}


IGraph			*DLLoader::getCurrentGraph(void)
{
  return (this->_curr_graph);
}

IGame			*DLLoader::getCurrentGame(void)
{
  return (this->_curr_game);
}

IGraph			*DLLoader::nextGraph(const std::string &name)
{
  std::pair<uint16_t, uint16_t> size;

  this->_curr_graph->close_window();
  if (this->_it_graphs == --(this->_graphs.end()))
    this->_it_graphs = this->_graphs.begin();
  else
    this->_it_graphs++;
  this->_curr_graph = (*this->_it_graphs).second;
  size = this->_curr_graph->create_window(WIDTH, HEIGHT);
  this->_curr_game->init(size.first, size.second, name);
  return (this->_curr_graph);
}

IGraph			*DLLoader::prevGraph(const std::string &name)
{
  std::pair<uint16_t, uint16_t> size;

  this->_curr_graph->close_window();
  if (this->_it_graphs == this->_graphs.begin())
    this->_it_graphs = --(this->_graphs.end());
  else
    this->_it_graphs--;
  this->_curr_graph = (*this->_it_graphs).second;
  size = this->_curr_graph->create_window(WIDTH, HEIGHT);
  this->_curr_game->init(size.first, size.second, name);
  return (this->_curr_graph);
}

IGraph			*DLLoader::nbGraph(uint16_t nb, const std::string &name)
{
  std::pair<uint16_t, uint16_t> size;

  this->_curr_graph->close_window();
  this->_curr_graph = this->_graphs[nb].second;
  this->_it_graphs = this->_graphs.begin() + nb;
  size = this->_curr_graph->create_window(WIDTH, HEIGHT);
  this->_curr_game->init(size.first, size.second, name);
  return (this->_curr_graph);
}

IGame			*DLLoader::nextGame(const std::string &name)
{
  if (this->_it_games == --(this->_games.end()))
    this->_it_games = this->_games.begin();
  else
    this->_it_games++;
  this->_curr_game = (*this->_it_games).second;
  this->restartGame(name);
  return (this->_curr_game);
}

IGame			*DLLoader::prevGame(const std::string &name)
{
  if (this->_it_games == --(this->_games.end()))
    this->_it_games = this->_games.begin();
  else
    this->_it_games++;
  this->_curr_game = (*this->_it_games).second;
  this->restartGame(name);
  return (this->_curr_game);
}


IGame			*DLLoader::nbGame(uint16_t nb, const std::string &name)
{
  this->_curr_game = this->_games[nb].second;
  this->_it_games = this->_games.begin() + nb;
  this->restartGame(name);
  return (this->_curr_game);
}

void			DLLoader::restartGame(const std::string &name)
{
  std::pair<uint16_t, uint16_t> size;

  this->_curr_graph->close_window();
  size = this->_curr_graph->create_window(WIDTH, HEIGHT);
  this->_curr_game->init(size.first, size.second, name);
}

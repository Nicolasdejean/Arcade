//
// DLLoader.hpp for DLLoader in /home/renaud/Documents/Tech2/C++/cpp_arcade/dl/bootstrap
//
// Made by Renaud de Ganay
// Login   <renaud@epitech.net>
//
// Started on  Wed Mar 29 19:12:39 2017 Renaud de Ganay
// Last update Sun Apr  9 22:17:38 2017 benjamin girard
//

#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

#include <vector>
#include <string>
#include <dlfcn.h>
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include "../../Graph/includes/IGraph.hpp"
#include "../../games/includes/IGame.hpp"
#include "exception.hpp"

static const uint16_t WIDTH = 1500;
static const uint16_t HEIGHT = 900;

class							DLLoader
{
protected:
  std::string						_lib_path;
  IGraph						*_curr_graph;
  IGame							*_curr_game;
  std::vector<std::string>				_graph_names;
  std::vector<std::string>				_game_names;
  std::vector<std::pair<void *, IGraph *> >		_graphs;
  std::vector<std::pair<void *, IGame *> >		_games;
  std::vector<std::pair <void *, IGraph *> >::iterator	_it_graphs;
  std::vector<std::pair <void *, IGame *> >::iterator	_it_games;

private:
  DLLoader(DLLoader const &/* other */) {}
  DLLoader operator=(DLLoader const &/* other */)
  { return (*this); }

public:
  DLLoader(std::string const &lib_path);
  virtual ~DLLoader(void);

  bool							is_name_end(std::string const &name, std::string const &end);

  IGraph						*getCurrentGraph(void);
  IGame							*getCurrentGame(void);

  IGraph						*nextGraph(const std::string &name);
  IGraph						*prevGraph(const std::string &name);
  IGraph						*nbGraph(uint16_t nb, const std::string &name);

  IGame							*nextGame(const std::string &name);
  IGame							*prevGame(const std::string &name);
  IGame							*nbGame(uint16_t nb, const std::string &name);
  void							restartGame(const std::string &name);

  template <typename T>
  void							loadAll(std::string const						&path,
								std::string const						&curr_name,
								T								**curr_lib,
								std::vector<std::pair<void *, T *> >	&vec,
								typename std::vector<std::pair <void *, T * > >::iterator	&curr_it,
								std::vector<std::string>					&names)
  {
    DIR			*dir;
    struct dirent	*ent;
    std::string		file_path;
    T			*(*external_creator)();
    void		*handle;
    int			pos;
    Except		dlfail;
    bool		know_lib = false;

    pos = 0;
    try {
    if ((dir = opendir(path.c_str())) == NULL)
      throw dlfail;
    }
    catch (const Except &e)
      {
	e.opendirfail();
      }
    while ((ent = readdir(dir)) != NULL)
      {
	if (is_name_end(ent->d_name, ".so"))
	  {
	    file_path = path + ent->d_name;
	    try {
	    if ((handle = dlopen(file_path.c_str(), RTLD_LAZY)) == NULL)
	      throw dlfail;
	    }
	    catch(const Except &e)
	      {
		e.dlopenfail();
	      }
	    vec.push_back(std::make_pair(handle,
						   static_cast<T *>(NULL)));
	    if ((external_creator = reinterpret_cast<T* (*)()>
		 (dlsym(vec.back().first, "create_igraph"))) == NULL)
	      external_creator = reinterpret_cast<T* (*)()>
		(dlsym(vec.back().first, "create_igame"));
	    vec.back().second = static_cast<T *>(NULL);
	    vec.back().second = external_creator();
	    names.push_back(ent->d_name);
	    if (ent->d_name == curr_name)
	      {
		*curr_lib = vec.back().second;
		pos = vec.size() - 1;
		know_lib = true;
	      }
	  }
      }
    try {
      if (vec.empty())
	  throw dlfail;
    }
    catch (const Except &e)
      {
	e.emptyvec();
      }
    curr_it = vec.begin() + pos;
    if (know_lib == false)
      *curr_lib = vec.front().second;
  }
};

#endif /* !DLLOADER_HPP_ */

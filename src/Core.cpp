//
// Core.cpp for core in /home/rebut_p/Programmation/CPP/cpp_arcade/src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Tue Mar 15 17:40:11 2016 Pierre Rebut
// Last update Mon Apr  4 01:05:30 2016 Pierre Rebut
//

#include	<dlfcn.h>
#include	<iostream>
#include	<iterator>
#include	"Core.hpp"
#include	"Map.hpp"
#include	"utils.hpp"

arcade::Core::Core()
{
  _player = "Pierre";
  _menu._player = _player;
  _lstGame = open_dir("./games/");
  _lstDisplay = open_dir("./lib/");
  if (_lstGame.size() == 0 || _lstDisplay.size() == 0)
    throw std::runtime_error("List game or display empty !");
  _currentDisplay = -1;
  _currentGame = -1;
  _game = NULL;
  _display = NULL;
  _displayLD = NULL;
  _gameLD = NULL;
}

arcade::Core::~Core()
{
  if (_game != NULL)
    delete _game;
  if (_display != NULL)
    delete _display;
  if (_displayLD != NULL)
    dlclose(_displayLD);
  if (_gameLD != NULL)
    dlclose(_gameLD);
}

template<typename T>
T	loadLibrary(const std::string &file, void **lib, const std::string &cmd)
{
  T	ptr;

  if (file == "")
    {
      std::cerr << "ERROR: file not set or is not in list" << std::endl;
      return (NULL);
    }
  if (*lib != NULL)
    dlclose(*lib);
  ptr = open_lib<T>(file, cmd, lib);
  if (ptr == NULL)
    {
      if (*lib != NULL)
	dlclose(*lib);
      throw std::runtime_error(" Core: file is not arcade library > exit");
    }
  return (ptr);
}

bool		arcade::Core::changeDisplay(const std::string &file)
{
  IDisplay	*(*ptr)(const size_t, const size_t);

  if (_display != NULL)
    _display->destroyWin();
  delete _display;
  ptr = loadLibrary<IDisplay *(*)(const size_t,
				  const size_t)>(file, &_displayLD, "init_screen");
  if (ptr == NULL)
    return (false);
  _display = ptr(800, 600);
  if (_display == NULL)
    throw std::runtime_error(" Core: init error");
  _display->newWin();
  return (true);
}

bool		arcade::Core::changeGame(const std::string &file)
{
  IGame		*(*ptr)(const size_t, const size_t);

  delete _game;
  ptr = loadLibrary<IGame *(*)(const size_t,
				  const size_t)>(file, &_gameLD, "init_game");
  if (ptr == NULL)
    return (false);
  _game = ptr(40, 30);
  if (_game == NULL)
    throw std::runtime_error(" Core: init error");
  _display->setSpriteSheet(_game->getSpriteSheet());
  _pause = true;
  _gameName = _lstGame.at(_currentGame).first;
  initScore();
  return (true);
}

void		arcade::Core::changeDisplayByLst(const int id)
{
  if (id > 0)
    {
      if (_currentDisplay == 0)
	_currentDisplay = _lstDisplay.size();
      _currentDisplay -= 1;
    }
  else
    {
      _currentDisplay += 1;
      _currentDisplay %= _lstDisplay.size();
    }
  changeDisplay(_lstDisplay.at(_currentDisplay).second);
}

void		arcade::Core::changeGameByLst(const int id)
{
  if (id > 0)
    {
      if (_currentGame == 0)
	_currentGame = _lstGame.size();
      _currentGame -= 1;
    }
  else
    {
      _currentGame += 1;
      _currentGame %= _lstGame.size();
    }
  changeGame(_lstGame.at(_currentGame).second);
}

bool			arcade::Core::getInitDisplay(const std::string &line)
{
  for (unsigned int i = 0; i < _lstDisplay.size(); i++)
    {
      if (line == _lstDisplay.at(i).first)
	{
	  _currentDisplay = i;
	  if (changeDisplay(_lstDisplay.at(i).second) == false)
	    return (false);
	  return (true);
	}
    }
  return (false);
}

bool			arcade::Core::initCore(const std::string &filename)
{
  void			*tmp;
  std::string const	(*ptr)();
  std::string		line;

  ptr = open_lib<std::string const (*)()>(filename, "getName", &tmp);
  if (ptr == NULL)
    throw std::runtime_error(" Core: file is not arcade lib");
  line = ptr();
  if (getInitDisplay(line) == false)
    {
      std::cerr << "Can't find graphic lib in list" << std::endl;
      return (false);
    }
  if (tmp != NULL)
    dlclose(tmp);
  _currentGame = 0;
  if (changeGame(_lstGame.at(0).second) == false)
    return (false);
  return (true);
}

void	arcade::Core::switch_cmd(const arcade::CommandType cmd, bool &menu, bool &loopPlay)
{
  switch (cmd)
    {
    case CommandType::EXIT:
      loopPlay = false;
      break;
    case CommandType::DISPLAY_PREV:
      this->changeDisplayByLst(-1);
      _display->setSpriteSheet(_game->getSpriteSheet());
      break;
    case CommandType::DISPLAY_NEXT:
      this->changeDisplayByLst(1);
      _display->setSpriteSheet(_game->getSpriteSheet());
      break;
    case CommandType::GAME_PREV:
      this->changeGameByLst(-1);
      break;
    case CommandType::GAME_NEXT:
      this->changeGameByLst(1);
      break;
    case CommandType::PLAY:
      if (menu == false)
	_pause = !_pause;
      break;
    case CommandType::ENTER:
      if (menu == true)
	{
	  _player = _display->getUserName();
	  _menu._player = _player;
	}
      break;
    case CommandType::MENU:
      menu = true;
      _pause = menu;
      break;
    default:
      if (_pause == false)
	_game->playMove(cmd);
    };
}

void				arcade::Core::loopGame()
{
  bool				menu = true;
  bool				loopPlay;
  CommandType			cmd;

  loopPlay = true;
  while (loopPlay == true)
    {
      cmd = _display->getEvent();
      switch_cmd(cmd, menu, loopPlay);
      _display->drawHeader(_player, _gameName, _game->getScore());
      _display->drawMap(_game->getMap());
      if (_game->isAlive() == false)
	{
	  _display->printText("Game Over", 250, 250, 60, 0xffff0000);
	  if (cmd == CommandType::PLAY && menu == false)
	    {
	      updateScore();
	      if (_game->Reload() == false)
		return;
	    }
	  else if (cmd == CommandType::MENU)
	    updateScore();
	  _pause = true;
	}
      if (menu == true)
	{
	  printMenu(cmd, &menu);
	  _pause = menu;
	}
      _display->updateWindow(_game->getUpdateTimer());
    }
}

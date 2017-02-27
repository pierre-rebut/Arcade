//
// Menu.cpp for Menu in /home/rebut_p/Programmation/CPP/cpp_arcade/games/menu_src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Mon Mar 21 14:24:28 2016 Pierre Rebut
// Last update Sat Apr  2 18:41:04 2016 ganive_v
//

#include	<iostream>
#include	<iterator>
#include	"Menu.hpp"
#include	"Core.hpp"

void		arcade::Core::initMenu()
{
  _menu._currentGame = 0;
  for (std::vector<std::pair<std::string, std::string> >::const_iterator it = _lstGame.begin();
       it != _lstGame.end(); ++it)
    _menu._lstGame.push_back((*it).first);
  for (std::vector<std::pair<std::string, std::string> >::const_iterator it = _lstDisplay.begin();
       it != _lstDisplay.end(); ++it)
    _menu._lstDisplay.push_back((*it).first);
}

void		arcade::Core::printMenu(const arcade::CommandType cmd, bool *menu)
{
  switch (cmd)
    {
    case CommandType::GO_UP:
      _menu._currentGame --;
      break;
    case CommandType::GO_DOWN:
      _menu._currentGame++;
      break;
    case CommandType::PLAY:
      _currentGame = _menu._currentGame;
      changeGame(_lstGame.at(_menu._currentGame).second);
      *menu = false;
      break;
    default:break;
    }
  _menu._currentGame %= _menu._lstGame.size();
  _display->drawMenu(_menu);
}

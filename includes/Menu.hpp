//
// drawMenu.hpp for drawMenu in /home/rebut_p/Programmation/CPP/cpp_arcade/src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Fri Apr  1 19:00:01 2016 Pierre Rebut
// Last update Sun Apr  3 10:22:38 2016 Pierre Rebut
//

#ifndef		__MENU_HPP__
# define	__MENU_HPP__
# include	<vector>
# include	<string>

namespace		arcade
{
  struct		Menu
  {
    size_t			_currentGame;
    std::string			_player;
    std::vector<std::string>	_lstGame;
    std::vector<std::string>	_lstDisplay;
    std::vector<std::pair<std::string, size_t> >	_score;
  };
}

#endif

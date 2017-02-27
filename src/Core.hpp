//
// Core.hpp for core in /home/rebut_p/Programmation/CPP/cpp_arcade/src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Tue Mar 15 17:27:28 2016 Pierre Rebut
// Last update Sun Apr  3 21:56:03 2016 Pierre Rebut
//

#ifndef		__CORE_HPP__
# define	__CORE_HPP__
# include	<string>
# include	<vector>
# include	<utility>
# include	<exception>
# include	<stdexcept>
# include	"IDisplay.hpp"
# include	"IGame.hpp"
# include	"Menu.hpp"
# include	"Map.hpp"

namespace	arcade
{
  class		Core
  {
    bool			_pause;
    std::vector<std::pair<std::string, std::string> >	_lstGame;
    std::vector<std::pair<std::string, std::string> >	_lstDisplay;
    unsigned int		_currentDisplay;
    unsigned int		_currentGame;
    IDisplay			*_display;
    IGame			*_game;
    void			*_displayLD;
    void			*_gameLD;
    std::string			_player;
    std::string			_gameName;

    Menu			_menu;

    bool			changeDisplay(const std::string &);
    bool			changeGame(const std::string &);
    void			changeDisplayByLst(const int id);
    void			changeGameByLst(const int id);

    void			printMenu(CommandType, bool*);
    bool			getInitDisplay(const std::string &filename);
    void			switch_cmd(const arcade::CommandType, bool &, bool &);

    void			updateFile() const;
    void			updateScore();
    void			initScore();

  public:
    Core();
    ~Core();

    bool			initCore(const std::string &);
    void			initMenu();
    void			loopGame();
  };
}

#endif		/* !__CORE_HPP__ */

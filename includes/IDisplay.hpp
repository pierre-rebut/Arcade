//
// IDisplay.hpp for IDisplay in /home/rebut_p/Programmation/CPP/cpp_arcade/includes
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Tue Mar 15 17:22:09 2016 Pierre Rebut
// Last update Sun Apr  3 21:57:02 2016 Pierre Rebut
//

#ifndef			__IDISPLAY_HPP__
# define		__IDISPLAY_HPP__
# include		<string>
# include		<stdexcept>
# include		<vector>
# include		"Map.hpp"
# include		"Menu.hpp"
# include		"Protocol.hpp"

namespace		arcade
{
  class			IDisplay
  {
  public:
    virtual		~IDisplay() {}

    virtual bool	newWin() = 0;
    virtual bool	destroyWin() = 0;
    virtual CommandType	getEvent() const = 0;
    virtual bool	drawMap(const std::vector<gridPosition*> &) const = 0;
    virtual bool	drawHeader(const std::string &, const std::string &,
				   const size_t) const = 0;
    virtual bool	printText(const std::string &, const size_t,
				  const size_t, const size_t, const size_t) const = 0;
    virtual bool	drawMenu(const Menu &) const = 0;
    virtual bool	setSpriteSheet(const arcade::SpriteSheetInfo &) = 0;
    virtual void	updateWindow(const size_t) const = 0;
    virtual std::string	getUserName() = 0;
  };
}

#endif			/* !__IDISPLAY_HPP__ */

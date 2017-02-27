//
// DisplayCaca.hpp for DisplayCaca in /home/rebut_p/Programmation/CPP/cpp_arcade/lib/lib1
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 16 15:44:38 2016 Pierre Rebut
// Last update Sun Apr  3 21:59:00 2016 Pierre Rebut
//

#ifndef		__DISPLAYCACA_HPP__
# define	__DISPLAYCACA_HPP__
# include	<caca.h>
# include	<string>
# include	<exception>
# include	"IDisplay.hpp"
# include	"Map.hpp"

namespace	arcade
{
  class		DisplayCaca : public IDisplay
  {
    std::vector<size_t>	_tabColor;
    caca_canvas_t	*_cv;
    caca_display_t	*_dp;
    size_t		_height;
    size_t		_width;
    size_t		_mapX;
    size_t		_mapY;

    void		drawRectangle(const size_t, const size_t, const size_t,
				      const size_t, int, int) const;

  public:
    DisplayCaca(const size_t, const size_t);
    ~DisplayCaca();

    bool	newWin();
    bool	destroyWin();
    CommandType	getEvent() const;
    bool	drawMap(const std::vector<gridPosition*>&) const;
    bool	drawHeader(const std::string &, const std::string &,
			   const size_t) const;
    bool	setSpriteSheet(const arcade::SpriteSheetInfo &);
    void	updateWindow(const size_t) const;
    bool	drawMenu(const arcade::Menu &) const;
    bool	printText(const std::string &, const size_t, const size_t,
			  const size_t, const size_t) const;
    std::string	getUserName();
  };
}

#endif		/* !__DISPLAYCACA_HPP__ */

//
// DisplaySfml.hpp for DisplaySfml in /home/rebut_p/Programmation/CPP/cpp_arcade/lib/lib1
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 16 15:44:38 2016 Pierre Rebut
// Last update Sun Apr  3 14:13:44 2016 Pierre Rebut
//

#ifndef		__DISPLAYSFML_HPP__
# define	__DISPLAYSFML_HPP__
# include	<SFML/Graphics.hpp>
# include	<SFML/Window.hpp>
# include	<exception>
# include	"IDisplay.hpp"
# include	"Map.hpp"

namespace	arcade
{
  class		DisplaySfml : public IDisplay
  {
    std::vector<sf::Texture>	*_tabTexture;
    std::vector<size_t>		_tabColor;
    sf::Font		_font;
    sf::RenderWindow	*_window;
    size_t		_height;
    size_t		_width;
    double		_mapX;
    double		_mapY;

    void		drawSprite(const size_t x, const size_t y, const size_t id) const;
    void		drawColor(const size_t x, const size_t y, const size_t id) const;
    void		drawRectangle(const size_t, const size_t, const size_t,
				      const size_t, const sf::Color) const;

  public:
    DisplaySfml(const size_t, const size_t);
    ~DisplaySfml();

    bool	newWin();
    bool	destroyWin();
    CommandType	getEvent() const;
    bool	drawMap(const std::vector<gridPosition*> &) const;
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

#endif		/* !__DISPLAYSFML_HPP__ */

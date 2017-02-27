//
// DisplayOpengl.hpp for DisplayOpengl in /home/rebut_p/Programmation/CPP/cpp_arcade/lib/lib1
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 16 15:44:38 2016 Pierre Rebut
// Last update Sun Apr  3 10:43:21 2016 Pierre Rebut
//

#ifndef		__DISPLAYOPENGL_HPP__
# define	__DISPLAYOPENGL_HPP__
# include	<SDL/SDL.h>
# include	<GL/gl.h>
# include	<GL/glu.h>
# include	"IDisplay.hpp"
# include	"Map.hpp"

namespace	arcade
{
  class		DisplayOpengl : public IDisplay
  {
    std::vector<size_t>	_tabColor;
    SDL_Surface		*_window;
    size_t		_height;
    size_t		_width;
    double		_mapX;
    double		_mapY;
    GLuint		_texture;

    void		drawSprite(const size_t x, const size_t y, const size_t id) const;
    void		drawColor(const size_t x, const size_t y, const size_t id) const;
    void		drawRectangle(const size_t, const size_t, const size_t,
				      const size_t, const size_t color) const;

  public:
    DisplayOpengl(const size_t, const size_t);
    ~DisplayOpengl();

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

#endif		/* !__DISPLAYOPENGL_HPP__ */

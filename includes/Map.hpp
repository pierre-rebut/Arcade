//
// Map.hpp for Map in /home/rebut_p/Programmation/CPP/cpp_arcade/includes
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Thu Mar 17 19:02:22 2016 Pierre Rebut
// Last update Thu Mar 31 16:33:25 2016 Pierre Rebut
//

#ifndef		__MAP_HPP__
# define	__MAP_HPP__
# include	<vector>
# include	"Protocol.hpp"

namespace	arcade
{
  enum class	ArcadeColor : uint16_t
  {
    BLACK		= 0,
    BLUE		= 1,
    RED			= 2,
    CYAN		= 3,
    GREEN		= 4,
    YELLOW		= 5,
    MAGENTA		= 6,
    WHITE		= 7
  };

  enum		Direction
    {
      LEFT,
      RIGHT,
      UP,
      DOWN,
      NONE
    };

  struct		gridPosition
  {
    gridPosition(const size_t _x, const size_t _y, const size_t sprite, const TileType type)
    {
      x = _x;
      y = _y;
      spriteId = sprite;
      tileId = type;
    }
    size_t		x;
    size_t		y;
    size_t		spriteId;
    TileType		tileId;
  };

  struct		SpriteSheetInfo
  {
    size_t		map_x;
    size_t		map_y;
    size_t		nb_elem_x;
    size_t		nb_elem_y;
    std::string		path;
    std::vector<size_t>	color;
  };
}

#endif		/* !__MAP_HPP__ */

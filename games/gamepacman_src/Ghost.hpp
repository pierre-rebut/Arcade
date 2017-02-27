//
// Ghost.cpp for Ghost in /home/dourch_m/Epitech/CPP/cpp_arcade/games/game2_src
// 
// Made by Dourches Martin
// Login   <dourch_m@epitech.net>
// 
// Started on  Wed Mar 30 15:33:08 2016 Dourches Martin
// Last update Sun Apr  3 21:22:30 2016 Pierre Rebut
//

#ifndef		__GHOST_H__
# define	__GHOST_H__
# include	"IGame.hpp"

namespace arcade
{
  class Ghost
  {
    size_t     	_id;
    int		_posX;
    int		_posY;
  public:
    bool	_alive;
  private:
    int		_direction;
    std::vector<arcade::gridPosition*>	*_map;

    bool	check_ghost_next(int dir, int) const;
    int		new_direction() const;
    int		check_pos(int);

  public:
    Ghost(int, size_t, size_t, std::vector<arcade::gridPosition*>*);
    ~Ghost();

    void	setPosX(size_t);
    void	setPosY(size_t);
    void	setAlive(bool);
    size_t	getPosX() const;
    size_t	getPosY() const;
    int		getId() const;
    void	move_ghost(int, int);
    void	direction_left(int);
    void	direction_right(int);
    void	direction_up(int);
    void	direction_down(int);
  };
}

#endif		/* __GHOST_H__ */

//
// GameSnake.hpp for gamesnake in /home/rebut_p/Programmation/CPP/cpp_arcade/games/gamesnake_src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Thu Mar 17 14:13:20 2016 Pierre Rebut
// Last update Mon Apr  4 01:05:58 2016 Pierre Rebut
//

#ifndef			__GAMESNAKE_H__
# define		__GAMESNAKE_H__
# include		"IGame.hpp"
# include		<list>

namespace		arcade
{
  class			GameSnake : public IGame
  {
    size_t		_score;
    bool		_alive;
    int			_posX;
    int			_posY;
    int			_len;
    char		_saveDir;
    char		_direction;
    int			_height;
    int			_width;
    bool		_isMoul;

    std::vector<gridPosition*>	_snake;
    std::vector<gridPosition*>	_map;
    int			_timer;

    void	fruit();
    void	reset_map();
    void	move();
    void	die_snake();
    void	down();
    void	up();
    void	left();
    void	right();

  public:
    GameSnake(const size_t = 40, const size_t = 30, bool = false);
    ~GameSnake();

    size_t					getUpdateTimer() const;
    const arcade::SpriteSheetInfo		getSpriteSheet() const;
    const std::vector<arcade::gridPosition*>&	playMove(const CommandType);
    const std::vector<arcade::gridPosition*>&	getMap() const;
    const std::vector<arcade::gridPosition*>&	getSnake() const;
    size_t					getScore() const;
    bool					isAlive() const;
    bool					Reload();
  };
}

#endif			/* !__GAMESNAKE_H__ */

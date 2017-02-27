//
// Game_Pacman.hpp for Game_Pacman in /home/dourch_m/Epitech/CPP/cpp_arcade/games/gamesnake_src
// 
// Made by Dourches Martin
// Login   <dourch_m@epitech.net>
// 
// Started on  Tue Mar 29 13:02:01 2016 Dourches Martin
// Last update Sun Apr  3 19:24:25 2016 Dourches Martin
//

#ifndef		__GAMEPACMAN_H__
# define	__GAMEPACMAN_H__
# include	"IGame.hpp"
# include	"Ghost.hpp"

namespace	arcade
{
  class GamePacman : public IGame
  {
    bool	_pause;
    int		_posX;
    int		_posY;
    int       	_direction;
    int		_directionMove;
    int		_height;
    int		_width;
    size_t     	_score;
    int		_invincible;
    int		_round;
    int		_first_round;
    bool	_alive;
    bool	_open;

    std::vector<Ghost *> _gList;
    std::vector<gridPosition*> _map;
    int	       	_timer;

    std::vector<size_t>	*parsefile(const std::string &);
    void		move();
    void		changeMove();
    int			check_next(int pos, int);
    void		checkpowerup(int);
    void		check_ghost(int);
    void		checkWin();
  public:
    GamePacman(const size_t = 50, const size_t = 50);
    ~GamePacman();

    const arcade::SpriteSheetInfo		getSpriteSheet() const;
    const std::vector<arcade::gridPosition*>&	playMove(const CommandType);
    const std::vector<arcade::gridPosition*>&	getMap() const;
    size_t					getScore() const;
    bool					isAlive() const;
    size_t					getUpdateTimer() const;
    bool					Reload();
    void					KillGhost(int);
    void					game_over(int);
  };

  enum PacmanID
    {
      EMPTY = 0,
      BLOCKPAC = 1,
      SPRITERIGHTO = 3,
      SPRITEDOWNO = 17,
      SPRITELEFTO = 31,
      SPRITEUPO = 45,
      SPRITERIGHTF = 2,
      SPRITEDOWNF = 16,
      SPRITELEFTF = 30,
      SPRITEUPF = 44,
      SGHOSTRIGHTR = 11,
      SGHOSTDOWNR = 25,
      SGHOSTUPR = 53,
      SGHOSTLEFTR = 38,
      BONUS = 42,
      BONUSSP = 43,
      EVILR = 10,
      EVILP = 4,
      EVILY = 13,
      EVILB = 8,
      DEAD = 14,
      LIMIT = 15,
      SGHOSTRIGHTP = 4,
      SGHOSTDOWNP = 18,
      SGHOSTUPP = 46,
      SGHOSTLEFTP = 32,
      SGHOSTRIGHTY = 13,
      SGHOSTDOWNY = 27,
      SGHOSTUPY = 55,
      SGHOSTLEFTY = 41,
      SGHOSTRIGHTB = 8,
      SGHOSTDOWNB = 22,
      SGHOSTUPB = 50,
      SGHOSTLEFTB = 36,
    };
}

#endif		/* __GAMEPACMAN_H__ */

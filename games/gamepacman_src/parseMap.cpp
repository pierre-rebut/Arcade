//
// parse_map.cpp for parse_map in /home/dourch_m/Epitech/CPP/cpp_arcade/games/game2_src
// 
// Made by Dourches Martin
// Login   <dourch_m@epitech.net>
// 
// Started on  Tue Mar 29 17:19:34 2016 Dourches Martin
// Last update Sun Apr  3 20:34:44 2016 Pierre Rebut
//

#include	<iostream>
#include	<iterator>
#include	<cstdlib>
#include	"Map.hpp"
#include	"GamePacman.hpp"
#include	"Protocol.hpp"

std::vector<size_t>	*arcade::GamePacman::parsefile(const std::string &line)
{
  char			c;
  const char		*tmp = line.c_str();
  int			len = 0;
  std::vector<size_t>	*map = new std::vector<size_t>;

  for (int i = 0; tmp[i] != '\0'; i++)
    {
      c = tmp[i];
      if (c < '0' || c > '9')
	throw std::runtime_error("Pacman: caractere map incorecte");
      map->push_back(static_cast<size_t>(c - '0'));
      len++;
    }
  if (len != _width)
    {
      throw std::runtime_error("Pacman: size width map incorecte");
      delete map;
      return (NULL);
    }
  return (map);
}

void	arcade::GamePacman::checkpowerup(int pos)
{
  switch (_map.at(pos)->spriteId)
    {
    case BONUS:
      _score += 10;
      break;
      break;
    case BONUSSP:
      _invincible = 1;
      _score += 100;
      break;
    default:
      break;
    };
}

void	arcade::GamePacman::game_over(int pos)
{
  _map.at(pos)->spriteId = DEAD;
  _alive = false;
}

void	arcade::GamePacman::check_ghost(int pos)
{
  size_t	posGhost;

  for (std::vector<Ghost*>::const_iterator it = _gList.begin();
       it != _gList.end(); ++it)
    {
      posGhost = ((*it)->getPosY() * _width) + (*it)->getPosX();
      if (posGhost == static_cast<size_t>(pos))
	{
	  if (_invincible == 0)
	    game_over(pos);
	  else
	    KillGhost(pos);
	}
    }
}

int	arcade::GamePacman::check_next(int pos, int dir)
{
  check_ghost(pos);
  switch (_map.at(pos)->spriteId)
    {
    case  BLOCKPAC:
      if (dir == DOWN)
	_posY -= 1;
      else if (dir == UP)
	_posY += 1;
      else if (dir == RIGHT)
	_posX -= 1;
      else
	_posX += 1;
      pos = (_posY * _width) + _posX;
      break;
    case  LIMIT:
      if (dir == DOWN)
	_posY -= 1;
      else if (dir == UP)
	_posY += 1;
      else if (dir == RIGHT)
	_posX -= 1;
      else
	_posX += 1;
      pos = (_posY * _width) + _posX;
      break;
    case BONUS:
      checkpowerup(pos);
      break;
    case BONUSSP:
      checkpowerup(pos);
      break;
    default:
      break;
    };
  return (pos);
}

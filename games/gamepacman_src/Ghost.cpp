//
// Ghost.cpp for Ghost in /home/dourch_m/Epitech/CPP/cpp_arcade/games/game2_src
// 
// Made by Dourches Martin
// Login   <dourch_m@epitech.net>
// 
// Started on  Wed Mar 30 15:42:59 2016 Dourches Martin
// Last update Sun Apr  3 19:26:07 2016 Dourches Martin
//

#include	<iostream>

#include	<vector>
#include	<iterator>
#include	"GamePacman.hpp"
#include	"Ghost.hpp"

arcade::Ghost::Ghost(int id, size_t posX, size_t posY, std::vector<arcade::gridPosition*> *map)
{
  _id = id;
  _posX = posX;
  _posY = posY;
  _alive = false;
  _direction = RIGHT;
  _map = map;
}

arcade::Ghost::~Ghost()
{
}

void	arcade::Ghost::setPosX(size_t x)
{
  _posX = x;
  _map->at(_id)->x = _posX;
}

void	arcade::Ghost::setPosY(size_t y)
{
  _posY = y;
  _map->at(_id)->y = _posY;
}

void	arcade::Ghost::setAlive(bool alive)
{
  _alive = alive;
}

size_t	arcade::Ghost::getPosX() const
{
  return _posX;
}

size_t	arcade::Ghost::getPosY() const
{
  return _posY;
}

int	arcade::Ghost::getId() const
{
  return (_id);
}

bool	arcade::Ghost::check_ghost_next(int dir, int width) const
{
  int	pos;

  switch (dir)
    {
    case LEFT:
      pos = (_posY * width) + _posX - 1;
      break;
    case RIGHT:
      pos = (_posY * width) + _posX + 1;
      break;
    case UP:
      pos = ((_posY - 1)* width) + _posX;
      break;
    case DOWN:
      pos = ((_posY + 1) * width) + _posX;
      break;
    default:
      return (false);
    }
  if (_map->at(pos)->tileId == TileType::BLOCK)
    return (false);
  return (true);
}

int		arcade::Ghost::new_direction() const
{
  size_t	tab[4];
  int		check;

  check = rand() % 4;
  tab[0] = RIGHT;
  tab[3] = LEFT;
  tab[1] = UP;
  tab[2] = DOWN;
  return (tab[check]);
}

int	arcade::Ghost::check_pos(int width)
{
  size_t	tab[4];
  int		pos;
  int		i;

  i = 0;
  pos = (_posY * width) + _posX - 1;
  if (_map->at(pos)->tileId != TileType::BLOCK && _direction != LEFT)
    tab[i++] = LEFT;
  pos = (_posY * width) + _posX + 1;
  if (_map->at(pos)->tileId != TileType::BLOCK && _direction != RIGHT)
    tab[i++] = RIGHT;
  pos = ((_posY - 1)* width) + _posX;
  if (_map->at(pos)->tileId != TileType::BLOCK && _direction != UP)
    tab[i++] = UP;
  pos = ((_posY + 1) * width) + _posX;
  if (_map->at(pos)->tileId != TileType::BLOCK && _map->at(pos)->spriteId != LIMIT &&
      _direction != DOWN)
    tab[i++] = DOWN;
  if (i > 1)
    _direction = tab[rand() % i];
  return (i);
}

void	arcade::Ghost::direction_left(int invincible)
{
  _posX -= 1;
  _map->at(_id)->x = _posX;
  if (invincible == 1)
    _map->at(_id)->spriteId = DEAD;
  else
    if (_id == static_cast<size_t>(_map->size() - 4))
      _map->at(_id)->spriteId = SGHOSTLEFTY;
    else if (_id == static_cast<size_t>(_map->size() - 3))
      _map->at(_id)->spriteId = SGHOSTLEFTR;
    else if (_id == static_cast<size_t>(_map->size() - 2))
      _map->at(_id)->spriteId = SGHOSTLEFTP;
    else
      _map->at(_id)->spriteId = SGHOSTLEFTB;
}

void	arcade::Ghost::direction_right(int invincible)
{
  _posX += 1;
  _map->at(_id)->x = _posX;
  if (invincible == 1)
    _map->at(_id)->spriteId = DEAD;
  else
    if (_id == static_cast<size_t>(_map->size() - 4))
      _map->at(_id)->spriteId = SGHOSTRIGHTY;
    else if (_id == static_cast<size_t>(_map->size() - 3))
      _map->at(_id)->spriteId = SGHOSTRIGHTR;
    else if (_id == static_cast<size_t>(_map->size() - 2))
      _map->at(_id)->spriteId = SGHOSTRIGHTP;
    else
      _map->at(_id)->spriteId = SGHOSTRIGHTB;
}

void	arcade::Ghost::direction_up(int invincible)
{
  _posY -= 1;
  _map->at(_id)->y = _posY;
  if (invincible == 1)
    _map->at(_id)->spriteId = DEAD;
  else
    if (_id == static_cast<size_t>(_map->size() - 4))
      _map->at(_id)->spriteId = SGHOSTUPY;
    else if (_id == static_cast<size_t>(_map->size() - 3))
      _map->at(_id)->spriteId = SGHOSTUPR;
    else if (_id == static_cast<size_t>(_map->size() - 2))
      _map->at(_id)->spriteId = SGHOSTUPP;
    else
      _map->at(_id)->spriteId = SGHOSTUPB;
}

void	arcade::Ghost::direction_down(int invincible)
{
  _posY += 1;
  _map->at(_id)->y = _posY;
  if (invincible == 1)
    _map->at(_id)->spriteId = DEAD;
  else
    if (_id == static_cast<size_t>(_map->size() - 4))
      _map->at(_id)->spriteId = SGHOSTDOWNY;
    else if (_id == static_cast<size_t>(_map->size() - 3))
      _map->at(_id)->spriteId = SGHOSTDOWNR;
    else if (_id == static_cast<size_t>(_map->size() - 2))
      _map->at(_id)->spriteId = SGHOSTDOWNP;
    else
      _map->at(_id)->spriteId = SGHOSTDOWNB;
}

void	arcade::Ghost::move_ghost(int width, int invincible)
{
  if (_alive == true)
    {
      check_pos(width);
      if (check_ghost_next(_direction, width) == false)
	return;
      switch (_direction)
	{
	case LEFT:
	  direction_left(invincible);
	  break;
	case RIGHT:
	  direction_right(invincible);
	  break;
	case UP:
	  direction_up(invincible);
	  break;
	case DOWN:
	  direction_down(invincible);
	  break;
	};
    }
}


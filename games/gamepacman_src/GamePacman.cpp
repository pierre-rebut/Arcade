//
// Game_Pacman.cpp for Game_Pacman in /home/dourch_m/Epitech/CPP/cpp_arcade/games/gamesnake_src
// 
// Made by Dourches Martin
// Login   <dourch_m@epitech.net>
// 
// Started on  Tue Mar 29 13:59:05 2016 Dourches Martin
// Last update Sun Apr  3 21:49:32 2016 Pierre Rebut
//

#include	<iostream>
#include	<fstream>
#include	<iterator>
#include	<vector>
#include	<exception>
#include	"GamePacman.hpp"
#include	"Ghost.hpp"

arcade::GamePacman::GamePacman(const size_t w, const size_t h)
{
  (void)w;(void)h;
  if (Reload() == false)
    throw std::runtime_error("Pacman: can't init game");
}

bool		arcade::GamePacman::Reload()
{
  std::string		line;
  std::ifstream		myfile("./games/mappacman");
  std::vector<size_t>	*map;

  _posX = 10;
  _posY = 10;
  _height = 42;
  _width = 43;
  _timer = 140;
  _invincible = 0;
  _round = 0;
  _first_round = 0;
  _score = 0;
  _open = true;
  _alive = true;
  _directionMove = NONE;
  _direction = NONE;
  for (std::vector<gridPosition*>::iterator it = _map.begin(); it != _map.end(); ++it)
    delete *it;
  _map.clear();
  for (std::vector<Ghost*>::iterator it = _gList.begin(); it != _gList.end(); ++it)
    delete *it;
  _gList.clear();
  if (myfile.is_open())
    {
      int y = 0;
      std::getline(myfile, line);
      while (!myfile.eof())
	{
	  map = parsefile(line);
	  if (map == NULL)
	    throw std::runtime_error("Map incorecte");
	  for (int x = 0; x < _width; x++)
	    if (x == _posX && y == _posY)
	      _map.push_back(new gridPosition(x, y, SPRITERIGHTO, TileType::OTHER));
	    else if (map->at(x) == 1)
	      _map.push_back(new gridPosition(x, y, BLOCKPAC, TileType::BLOCK));
	    else if (map->at(x) == 8)
	      _map.push_back(new gridPosition(x, y, LIMIT, TileType::OTHER));
	    else if (map->at(x) == 9)
	      _map.push_back(new gridPosition(x, y, BONUS, TileType::POWERUP));
	    else if (map->at(x) == 7)
	      _map.push_back(new gridPosition(x, y, BONUSSP, TileType::POWERUP));
	    else
	      _map.push_back(new gridPosition(x, y, EMPTY, TileType::EMPTY));
	  delete map;
	  std::getline(myfile, line);
	  y++;
	}
      if (y != _height)
	throw std::runtime_error(" Pacman: size y map incorrect");
      for (int u = 0; u < _width; u++)
	if (_map.at(u)->spriteId != BLOCKPAC)
	  throw std::runtime_error(" Pacman: map border incorrect");
      for (int u = (y - 1) * _width; u < _width * _height; u++)
	if (_map.at(u)->spriteId != BLOCKPAC)
	  throw std::runtime_error(" Pacman: map border incorrect");
      myfile.close();
      _map.push_back(new gridPosition(20, 22, EVILY, TileType::EVIL_DUDE));
      _map.push_back(new gridPosition(22, 22, EVILR, TileType::EVIL_DUDE));
      _map.push_back(new gridPosition(20, 24, EVILP, TileType::EVIL_DUDE));
      _map.push_back(new gridPosition(22, 24, EVILB, TileType::EVIL_DUDE));
      _gList.push_back(new Ghost(_map.size() - 4, 20, 22, &_map));
      _gList.push_back(new Ghost(_map.size() - 3, 22, 22, &_map));
      _gList.push_back(new Ghost(_map.size() - 2, 20, 24, &_map));
      _gList.push_back(new Ghost(_map.size() - 1, 22, 24, &_map));
    }
  else
    throw std::runtime_error(" Pacman: can't open file");
  return (true);
}

arcade::GamePacman::~GamePacman()
{
  for (std::vector<gridPosition*>::iterator it = _map.begin(); it != _map.end(); ++it)
    {
      delete *it;
    }
  for (std::vector<Ghost*>::iterator it = _gList.begin(); it != _gList.end(); ++it)
    {
      delete *it;
    }
}

const std::vector<arcade::gridPosition*>&	arcade::GamePacman::getMap() const
{
  return ( _map);
}

const arcade::SpriteSheetInfo	arcade::GamePacman::getSpriteSheet() const
{
  std::vector<size_t>		color(56, 0x00000000);
  SpriteSheetInfo		sheet;

  color.at(EVILR) = 0xFF0000;
  color.at(EVILP) = 0xFF99FF;
  color.at(EVILB) = 0x6600CC;
  color.at(EVILY) = 0xFF6633;
  color.at(BLOCKPAC) = 0xF25761;
  color.at(SPRITEDOWNO) = 0xFFFF00;
  color.at(SPRITEUPO) = 0xFFFF00;
  color.at(SPRITELEFTO) = 0xFFFF00;
  color.at(SPRITERIGHTO) = 0xFFFF00;
  color.at(SPRITEDOWNF) = 0xFFFF00;
  color.at(SPRITEUPF) = 0xFFFF00;
  color.at(SPRITELEFTF) = 0xFFFF00;
  color.at(SPRITERIGHTF) = 0xFFFF00;
  color.at(DEAD) = 0x330099;
  color.at(BONUSSP) = 0xFFFFFF;
  color.at(SGHOSTLEFTR) = 0xFF0000;
  color.at(SGHOSTRIGHTR) = 0xFF0000;
  color.at(SGHOSTUPR) = 0xFF0000;
  color.at(SGHOSTDOWNR) = 0xFF0000;
  color.at(SGHOSTLEFTP) = 0xFF99FF;
  color.at(SGHOSTRIGHTP) = 0xFF99FF;
  color.at(SGHOSTUPP) = 0xFF99FF;
  color.at(SGHOSTDOWNP) = 0xFF99FF;
  color.at(SGHOSTLEFTB) = 0x6600CC;
  color.at(SGHOSTRIGHTB) = 0x6600CC;
  color.at(SGHOSTUPB) = 0x6600CC;
  color.at(SGHOSTDOWNB) = 0x6600CC;
  color.at(SGHOSTLEFTY) = 0xFF6633;
  color.at(SGHOSTRIGHTY) = 0xFF6633;
  color.at(SGHOSTUPY) = 0xFF6633;
  color.at(SGHOSTDOWNY) = 0xFF6633;
  color.at(BONUS) = 0x99FF66;
  sheet.nb_elem_x = 14;
  sheet.nb_elem_y = 4;
  sheet.map_x = _width;
  sheet.map_y = _height;
  sheet.path = "./games/texturePacman.png";
  sheet.color = color;
  return (sheet);
}

void		arcade::GamePacman::KillGhost(int pos)
{
  int	position;

  for (std::vector<Ghost *>::iterator it = _gList.begin(); it != _gList.end(); it++)
    {
      position = ((*it)->getPosY() * _width) + (*it)->getPosX();
      if (pos == position)
	{
	  (*it)->setPosY(22);
	  (*it)->setPosX(20);
	}
    }
  _score += 200;
}

void		arcade::GamePacman::changeMove()
{
  int		pos;

  switch (_direction)
    {
    case DOWN:
      pos = ((_posY + 1)* _width) + _posX;
      if (_map.at(pos)->tileId != TileType::BLOCK)
	_directionMove = DOWN;
      break;
    case UP:
      pos = ((_posY - 1) * _width) + _posX;
      if (_map.at(pos)->tileId != TileType::BLOCK)
	_directionMove = UP;
      break;
    case LEFT:
      pos = (_posY * _width) + (_posX - 1);
      if (_map.at(pos)->tileId != TileType::BLOCK)
	_directionMove = LEFT;
      break;
    case RIGHT:
      pos = (_posY * _width) + (_posX + 1);
      if (_map.at(pos)->tileId != TileType::BLOCK)
	_directionMove = RIGHT;
      break;
    default:
      break;
    };
}

void		arcade::GamePacman::move()
{
  int		pos;

  if (_directionMove != NONE)
    {
      pos = (_posY * _width) + _posX;
      _map.at(pos)->tileId = TileType::EMPTY;
      _map.at(pos)->spriteId = EMPTY;
    }
  if (_invincible == 1)
    _round++;
  if (_round == 120)
    {
      _invincible = 0;
      _round = 0;
    }
  check_ghost(pos);
  _open = !_open;
  switch (_directionMove)
    {
    case DOWN:
      _posY += 1;
      pos = (_posY * _width) + _posX;
      pos = check_next(pos, DOWN);
      if (_open == false)
	_map.at(pos)->spriteId = SPRITEDOWNF;
      else
	_map.at(pos)->spriteId = SPRITEDOWNO;
      break;
    case UP:
      _posY -= 1;
      pos = (_posY * _width) + _posX;
      pos = check_next(pos, UP);
      if (_open == false)
	_map.at(pos)->spriteId = SPRITEUPF;
      else
	_map.at(pos)->spriteId = SPRITEUPO;
      break;
    case RIGHT:
      _posX += 1;
      pos = (_posY * _width) + _posX;
      pos = check_next(pos, RIGHT);
      if (_open == false)
	_map.at(pos)->spriteId = SPRITERIGHTF;
      else
	_map.at(pos)->spriteId = SPRITERIGHTO;
      break;
    case LEFT:
      _posX -= 1;
      pos = (_posY * _width) + _posX;
      pos = check_next(pos, LEFT);
      if (_open == false)
	_map.at(pos)->spriteId = SPRITELEFTF;
      else
	_map.at(pos)->spriteId = SPRITELEFTO;
      break;
    default:
      break;
    };
  if (_directionMove != NONE)
    _map.at(pos)->tileId = TileType::OTHER;
}

void		arcade::GamePacman::checkWin()
{
  for (std::vector<gridPosition*>::iterator it = _map.begin(); it != _map.end(); it++)
    {
      if ((*it)->spriteId == BONUS)
	return ;
    }
  _alive = false;
}

const std::vector<arcade::gridPosition*>&	arcade::GamePacman::playMove(const arcade::CommandType cmd)
{
  _first_round++;
  switch (cmd)
    {
    case CommandType::GO_UP:
      _direction = UP;
      break;
    case CommandType::GO_DOWN:
      _direction = DOWN;
      break;
    case CommandType::GO_RIGHT:
      _direction = RIGHT;
      break;
    case CommandType::GO_LEFT:
      _direction = LEFT;
      break;
    case CommandType::RELOAD:
      Reload();
      break;
    default:
      break;
    };
  checkWin();
  changeMove();
  move();
  if (_alive == false)
    return (_map);
  for (std::vector<Ghost *>::iterator it = _gList.begin(); it != _gList.end(); it++)
    {
      if (_first_round >= 120)
	(*it)->_alive = true;
      (*it)->move_ghost(_width, _invincible);
    }
  return (_map);
}

size_t	arcade::GamePacman::getScore() const
{
  return (_score);
}

size_t	arcade::GamePacman::getUpdateTimer() const
{
  return _timer;
}

bool	arcade::GamePacman::isAlive() const
{
  return (_alive);
}

void	doGetMap(const std::vector<arcade::gridPosition*> &map, arcade::GetMap *moul)
{
  int	pos;

  moul->type = arcade::CommandType::GET_MAP;
  moul->width = 43;
  moul->height = 42;
  for (std::vector<arcade::gridPosition*>::const_iterator it = map.begin();
       it != map.end(); ++it)
    {
      pos = ((*it)->y * 43) + (*it)->x;
      if (pos < 43 * 42)
	{
	  if ((*it)->tileId != arcade::TileType::OTHER)
	    moul->tile[pos] = (*it)->tileId;
	  else
	    moul->tile[pos] = arcade::TileType::EMPTY;
	}
    }
  std::cout.write(reinterpret_cast<char*>(moul),
		  sizeof(arcade::GetMap) + 43 * 42 * sizeof(arcade::TileType));
}

void	doWhereIam(const std::vector<arcade::gridPosition*> &map,
		   arcade::WhereAmI *moul)
{
  moul->type = arcade::CommandType::WHERE_AM_I;
  moul->lenght = 1;
  for (std::vector<arcade::gridPosition*>::const_iterator it = map.begin();
       it != map.end(); ++it)
    {
      if ((*it)->tileId == arcade::TileType::OTHER)
	{
	  moul->position[0].x = (*it)->x;
	  moul->position[0].y = (*it)->y;
	  break;
	}
    }
  std::cout.write(reinterpret_cast<char*>(moul),
		  sizeof(arcade::WhereAmI) + sizeof(arcade::Position));
}

extern "C"
{
  arcade::IGame	*init_game(const size_t w, const size_t h)
  {
    return new arcade::GamePacman(w, h);
  }

  std::string	 getName()
  {
    return "Pacman";
  }

  void	 Play()
  {
    std::vector<arcade::gridPosition*>	 map;
    arcade::CommandType	cmd;
    arcade::GamePacman	game(43, 42);
    arcade::GetMap		*MapMoul;
    arcade::WhereAmI		*PacMoul;

    MapMoul = new arcade::GetMap + 43 * 42 * sizeof(arcade::TileType);
    PacMoul = new arcade::WhereAmI + sizeof(arcade::Position);
    while (42)
      {
	std::cin.read(reinterpret_cast<char*>(&cmd),
		      sizeof(arcade::CommandType));
	map = game.getMap();
	switch (cmd)
	  {
	  case arcade::CommandType::WHERE_AM_I:
	    doWhereIam(map, PacMoul);
	    break;
	  case arcade::CommandType::GET_MAP:
	    doGetMap(map, MapMoul);
	    break;
	  case arcade::CommandType::ILLEGAL:
	    break;
	  default:
	    game.playMove(cmd);
	    break;
	  };
      }
  }
}

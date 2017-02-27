//
// GameSnake.cpp for Game in /home/rebut_p/Programmation/CPP/cpp_arcade/games/gamesnake_src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Thu Mar 17 16:36:35 2016 Pierre Rebut
// Last update Mon Apr  4 01:07:00 2016 Pierre Rebut
//

#include	<iostream>
#include	<iterator>
#include	<cstdlib>
#include	<iomanip>
#include	<ctime>
#include	"GameSnake.hpp"

enum
  {
    LEFT,
    RIGHT,
    UP,
    DOWN
  };

enum
  {
    DOWN_LEFT = 0,
    HORIZONTAL,
    DOWN_RIGHT,
    HEAD_UP,
    HEAD_RIGHT,
    TURN_RIGHT,
    NOTHING_1,
    VERTICAL,
    HEAD_LEFT,
    HEAD_DOWN,
    NOTHING_2,
    NOTHING_3,
    TURN_LEFT,
    TAIL_UP,
    TAIL_RIGHT,
    APPLE,
    NOTHING_4,
    BLOCK,
    TAIL_LEFT,
    TAIL_DOWN
  };

arcade::GameSnake::GameSnake(const size_t w, const size_t h, bool moul)
{
  _height = h;
  _isMoul = moul;
  _width = w;
  if (Reload() == false)
    throw std::runtime_error("Snake: can't init game");
}

size_t		arcade::GameSnake::getUpdateTimer() const
{
  return (_timer);
}

size_t		arcade::GameSnake::getScore() const
{
  return (_score);
}

bool		arcade::GameSnake::isAlive() const
{
  return (_alive);
}

arcade::GameSnake::~GameSnake()
{
  for (std::vector<gridPosition*>::iterator it = _map.begin(); it != _map.end(); ++it)
    {
      delete *it;
    }
  for (std::vector<gridPosition*>::iterator it = _snake.begin(); it != _snake.end(); ++it)
    {
      delete *it;
    }
}

const std::vector<arcade::gridPosition*>&	arcade::GameSnake::getMap() const
{
  return ( _map);
}

void		arcade::GameSnake::fruit()
{
  int	x = random() % _width;
  int	y = random() % _height;
  int pos = (y * _width) + x;
  while (_map.at(pos)->tileId != TileType::EMPTY)
    {
      x = random() % _width;
      y = random() % _height;
      pos = (y * _width) + x;
    }
  _map.at(pos)->spriteId = APPLE;
  _map.at(pos)->tileId = TileType::POWERUP;
}

bool		arcade::GameSnake::Reload()
{
  _score = 0;
  _alive = true;
  _direction = RIGHT;
  _saveDir = RIGHT;
  _len = 4;
  _timer = 180;
  _posX = _width / 2;
  _posY = _height / 2;
  for (std::vector<gridPosition*>::iterator it = _snake.begin() ; it != _snake.end() ; ++it)
    delete *it;
  _snake.clear();
  for (std::vector<gridPosition*>::iterator it = _map.begin() ; it != _map.end() ; ++it)
    delete *it;
  _map.clear();
  for (int y = 0; y < _height ; y++)
    {
      for (int x = 0; x < _width ; x++)
	if (x == 0 || y == 0 || x == _width - 1 || y == _height - 1)
	  _map.push_back(new gridPosition(x, y, BLOCK, TileType::EVIL_DUDE));
	else
	  _map.push_back(new gridPosition(x, y, NOTHING_1, TileType::EMPTY));
    }
  int pos = (_posY * _width) + _posX;
  _map.at(pos)->spriteId = HEAD_RIGHT;
  _map.at(pos)->tileId = TileType::OTHER;
  _snake.push_back(new gridPosition(_posX, _posY, HEAD_RIGHT, TileType::OTHER));
  pos = (_posY * _width) + _posX - 1;
  _map.at(pos)->spriteId = HORIZONTAL;
  _map.at(pos)->tileId = TileType::EVIL_DUDE;
  _snake.push_back(new gridPosition(_posX - 1, _posY, HORIZONTAL, TileType::EVIL_DUDE));
  pos = (_posY * _width) + _posX - 2;
  _map.at(pos)->spriteId = HORIZONTAL;
  _map.at(pos)->tileId = TileType::EVIL_DUDE;
  _snake.push_back(new gridPosition(_posX - 2, _posY, HORIZONTAL, TileType::EVIL_DUDE));
  pos = (_posY * _width) + _posX - 3;
  _map.at(pos)->spriteId = TAIL_RIGHT;
  _map.at(pos)->tileId = TileType::EVIL_DUDE;
  _snake.push_back(new gridPosition(_posX - 3, _posY, TAIL_RIGHT, TileType::EVIL_DUDE));
  fruit();
  return (true);
}

void		arcade::GameSnake::reset_map()
{
  int		pos;

  for (std::vector<gridPosition*>::iterator it = _snake.begin() ; it != _snake.end() ; ++it)
    {
      pos = ((*it)->y * _width) + (*it)->x;
      (*it)->spriteId = _map.at(pos)->spriteId;
      _map.at(pos)->spriteId = NOTHING_1;
      _map.at(pos)->tileId = TileType::EMPTY;
    }
}

void		arcade::GameSnake::up()
{
  int		pos;

  pos = (_posY * _width) + _posX;
  if (_map.at(pos)->tileId == TileType::EVIL_DUDE)
    return (die_snake());
  else if (_map.at(pos)->tileId == TileType::POWERUP)
    {
      _snake.push_back(new gridPosition(_snake.back()->x, _snake.back()->y, HORIZONTAL, TileType::EVIL_DUDE));
      _score += 100;
      if (_timer - 20 > 0)
	_timer -= 20;
      else
	_score += 900;
      fruit();
    }
  reset_map();
  for (int i = _snake.size() - 1; i >= 0  ; i--)
    {
      if (i == 0)
	_snake[i]->y = _posY;
      else
	{
	  _snake[i]->x = _snake[i - 1]->x;
	  _snake[i]->y = _snake[i - 1]->y;
	}
      pos = (_snake[i]->y * _width) + _snake[i]->x;
      _map.at(pos)->tileId = TileType::EVIL_DUDE;
      if (i == 0)
	_map.at(pos)->spriteId = HEAD_UP;
      else if (static_cast<unsigned int>(i) == _snake.size() - 1)
	{
	  if (_snake[i - 2]->spriteId == VERTICAL && (_snake[i]->spriteId == TAIL_LEFT || _snake[i]->spriteId == TAIL_RIGHT))
	    _map.at(pos)->spriteId = _snake[i - 2]->y + 1 == _snake[i]->y ? TAIL_UP : TAIL_DOWN;
	  else if ((_snake[i - 1]->spriteId == HORIZONTAL || _snake[i - 1]->spriteId == DOWN_LEFT) && _snake[i - 2]->x <= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_LEFT;
	  else if ((_snake[i - 1]->spriteId == HORIZONTAL || _snake[i - 1]->spriteId == DOWN_RIGHT) && _snake[i - 2]->x >= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_RIGHT;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y <= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_UP;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y >= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_DOWN;
	  else
	    _map.at(pos)->spriteId = _snake[i]->spriteId;
	}
      else if (i == 1)
	{
	  if (_snake[i]->spriteId == HORIZONTAL)
	    {
	      if (_saveDir == RIGHT)
		_map.at(pos)->spriteId = TURN_LEFT;
	      else if (_saveDir == LEFT)
		_map.at(pos)->spriteId = TURN_RIGHT;
	    }
	  else
	    _map.at(pos)->spriteId = VERTICAL;
	}
      else
	_map.at(pos)->spriteId = _snake[i - 1]->spriteId;
    }
}

void		arcade::GameSnake::down()
{
  int		pos;

  pos = (_posY * _width) + _posX;
  if (_map.at(pos)->tileId == TileType::EVIL_DUDE)
    return (die_snake());
  else if (_map.at(pos)->tileId == TileType::POWERUP)
    {
      _snake.push_back(new gridPosition(_snake.back()->x, _snake.back()->y, HORIZONTAL, TileType::EVIL_DUDE));
      _score += 100;
      if (_timer - 20 > 0)
	_timer -= 20;
      else
	_score += 900;
      fruit();
    }
  reset_map();
  for (unsigned int i = _snake.size() - 1; static_cast<int>(i) >= 0  ; i--)
    {
      if (i == 0)
	_snake[i]->y = _posY;
      else
	{
	  _snake[i]->x = _snake[i - 1]->x;
	  _snake[i]->y = _snake[i - 1]->y;
	}
      pos = (_snake[i]->y * _width) + _snake[i]->x;
      _map.at(pos)->tileId = TileType::EVIL_DUDE;
      if (i == 0)
	_map.at(pos)->spriteId = HEAD_DOWN;
      else if (i == _snake.size() - 1)
	{
	  if (_snake[i - 2]->spriteId == VERTICAL && (_snake[i]->spriteId == TAIL_LEFT || _snake[i]->spriteId == TAIL_RIGHT))
	    _map.at(pos)->spriteId = _snake[i - 2]->y + 1 == _snake[i]->y ? TAIL_UP : TAIL_DOWN;
	  else if ((_snake[i - 1]->spriteId == HORIZONTAL || _snake[i - 1]->spriteId == DOWN_LEFT) && _snake[i - 2]->x <= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_LEFT;
	  else if ((_snake[i - 1]->spriteId == HORIZONTAL || _snake[i - 1]->spriteId == DOWN_RIGHT) && _snake[i - 2]->x >= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_RIGHT;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y >= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_DOWN;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y <= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_UP;
	  else
	    _map.at(pos)->spriteId = _snake[i]->spriteId;
	}
      else if (i == 1)
	{
	  if (_snake[i]->spriteId == HORIZONTAL)
	    {
	      if (_saveDir == RIGHT)
		_map.at(pos)->spriteId = DOWN_RIGHT;
	      else if (_saveDir == LEFT)
		_map.at(pos)->spriteId = DOWN_LEFT;
	    }
	  else
	    _map.at(pos)->spriteId = VERTICAL;
	}
      else
	_map.at(pos)->spriteId = _snake[i - 1]->spriteId;
    }
}

void		arcade::GameSnake::die_snake()
{
  _alive = false;
}

void		arcade::GameSnake::right()
{
  int		pos;

  pos = (_posY * _width) + _posX;
  if (_map.at(pos)->tileId == TileType::EVIL_DUDE)
    return (die_snake());
  else if (_map.at(pos)->tileId == TileType::POWERUP)
    {
      _snake.push_back(new gridPosition(_snake.back()->x, _snake.back()->y, HORIZONTAL, TileType::EVIL_DUDE));
      _score += 100;
      if (_timer - 20 > 0)
	_timer -= 20;
      else
	_score += 900;
      fruit();
    }
  reset_map();
  for (int i = _snake.size() - 1; i >= 0  ; i--)
    {
      if (i == 0)
	_snake[i]->x = _posX;
      else
	{
	  _snake[i]->x = _snake[i - 1]->x;
	  _snake[i]->y = _snake[i - 1]->y;
	}
      pos = (_snake[i]->y * _width) + _snake[i]->x;
      _map.at(pos)->tileId = TileType::EVIL_DUDE;
      if (i == 0)
	_map.at(pos)->spriteId = HEAD_RIGHT;
      else if (i == static_cast<int>(_snake.size()) - 1)
	{
	  if (_snake[i - 2]->spriteId == HORIZONTAL && (_snake[i]->spriteId == TAIL_UP || _snake[i]->spriteId == TAIL_DOWN))
	    _map.at(pos)->spriteId = _snake[i - 2]->x + 1 == _snake[i]->y ? TAIL_LEFT : TAIL_RIGHT;
	  else if (_snake[i - 1]->spriteId == HORIZONTAL && _snake[i - 2]->x >= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_RIGHT;
	  else if (_snake[i - 1]->spriteId == HORIZONTAL && _snake[i - 2]->x <= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_LEFT;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y >= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_DOWN;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y <= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_UP;
	  else
	    _map.at(pos)->spriteId = _snake[i]->spriteId;
	}
      else if (i == 1)
	{
	  if (_snake[i]->spriteId == VERTICAL)
	    {
	      if (_saveDir == UP)
		_map.at(pos)->spriteId = DOWN_LEFT;
	      else if (_saveDir == DOWN)
		_map.at(pos)->spriteId = TURN_RIGHT;
	    }
	  else
	    _map.at(pos)->spriteId = HORIZONTAL;
	}
      else
	_map.at(pos)->spriteId = _snake[i - 1]->spriteId;
    }
}

void		arcade::GameSnake::left()
{
  int		pos;

  pos = (_posY * _width) + _posX;
  if (_map.at(pos)->tileId == TileType::EVIL_DUDE)
    return (die_snake());
  else if (_map.at(pos)->tileId == TileType::POWERUP)
    {
      _snake.push_back(new gridPosition(_snake.back()->x, _snake.back()->y, HORIZONTAL, TileType::EVIL_DUDE));
      _score += 100;
      if (_timer - 20 > 0)
	_timer -= 20;
      else
	_score += 900;
      fruit();
    }
  reset_map();
  for (int i = _snake.size() - 1; i >= 0  ; i--)
    {
      if (i == 0)
	_snake[i]->x = _posX;
      else
	{
	  _snake[i]->x = _snake[i - 1]->x;
	  _snake[i]->y = _snake[i - 1]->y;
	}
      pos = (_snake[i]->y * _width) + _snake[i]->x;
      _map.at(pos)->tileId = TileType::EVIL_DUDE;
      if (i == 0)
	_map.at(pos)->spriteId = HEAD_LEFT;
      else if (i == static_cast<int>(_snake.size()) - 1)
	{
	  if (_snake[i - 2]->spriteId == HORIZONTAL && (_snake[i]->spriteId == TAIL_UP || _snake[i]->spriteId == TAIL_DOWN))
	    _map.at(pos)->spriteId = _snake[i - 2]->x + 1 == _snake[i]->y ? TAIL_RIGHT : TAIL_LEFT;
	  else if (_snake[i - 1]->spriteId == HORIZONTAL && _snake[i - 2]->x <= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_LEFT;
	  else if (_snake[i - 1]->spriteId == HORIZONTAL && _snake[i - 2]->x >= _snake[i]->x)
	    _map.at(pos)->spriteId = TAIL_RIGHT;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y <= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_UP;
	  else if (_snake[i - 1]->spriteId == VERTICAL && _snake[i - 2]->y >= _snake[i]->y)
	    _map.at(pos)->spriteId = TAIL_DOWN;
	  else
	    _map.at(pos)->spriteId = _snake[i]->spriteId;
	}
      else if (i == 1)
	{
	  if (_snake[i]->spriteId == VERTICAL)
	    {
	      if (_saveDir == UP)
		_map.at(pos)->spriteId = DOWN_RIGHT;
	      else if (_saveDir == DOWN)
		_map.at(pos)->spriteId = TURN_LEFT;
	    }
	  else
	    _map.at(pos)->spriteId = HORIZONTAL;
	}
      else
	_map.at(pos)->spriteId = _snake[i - 1]->spriteId;
    }
}

void		arcade::GameSnake::move()
{
  switch (_direction)
    {
    case DOWN:
      _posY += 1;
      down();
      _saveDir = DOWN;
      break;
    case UP:
      _posY -= 1;
      up();
      _saveDir = UP;
      break;
    case RIGHT:
      _posX += 1;
      right();
      _saveDir = RIGHT;
      break;
    case LEFT:
      _posX -= 1;
      left();
      _saveDir = LEFT;
      break;
    };
}

const std::vector<arcade::gridPosition*>&	arcade::GameSnake::playMove(const arcade::CommandType cmd)
{
  switch (cmd)
    {
    case CommandType::GO_DOWN:
      if (_direction != UP)
	_direction = DOWN;
      break;
    case CommandType::GO_UP:
      if (_direction != DOWN)
	_direction = UP;
      break;
    case CommandType::GO_LEFT:
      if (_direction != RIGHT)
	_direction = LEFT;
      break;
    case CommandType::GO_RIGHT:
      if (_direction != LEFT)
	_direction = RIGHT;
      break;
    case CommandType::RELOAD:
      Reload();
    default:
      if (_isMoul == true)
	this->move();
      break;
    };
  if (_isMoul == false)
    this->move();
  return (_map);
}

const arcade::SpriteSheetInfo	arcade::GameSnake::getSpriteSheet() const
{
  std::vector<size_t>		color(20, 0x000000);
  SpriteSheetInfo		sheet;

  color.at(DOWN_LEFT) = 0x3BA13A;
  color.at(HORIZONTAL) = 0x3BA13A;
  color.at(DOWN_RIGHT) = 0x3BA13A;
  color.at(HEAD_UP) = 0x3BA13A;
  color.at(HEAD_RIGHT) = 0x3BA13A;
  color.at(TURN_RIGHT) = 0x3BA13A;
  color.at(VERTICAL) = 0x3BA13A;
  color.at(HEAD_LEFT) = 0x3BA13A;
  color.at(HEAD_DOWN) = 0x3BA13A;
  color.at(TURN_LEFT) = 0x3BA13A;
  color.at(TAIL_UP) = 0x3BA13A;
  color.at(TAIL_RIGHT) = 0x3BA13A;
  color.at(APPLE) = 0xEE0000;
  color.at(BLOCK) = 0x3A52A1;
  color.at(TAIL_LEFT) = 0x3BA13A;
  color.at(TAIL_DOWN) = 0x3BA13A;
  sheet.nb_elem_x = 5;
  sheet.nb_elem_y = 4;
  sheet.map_x = _width;
  sheet.map_y = _height;
  sheet.path = "./games/textureSnake.png";
  sheet.color = color;
  return (sheet);
}

const std::vector<arcade::gridPosition*>&	arcade::GameSnake::getSnake() const
{
  return (_snake);
}

void		doGetMap(const std::vector<arcade::gridPosition*> &map, arcade::GetMap *moul)
{
  int		pos;

  moul->type = arcade::CommandType::GET_MAP;
  moul->width = 40;
  moul->height = 30;
  for (std::vector<arcade::gridPosition*>::const_iterator it = map.begin();
       it != map.end(); ++it)
    {
      pos = ((*it)->y * 40) + (*it)->x;
      if (pos < 40 * 30)
	{
	  if ((*it)->spriteId == BLOCK)
	    moul->tile[pos] = arcade::TileType::BLOCK;
	  else if ((*it)->tileId == arcade::TileType::POWERUP)
	    moul->tile[pos] = arcade::TileType::POWERUP;
	  else
	    moul->tile[pos] = arcade::TileType::EMPTY;
	}
    }
  std::cout.write(reinterpret_cast<char*>(moul),
		  sizeof(arcade::GetMap) + 40 * 30 * sizeof(arcade::TileType));
}

void			doWhereIam(const std::vector<arcade::gridPosition*> &snake,
				   arcade::WhereAmI *moul)
{
  int			pos;

  moul->type = arcade::CommandType::WHERE_AM_I;
  moul->lenght = snake.size();
  pos = 0;
  for (std::vector<arcade::gridPosition*>::const_iterator it = snake.begin();
       it != snake.end(); ++it)
    {
      moul->position[pos].x = (*it)->x;
      moul->position[pos].y = (*it)->y;
      pos++;
    }
  std::cout.write(reinterpret_cast<char*>(moul),
		  sizeof(arcade::WhereAmI) + snake.size() * sizeof(arcade::Position));
}

extern "C"
{
  arcade::IGame	*init_game(const size_t w, const size_t h)
  {
    return new arcade::GameSnake(w, h);
  }

  std::string	 getName()
  {
    return "Snake";
  }

  void		Play()
  {
    std::vector<arcade::gridPosition*> map;
    arcade::CommandType	cmd;
    arcade::GameSnake	game(40, 30, true);
    arcade::GetMap	*MapMoul;
    arcade::WhereAmI	*SnakeMoul;

    MapMoul = new arcade::GetMap + 40 * 30 * sizeof(arcade::TileType);
    SnakeMoul = new arcade::WhereAmI + 1200 * sizeof(arcade::Position);
    while (42)
      {
	std::cin.read(reinterpret_cast<char*>(&cmd),
		      sizeof(arcade::CommandType));
	switch (cmd)
	  {
	  case arcade::CommandType::WHERE_AM_I:
	    map = game.getSnake();
	    doWhereIam(map, SnakeMoul);
	    break;
	  case arcade::CommandType::GET_MAP:
	    map = game.getMap();
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

//
// DisplayCaca.cpp for DisplayCaca in /home/rebut_p/Programmation/CPP/cpp_arcade/lib/lib1
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 16 15:48:29 2016 Pierre Rebut
// Last update Sun Apr  3 21:20:06 2016 Pierre Rebut
//

#include	<sstream>
#include	<unistd.h>
#include	<utility>
#include	<iostream>
#include	"DisplayCaca.hpp"

static const std::pair<int, arcade::CommandType> keyConf[] = {
  { 273, arcade::CommandType::GO_UP},
  { 274, arcade::CommandType::GO_DOWN},
  { 275, arcade::CommandType::GO_LEFT},
  { 276, arcade::CommandType::GO_RIGHT},
  { 27, arcade::CommandType::EXIT},
  { 283, arcade::CommandType::DISPLAY_PREV},
  { 284, arcade::CommandType::DISPLAY_NEXT},
  { 285, arcade::CommandType::GAME_PREV},
  { 286, arcade::CommandType::GAME_NEXT},
  { 289, arcade::CommandType::RELOAD},
  { 290, arcade::CommandType::MENU},
  { 32, arcade::CommandType::PLAY},
  { 107, arcade::CommandType::SHOOT},
  { 293, arcade::CommandType::ENTER}
};

arcade::DisplayCaca::DisplayCaca(const size_t width, const size_t height)
{
  _width = width / 10;
  _height = height / 10;
  _width += 5;
}

arcade::DisplayCaca::~DisplayCaca()
{
}

bool		arcade::DisplayCaca::newWin()
{
  _cv = caca_create_canvas(_width, _width);
  if (_cv == NULL)
    throw std::runtime_error("CACA: can't init window");
  _dp = caca_create_display(_cv);
  if (_dp == NULL)
    throw std::runtime_error("CACA: can't init window");
  caca_set_display_title(_dp, "Arcade: Caca window");
  caca_clear_canvas(_cv);
  return (true);
}

bool		arcade::DisplayCaca::destroyWin()
{
  caca_free_display(_dp);
  caca_free_canvas(_cv);
  return (true);
}

void			arcade::DisplayCaca::updateWindow(const size_t timer) const
{
  caca_set_color_argb(_cv, 0x0000000, 0X000000);
  caca_refresh_display(_dp);
  usleep(timer * 500);
}

arcade::CommandType	arcade::DisplayCaca::getEvent() const
{
  int			keypress;
  caca_event_t		event;

  if (caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &event, 2) == 1)
    {
      keypress = event.data.key.ch;
      for (int i = 0; i < 16; i++)
	{
	  if (keyConf[i].first == keypress)
	    return (keyConf[i].second);
	}
    }
  return (CommandType::DEFAULT);
}

bool		arcade::DisplayCaca::drawMap(const std::vector<gridPosition*> &map) const
{
  size_t	colorR, colorG, colorB, color;

  for (std::vector<gridPosition*>::const_iterator it = map.begin(); it != map.end(); ++it)
    {
      color = _tabColor.at((*it)->spriteId);
      colorB = (color % 256) >> 3;
      colorG = (color / 256) % 256 >> 3;
      colorR = (color / 65536) >> 3;
      color = (colorB << 10) | (colorG << 5) | colorR;
      caca_set_color_argb(_cv, color, color);
      caca_put_str(_cv, (*it)->x * 2, (*it)->y + 10, "  ");
    }
  return (true);
}

bool		arcade::DisplayCaca::printText(const std::string &msg, const size_t x,
					       const size_t y, const size_t size,
					       const size_t color) const
{
  size_t	colorR, colorG, colorB, tmp;

  (void)size;
  tmp = color;
  colorB = (tmp % 256) >> 3;
  colorG = (tmp / 256) % 256 >> 3;
  colorR = (tmp / 65536) >> 3;
  tmp = (colorB << 10) | (colorG << 5) | colorR;
  caca_set_color_argb(_cv, tmp, 0x000000);
  caca_put_str(_cv, x / 10, y / 10, msg.c_str());
  return (true);
}

bool		arcade::DisplayCaca::drawHeader(const std::string &msg1,
						const std::string &msg2,
						const size_t score) const
{
  std::ostringstream	str;

  size_t	w = _width;
  size_t	h = 10;

  caca_clear_canvas(_cv);
  for (size_t y = 0; y < h; y++)
    {
      for (size_t x = 0; x < w; x++)
	{
	  if (x == 0 || y == 0 || x == w - 1 || y == h - 1)
	    caca_set_color_ansi(_cv, CACA_RED, CACA_RED);
	  else
	    caca_set_color_ansi(_cv, CACA_BLACK, CACA_BLACK);
	  caca_put_str(_cv, x, y, " ");
	}
    }
  str << "Score: " << score;
  caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
  caca_put_str(_cv, 10, 5, msg1.c_str());
  caca_put_str(_cv, 30, 5, msg2.c_str());
  caca_put_str(_cv, 50, 5, str.str().c_str());
  return (true);
}

void		arcade::DisplayCaca::drawRectangle(const size_t posx, const size_t posy,
						   const size_t w, const size_t h,
						   int color1, int color2) const
{
  for (size_t y = 0; y < h; y++)
    {
      for (size_t x = 0; x < w; x++)
	{
	  if (x == 0 || y == 0 || x == w - 1 || y == h - 1)
	    caca_set_color_ansi(_cv, color1, color1);
	  else
	    caca_set_color_ansi(_cv, color2, color2);
	  caca_put_str(_cv, x + posx, y + posy, " ");
	}
    }
}

bool		arcade::DisplayCaca::drawMenu(const arcade::Menu &menu) const
{
  std::ostringstream os;
  size_t	pos;

  pos = 0;
  drawRectangle(35, 12, 35, 25, CACA_RED, CACA_CYAN);
  caca_set_color_ansi(_cv, CACA_WHITE, CACA_CYAN);
  caca_put_str(_cv, 50, 15, "MENU");
  caca_put_str(_cv, 40, 18, "List Game:");
  for (std::vector<std::string>::const_iterator it = menu._lstGame.begin();
       it != menu._lstGame.end(); ++it)
    {
      if (menu._currentGame == pos)
	caca_set_color_ansi(_cv, CACA_RED, CACA_CYAN);
      else
	caca_set_color_ansi(_cv, CACA_WHITE, CACA_CYAN);
      caca_put_str(_cv, 52, 20 + pos * 2, (*it).c_str());
      pos++;
    }
  caca_set_color_ansi(_cv, CACA_WHITE, CACA_CYAN);
  caca_put_str(_cv, 40, 20 + pos * 2, "List Display:");
  pos++;
  for (std::vector<std::string>::const_iterator it = menu._lstDisplay.begin();
       it != menu._lstDisplay.end(); ++it)
    {
      caca_set_color_ansi(_cv, CACA_WHITE, CACA_CYAN);
      caca_put_str(_cv, 52, 20 + pos * 2, (*it).c_str());
      pos++;
    }
  pos = 0;
  drawRectangle(3, 12, 30, 25, CACA_RED, CACA_CYAN);
  caca_set_color_ansi(_cv, CACA_WHITE, CACA_CYAN);
  caca_put_str(_cv, 7, 15, "High scrore:");
  for (std::vector<std::pair<std::string, size_t> >::const_iterator it = menu._score.begin();
       it != menu._score.end(); ++it)
    {
      if (pos == 8)
	break;
      os.str("");
      os << (*it).first << ": " << (*it).second;
      caca_put_str(_cv, 12, 18 + pos * 2, os.str().c_str());
      pos++;
    }
  drawRectangle(6, 33, 24, 3, CACA_BLACK, CACA_BLACK);
  caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
  caca_put_str(_cv, 8, 34, menu._player.c_str());
  return (true);
}

bool		arcade::DisplayCaca::setSpriteSheet(const arcade::SpriteSheetInfo &file)
{
  _tabColor = file.color;
  _mapX = file.map_x;
  _mapY = file.map_y;
  return (false);
}

std::string	arcade::DisplayCaca::getUserName()
{
  int		keypress;
  caca_event_t	event;
  std::string	player;

  while (1)
    {
      if (caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &event, 2) == 1)
	{
	  keypress = event.data.key.ch;
	  if (keypress == 13)
	    {
	      if (player != "")
		return (player);
	    }
	  else if (keypress == 8)
	    player.size() > 0 ? player.erase(player.size() - 1, 1) : player = "";
	  else if ((keypress >= 'a' && keypress <= 'z') || (keypress >= 'A' || keypress <='Z'))
	    player.size() < 10 ? player += keypress : player = player;
	}
      caca_clear_canvas(_cv);
      drawRectangle(22, 22, 24, 2, CACA_RED, CACA_RED);
      caca_set_color_ansi(_cv, CACA_WHITE, CACA_RED);
      caca_put_str(_cv, 24, 22, player.c_str());
      caca_set_color_ansi(_cv, CACA_BLACK, CACA_BLACK);
      caca_refresh_display(_dp);
      usleep(500);
    }
  return (player);
}

extern "C"
{
  arcade::IDisplay	*init_screen(const size_t width, const size_t height)
  {
    if (width == 0 || height == 0)
      throw std::runtime_error("CACA: size window = 0");
    return new arcade::DisplayCaca(width, height);
  }

  std::string		getName()
  {
    return "Caca";
  }
}

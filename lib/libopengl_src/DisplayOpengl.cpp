//
// DisplayOpengl.cpp for DisplayOpengl in /home/rebut_p/Programmation/CPP/cpp_arcade/lib/lib1
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 16 15:48:29 2016 Pierre Rebut
// Last update Sun Apr  3 21:13:27 2016 Pierre Rebut
//

#include	<unistd.h>
#include	<utility>
#include	<iostream>
#include	<sstream>
#include	<exception>
#include	"DisplayOpengl.hpp"

static const std::pair<int, arcade::CommandType> keyConf[] = {
  { SDLK_ESCAPE, arcade::CommandType::EXIT},
  { SDLK_UP, arcade::CommandType::GO_UP},
  { SDLK_DOWN, arcade::CommandType::GO_DOWN},
  { SDLK_LEFT, arcade::CommandType::GO_LEFT},
  { SDLK_RIGHT, arcade::CommandType::GO_RIGHT},
  { SDLK_F2, arcade::CommandType::DISPLAY_PREV},
  { SDLK_F3, arcade::CommandType::DISPLAY_NEXT},
  { SDLK_F4, arcade::CommandType::GAME_PREV},
  { SDLK_F5, arcade::CommandType::GAME_NEXT},
  { SDLK_F8, arcade::CommandType::RELOAD},
  { SDLK_F9, arcade::CommandType::MENU},
  { SDLK_SPACE, arcade::CommandType::PLAY},
  { SDLK_k, arcade::CommandType::SHOOT},
  { SDLK_F10, arcade::CommandType::WHERE_AM_I},
  { SDLK_F1, arcade::CommandType::GET_MAP}
};

arcade::DisplayOpengl::DisplayOpengl(const size_t width, const size_t height)
{
  _width = width;
  _height = height;
}

arcade::DisplayOpengl::~DisplayOpengl()
{
}

bool		arcade::DisplayOpengl::newWin()
{
  int		nValue;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("Opengl: can't init SDL");
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_WM_SetCaption("Arcade Opengl", NULL);
  _window = SDL_SetVideoMode(_width, _height, 32, SDL_OPENGL);
  if (_window == NULL)
    throw std::runtime_error("Opengl: can't init window");
  if( SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &nValue) < 0)
    {
      std::cerr << "Erreur SDL_GL_DOUBLEBUFFER : " << SDL_GetError() << std::endl;
      throw std::runtime_error("Opengl: can't init SDL");
    }
  if(nValue != 1)
    {
      std::cerr << "Erreur : SDL_GL_DOUBLEBUFFER inactif" << std::endl;
      throw std::runtime_error("Opengl: can't init SDL");
    }
  gluOrtho2D(0, _width, _height, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  return (true);
}

bool		arcade::DisplayOpengl::destroyWin()
{
  SDL_Quit();
  return (true);
}

void		arcade::DisplayOpengl::updateWindow(const size_t timer) const
{
  glFlush();
  SDL_GL_SwapBuffers();
  usleep(timer * 500);
}

arcade::CommandType	arcade::DisplayOpengl::getEvent() const
{
  SDL_Event		event;

  while(SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  return (CommandType::EXIT);
	  break;
	case SDL_KEYDOWN:
	  for (int i = 0; i < 15; i++)
	    {
	      if (event.key.keysym.sym == keyConf[i].first)
		return (keyConf[i].second);
	    }
	  break;
	default:
	  break;
	};
    }
  return (CommandType::DEFAULT);
}

void		arcade::DisplayOpengl::drawRectangle(const size_t x, const size_t y,
						     const size_t w, const size_t h,
						     const size_t color) const
{
  int		colorR, colorG, colorB;

  colorB = color % 256;
  colorG = (color / 256) % 256;
  colorR = color / 65536;
  glBegin(GL_QUADS);
  glColor3ub(colorR,colorG,colorB);
  glVertex2d(x, y);
  glVertex2d(x + w, y);
  glVertex2d(x + w, y + h);
  glVertex2d(x, y + h);
  glEnd();
}

void		arcade::DisplayOpengl::drawColor(const size_t x, const size_t y,
						 const size_t id) const
{
  double		tmpx, tmpy;
  size_t		colorR, colorG, colorB;

  tmpx = static_cast<double>(x) * _mapX;
  tmpy = static_cast<double>(y) * _mapY;
  colorB = _tabColor.at(id) % 256;
  colorG = (_tabColor.at(id) / 256) % 256;
  colorR = _tabColor.at(id) / 65536;
  glBegin(GL_QUADS);
  glColor3ub(colorR, colorG, colorB);
  glVertex2d(tmpx, tmpy + 100);
  glVertex2d(tmpx + _mapX, tmpy + 100);
  glVertex2d(tmpx + _mapX, tmpy + _mapY + 100);
  glVertex2d(tmpx, tmpy + _mapY + 100);
  glEnd();
}

bool		arcade::DisplayOpengl::drawMap(const std::vector<gridPosition*> &map) const
{
  for (std::vector<gridPosition*>::const_iterator it = map.begin(); it != map.end(); ++it)
    {
      drawColor((*it)->x, (*it)->y, (*it)->spriteId);
    }
  return (true);
}

bool		arcade::DisplayOpengl::printText(const std::string &msg, const size_t x,
						 const size_t y, const size_t size,
						 const size_t color) const
{
  (void)msg;
  (void)x;(void)y;(void)size;(void)color;
  return (true);
}

bool		arcade::DisplayOpengl::drawHeader(const std::string &msg1,
							const std::string &msg2,
							const size_t len) const
{
  std::ostringstream	str;

  glClear(GL_COLOR_BUFFER_BIT);
  drawRectangle(0, 0, _width, 100, 0xFF0000);
  drawRectangle(15, 15, _width - 30, 70, 0x000000);
  printText(msg1, 150, 30, 25, 0x9969BD);
  printText(msg2, 345, 30, 25, 0x9969BD);
  str << "Score: " << len;
  printText(str.str(), 550, 30, 25, 0x9969BD);
  return (true);
}

bool		arcade::DisplayOpengl::setSpriteSheet(const arcade::SpriteSheetInfo &sheet)
{
  _tabColor = sheet.color;
  _mapX = static_cast<double>(_width) / static_cast<double>(sheet.map_x);
  _mapY = static_cast<double>(_height - 100) / static_cast<double>(sheet.map_y);
  return (true);
}

bool		arcade::DisplayOpengl::drawMenu(const arcade::Menu &menu) const
{
  size_t	pos;

  pos = 0;
  drawRectangle(230, 140, 400, 400, 0xFF0000);
  drawRectangle(245, 155, 370, 370, 0x40DFFF);
  printText("MENU", 360, 200, 50, 0xFF0000);
  for (std::vector<std::string>::const_iterator it = menu._lstGame.begin();
       it != menu._lstGame.end(); ++it)
    {
      if (menu._currentGame == pos)
	printText((*it), 380, 300 + pos * 10, 30, 0x0F00FF);
      else
	printText((*it), 380, 300 + pos * 10, 30, 0xFF0000);
      pos++;
    }
  return (true);
}

std::string	arcade::DisplayOpengl::getUserName()
{
  return ("Pierre");
}

extern "C"
{
  arcade::IDisplay	*init_screen(const size_t width, const size_t height)
  {
    if (width == 0 || height == 0)
      throw std::runtime_error("Opengl: size window = 0");
    return new arcade::DisplayOpengl(width, height);
  }

  std::string		getName()
  {
    return "Opengl";
  }
}

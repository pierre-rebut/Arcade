//
// DisplaySfml.cpp for DisplaySfml in /home/rebut_p/Programmation/CPP/cpp_arcade/lib/lib1
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 16 15:48:29 2016 Pierre Rebut
// Last update Sun Apr  3 21:14:13 2016 Pierre Rebut
//

#include	<unistd.h>
#include	<utility>
#include	<iostream>
#include	<sstream>
#include	"DisplaySfml.hpp"

static const std::pair<int, arcade::CommandType> keyConf[] = {
  { sf::Keyboard::F12, arcade::CommandType::ENTER},
  { sf::Keyboard::Escape, arcade::CommandType::EXIT},
  { sf::Keyboard::Up, arcade::CommandType::GO_UP},
  { sf::Keyboard::Down, arcade::CommandType::GO_DOWN},
  { sf::Keyboard::Left, arcade::CommandType::GO_LEFT},
  { sf::Keyboard::Right, arcade::CommandType::GO_RIGHT},
  { sf::Keyboard::F2, arcade::CommandType::DISPLAY_PREV},
  { sf::Keyboard::F3, arcade::CommandType::DISPLAY_NEXT},
  { sf::Keyboard::F4, arcade::CommandType::GAME_PREV},
  { sf::Keyboard::F5, arcade::CommandType::GAME_NEXT},
  { sf::Keyboard::F8, arcade::CommandType::RELOAD},
  { sf::Keyboard::F9, arcade::CommandType::MENU},
  { sf::Keyboard::Space, arcade::CommandType::PLAY},
  { sf::Keyboard::K, arcade::CommandType::SHOOT},
  { sf::Keyboard::F10, arcade::CommandType::WHERE_AM_I},
  { sf::Keyboard::F1, arcade::CommandType::GET_MAP}
};

arcade::DisplaySfml::DisplaySfml(const size_t width, const size_t height)
{
  _tabTexture = NULL;
  _window = new sf::RenderWindow();
  if (_window == NULL)
    throw std::runtime_error("sfml: can't init window");
  _width = width;
  _height = height;
  if (!_font.loadFromFile("CaviarDreams_Italic.ttf"))
    std::cerr << "Error Display: No police available" << std::endl;
}

arcade::DisplaySfml::~DisplaySfml()
{
  if (_tabTexture != NULL)
    delete _tabTexture;
  delete _window;
}

bool			arcade::DisplaySfml::newWin()
{
  if (_window == NULL)
    return (false);
  _window->create(sf::VideoMode(_width, _height), "Arcade", sf::Style::Titlebar);
  _window->clear();
  return (true);
}

bool			arcade::DisplaySfml::destroyWin()
{
  _window->close();
  return (true);
}

void			arcade::DisplaySfml::updateWindow(const size_t timer) const
{
  _window->display();
  usleep(timer * 500);
}

arcade::CommandType	arcade::DisplaySfml::getEvent() const
{
  sf::Event		event;

  while (_window->pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
	for (int i = 0; i < 16; i++)
	  {
	    if (event.key.code == keyConf[i].first)
	      return (keyConf[i].second);
	  }
    }
  return (CommandType::DEFAULT);
}

void			arcade::DisplaySfml::drawRectangle(const size_t x, const size_t y,
							   const size_t w, const size_t h,
							   const sf::Color color) const
{
  sf::RectangleShape	rec(sf::Vector2f(w, h));

  rec.setFillColor(color);
  rec.move(x, y);
  _window->draw(rec);
}

void			arcade::DisplaySfml::drawSprite(const size_t x, const size_t y,
							const size_t id) const
{
  sf::Vector2u		tmp;
  sf::Sprite		sprite;

  sprite.setTexture(_tabTexture->at(id));
  tmp = _tabTexture->at(id).getSize();
  sprite.move(static_cast<double>(x) * _mapX, static_cast<double>(y) * _mapY + 100);
  sprite.setScale(_mapX / tmp.x, _mapY / tmp.y);
  _window->draw(sprite);
}

void			arcade::DisplaySfml::drawColor(const size_t x, const size_t y,
						       const size_t id) const
{
  sf::RectangleShape	rec(sf::Vector2f(_mapX, _mapY));
  size_t		colorR, colorG, colorB;

  colorB = (_tabColor.at(id) % 256);
  colorG = (_tabColor.at(id) / 256) % 256;
  colorR = (_tabColor.at(id) / 65536);
  rec.setFillColor(sf::Color(colorR, colorG, colorB));
  rec.move(static_cast<double>(x) * _mapX, static_cast<double>(y) * _mapY + 100);
  _window->draw(rec);
}

bool			arcade::DisplaySfml::drawMap(const std::vector<gridPosition*> &map) const
{
  for (std::vector<gridPosition*>::const_iterator it = map.begin(); it != map.end(); ++it)
    {
      if (_tabTexture != NULL)
	drawSprite((*it)->x, (*it)->y, (*it)->spriteId);
      else
	drawColor((*it)->x, (*it)->y, (*it)->spriteId);
    }
  return (true);
}

bool			arcade::DisplaySfml::printText(const std::string &msg, const size_t x,
						       const size_t y, const size_t size,
						       const size_t color) const
{
  sf::Text		text;
  size_t		colorR, colorG, colorB;

  colorB = (color % 256);
  colorG = (color / 256) % 256;
  colorR = (color / 65536);
  text.setFont(_font);
  text.setCharacterSize(size);
  text.setColor(sf::Color(colorR, colorG, colorB));
  text.setString(msg);
  text.move(x, y);
  _window->draw(text);
  return (true);
}

bool			arcade::DisplaySfml::drawHeader(const std::string &msg1,
							const std::string &msg2,
							const size_t len) const
{
  std::ostringstream	str;

  _window->clear();
  drawRectangle(0, 0, _width, 100, sf::Color::Red);
  drawRectangle(15, 15, _width - 30, 70, sf::Color::Black);
  printText(msg1, 150, 30, 25, 0x9969BD);
  printText(msg2, 345, 30, 25, 0x9969BD);
  str << "Score: " << len;
  printText(str.str(), 550, 30, 25, 0x9969BD);
  return (true);
}

bool			arcade::DisplaySfml::setSpriteSheet(const arcade::SpriteSheetInfo &sheet)
{
  sf::Texture		texture;
  sf::Image		spriteSheet;
  sf::Vector2u		tmp;
  size_t		spriteX;
  size_t		spriteY;

  if (_tabTexture != NULL)
    {
      delete _tabTexture;
      _tabTexture = NULL;
    }
  _tabColor = sheet.color;
  _mapX = static_cast<double>(_width) / static_cast<double>(sheet.map_x);
  _mapY = static_cast<double>(_height - 100) / static_cast<double>(sheet.map_y);
  if (!spriteSheet.loadFromFile(sheet.path))
    {
      std::cerr << "Warning: SFML: Can't load texture ('" << sheet.path << "')" << std::endl;
      return (false);
    }
  tmp = spriteSheet.getSize();
  spriteX = tmp.x / sheet.nb_elem_x;
  spriteY = tmp.y / sheet.nb_elem_y;
  _tabTexture = new std::vector<sf::Texture>;
  if (_tabTexture == NULL)
    throw std::runtime_error("SFML: error can't alloc mem");
  for (size_t y = 0; y < sheet.nb_elem_y; y++)
    for (size_t x = 0; x < sheet.nb_elem_x; x++)
      {
	texture.loadFromImage(spriteSheet,
			      sf::IntRect(x * spriteX, y * spriteY, spriteX, spriteY));
	texture.setSmooth(true);
	_tabTexture->push_back(texture);
      }
  return (true);
}

bool		arcade::DisplaySfml::drawMenu(const arcade::Menu &menu) const
{
  std::ostringstream	os;
  size_t	pos;
  sf::Text	text;

  drawRectangle(300, 125, 420, 450, sf::Color::Red);
  drawRectangle(315, 140, 390, 420, sf::Color::Cyan);
  printText("MENU", 430, 160, 50, 0xFF0000);
  pos = 0;
  printText("List Game:", 330, 240, 30, 0xFF0000);
  for (std::vector<std::string>::const_iterator it = menu._lstGame.begin();
       it != menu._lstGame.end(); ++it)
    {
      if (menu._currentGame == pos)
	printText((*it), 470, 280 + pos * 40, 25, 0x0F00FF);
      else
	printText((*it), 470, 280 + pos * 40, 25, 0xFF0000);
      pos ++;
    }
  printText("List Display:", 330, 280 + pos * 40, 30, 0xFF0000);
  pos++;
  for (std::vector<std::string>::const_iterator it = menu._lstDisplay.begin();
       it != menu._lstDisplay.end(); ++it)
    {
      printText((*it), 470, 280 + pos * 40, 25, 0xFF0000);
      pos ++;
    }
  drawRectangle(35, 125, 250, 450, sf::Color::Red);
  drawRectangle(50, 140, 220, 420, sf::Color::Cyan);
  pos = 0;
  printText("High score:", 65, 160, 30, 0xFF0000);
  for (std::vector<std::pair<std::string, size_t> >::const_iterator it = menu._score.begin();
       it != menu._score.end(); ++it)
    {
      if (pos == 8)
	break;
      os.str("");
      os << (*it).first << ": " << (*it).second;
      printText(os.str(), 80, 200 + pos * 40, 25, 0xFF0000);
      pos ++;
    }
  drawRectangle(55, 500, 210, 50, sf::Color::Black);
  printText(menu._player, 63, 508, 25, 0xFFFFFF);
  return (true);
}

std::string		arcade::DisplaySfml::getUserName()
{
  std::string		player;
  sf::Event		event;

  while (1)
    {
      while (_window->pollEvent(event))
	{
	  if (event.type == sf::Event::KeyPressed)
	    {
	      if (event.key.code == sf::Keyboard::Return)
		{
		  if (player != "")
		    return (player);
		}
	      else if (event.key.code == sf::Keyboard::BackSpace)
		player.size() > 0 ? player.erase(player.size() - 1, 1) : player = "";
	      else if (event.key.code >= sf::Keyboard::A &&
		       event.key.code <= sf::Keyboard::Z)
		player.size() < 10 ? player += event.key.code + 'A' : player = player;
	    }
	}
      _window->clear();
      drawRectangle(220, 220, 250, 60, sf::Color::Red);
      printText(player, 235, 230, 25, 0xFFFFFF);
      _window->display();
      usleep(500);
    }
  return (player);
}

extern "C"
{
  arcade::IDisplay	*init_screen(const size_t width, const size_t height)
  {
    if (width == 0 || height == 0)
      throw std::runtime_error("SFML: size window = 0");
    return new arcade::DisplaySfml(width, height);
  }

  std::string		getName()
  {
    return "Sfml";
  }
}

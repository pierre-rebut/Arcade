//
// updateScore.cpp for updateScore in /home/rebut_p/Programmation/CPP/cpp_arcade
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Sat Apr  2 17:39:21 2016 Pierre Rebut
// Last update Sun Apr  3 16:02:02 2016 Pierre Rebut
//

#include	"Core.hpp"
#include	<iostream>
#include	<fstream>
#include	<algorithm>

bool pairCompare(std::pair<std::string, size_t> firstElem, std::pair<std::string, size_t> secondElem)
{
  return firstElem.second > secondElem.second;
}

void		arcade::Core::updateFile() const
{
  size_t	pos;
  std::ofstream file;

  pos = 0;
  file.open((_gameName + ".score").c_str(), std::ofstream::out);
  if (file.is_open())
    {
      for (std::vector<std::pair<std::string, size_t> >::const_iterator it =
	     _menu._score.begin(); it != _menu._score.end(); ++it)
	{
	  if (pos == 8)
	    break;
	  std::string str = (*it).first + ":" + std::to_string((*it).second) + "\n";
	  file << str;
	  pos ++;
	}
      file.close();
    }
}

void		arcade::Core::updateScore()
{
  int		pos;

  pos = 0;
  for (std::vector<std::pair<std::string, size_t> >::iterator it = _menu._score.begin();
       it != _menu._score.end(); ++it)
    {
      if ((*it).second < _game->getScore())
	{
	  _menu._score.push_back(std::make_pair(_player, _game->getScore()));
	  std::sort(_menu._score.begin(),  _menu._score.end(), pairCompare);
	  updateFile();
	  return;
	}
      pos ++;
    }
  if (pos < 8)
    _menu._score.push_back(std::make_pair(_player, _game->getScore()));
  std::sort(_menu._score.begin(),  _menu._score.end(), pairCompare);
  updateFile();
}

void		arcade::Core::initScore()
{
  std::string	line;
  std::ifstream	file((_gameName + ".score").c_str());

  _menu._score.clear();
  if (file.is_open())
    {
      std::getline(file, line);
      while (!file.eof())
	{
	  _menu._score.push_back(std::make_pair(line.substr(0, line.find(":")), atol(line.substr(line.find(":") + 1).c_str())));
	  std::getline(file, line);
	}
      std::sort(_menu._score.begin(),  _menu._score.end(), pairCompare);
      file.close();
    }
}

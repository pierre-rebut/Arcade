//
// IGame.hpp for IGame in /home/rebut_p/Programmation/CPP/cpp_arcade/includes
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Tue Mar 15 17:19:13 2016 Pierre Rebut
// Last update Sun Apr  3 21:56:47 2016 Pierre Rebut
//

#ifndef			__IGAME_HPP__
# define		__IGAME_HPP__
# include		<vector>
# include		<stdexcept>
# include		"Map.hpp"
# include		"Protocol.hpp"

namespace		arcade
{
  class			IGame
  {
  public:
    virtual		~IGame() {}

    virtual const std::vector<gridPosition*>&	playMove(const CommandType) = 0;
    virtual const std::vector<gridPosition*>&	getMap() const = 0;

    virtual const arcade::SpriteSheetInfo	getSpriteSheet() const = 0;
    virtual size_t				getScore() const = 0;
    virtual bool				isAlive() const = 0;
    virtual size_t				getUpdateTimer() const = 0;
    virtual bool				Reload() = 0;
  };
}

#endif			/* !__IGAME_HPP__ */

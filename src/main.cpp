//
// main.cpp for arcade in /home/rebut_p/Programmation/CPP/cpp_arcade/arcade/src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Thu Mar 10 11:59:50 2016 Pierre Rebut
// Last update Sun Apr  3 21:55:46 2016 Pierre Rebut
//

#include	<cstring>
#include	<iostream>
#include	"Core.hpp"

bool		getEnv(char **env)
{
  if (env == NULL)
    return (false);
  for (size_t i = 0; env[i] != NULL; i++)
    {
      if (strncmp(env[i], "DISPLAY=", 8) == 0)
	return (true);
    }
  return (false);
}

int		main(int ac, char **av, char **env)
{
  arcade::Core	*core;

  if (getEnv(env) == false)
    {
      std::cerr << "Error: env not set" << std::endl;
    }
  else if (ac != 2)
    std::cerr << "./arcade ./lib/lib_arcade_XXX.so" << std::endl;
  else
    {
      try
	{
	  core = new arcade::Core;
	  if (core == NULL)
	    throw std::runtime_error(" Core: can't alloc mem");
	  core->initMenu();
	  if (core->initCore(av[1]) != false)
	    core->loopGame();
	  delete core;
	}
      catch (const std::exception &e)
	{
	  std::cerr << "Error:" << e.what() << std::endl;
	}
    }
  return (0);
}

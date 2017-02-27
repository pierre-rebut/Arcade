//
// utils.cpp for utils in /home/rebut_p/Programmation/CPP/cpp_arcade/src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 30 15:13:03 2016 Pierre Rebut
// Last update Sun Apr  3 21:32:31 2016 Pierre Rebut
//

#include	<iostream>
#include	"utils.hpp"

std::vector<std::pair<std::string, std::string> >	open_dir(std::string const &pwd)
{
  std::vector<std::pair<std::string, std::string> >	lst;
  std::string			(*ptr)();
  void				*lib;
  DIR				*dir;
  struct dirent			*ent = NULL;
  std::string			file;

  dir = opendir(pwd.c_str());
  if (dir == NULL)
    throw std::runtime_error(" Core: can't open dir: " + pwd);
  else
    {
      while ((ent = readdir(dir)) != NULL)
	{
	  int size = strlen(ent->d_name);
	  if (size > 3 && strcmp(ent->d_name + size - 3, ".so") == 0)
	    {
	      file = pwd + ent->d_name;
	      ptr = open_lib<std::string (*)()>(file, "getName", &lib);
	      if (ptr != NULL)
		lst.push_back(std::make_pair(ptr(), file));
	      if (lib != NULL)
		dlclose(lib);
	    }
	}
      closedir(dir);
    }
  return lst;
}

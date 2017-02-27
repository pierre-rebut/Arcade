//
// utils.hpp for utils in /home/rebut_p/Programmation/CPP/cpp_arcade/src
// 
// Made by Pierre Rebut
// Login   <rebut_p@epitech.net>
// 
// Started on  Wed Mar 30 15:21:40 2016 Pierre Rebut
// Last update Sun Apr  3 21:56:27 2016 Pierre Rebut
//

#ifndef		__UTILS_HPP__
# define	__UTILS_HPP__
# include	<vector>
# include	<utility>
# include	<string>
# include	<cstring>
# include	<cstdlib>
# include	<stdexcept>
# include	<dirent.h>
# include	<dlfcn.h>
# include	<iostream>

template<typename T>
T	open_lib(const std::string &file, const std::string &fct, void **lib)
{
  T	ptr;

  *lib = dlopen(file.c_str(), RTLD_NOW);
  if (*lib == NULL)
    {
      throw std::runtime_error(dlerror());
    }
  ptr = reinterpret_cast<T>(dlsym(*lib, fct.c_str()));
  return (ptr);
}

std::vector<std::pair<std::string, std::string> > open_dir(std::string const &);

#endif		/* !__UITLS_HPP__ */

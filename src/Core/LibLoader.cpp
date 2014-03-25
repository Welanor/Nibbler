#include <iostream>
#include "LibLoader.hpp"
#include <stdio.h>

LibLoader::LibLoader(): _dlhandle(NULL)
{

}

LibLoader::~LibLoader()
{
  if (isOpen())
    close();
}

void LibLoader::open(const std::string &name, int flag)
{
  if (isOpen())
    close();
  _dlhandle = dlopen(name.c_str(), flag);
  perror("dlopen");
  if (_dlhandle == NULL)
    throw(Exception("Error while loading the library: " + name));
  dlerror();
}

void *LibLoader::getSym(const std::string &sym) const
{
  void *ret;
  char *str;

  ret = dlsym(_dlhandle, sym.c_str());
  if ((str = dlerror()) != NULL)
    std::cerr << "Error : " + std::string(str) << std::endl;
  return (ret);
}

void LibLoader::close()
{
  if (dlclose(_dlhandle) != 0)
    throw(Exception(dlerror()));
  _dlhandle = NULL;
}

bool LibLoader::isOpen() const
{
  if (_dlhandle != NULL)
    return (true);
  return (false);
}

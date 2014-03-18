#ifndef _LIBLOADER_HPP_
#define _LIBLOADER_HPP_

#include <string>
#include <dlfcn.h>
#include "Exception.hpp"

class LibLoader
{
public:
  LibLoader();
  LibLoader(const std::string &name, int flag);
  virtual ~LibLoader();

  void open(const std::string &name, int flag);
  void close();
  void *getSym(const std::string &sym) const;
  bool isOpen() const;

private:
  void	*_dlhandle;
};

#endif /* _LIBLOADER_HPP_ */

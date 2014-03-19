#ifndef _IGRAPHICS_H_
#define _IGRAPHICS_H_

#include <string>
#include <iostream>

class IGraphics
{
public:
  virtual ~IGraphics() {};

  virtual void create_window(const std::string &name) = 0;
  virtual void clear() = 0;
  virtual void draw(const std::string &map) = 0;
  virtual void destroyWindow() = 0;
};

#endif /* _IGRAPHICS_H_ */

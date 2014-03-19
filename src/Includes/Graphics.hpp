#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "IGraphics.hpp"

class Graphics : IGraphics
{
public:
  // Graphics();
  //  virtual ~Graphics();

  virtual void create_window(const std::string &name);
  virtual void clear();
  virtual void draw(const std::string &map);
  virtual void destroyWindow();
  virtual void talk();
};

#endif /* _GRAPHICS_H_ */

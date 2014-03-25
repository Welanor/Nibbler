#ifndef _IGRAPHICS_H_
# define _IGRAPHICS_H_

# include <string>
# include <iostream>
# include <list>
# include "Snake.hpp"

class IGraphics
{
public:
  virtual ~IGraphics() {};

  virtual void create_window(const std::string &name, const int ,const int) = 0;
  virtual void clear() = 0;
  virtual void draw(int x, int y, int type) = 0;
  virtual void destroyWindow() = 0;

  virtual void handleEvent(bool *key) = 0;
  virtual bool isDone() = 0;
};

#endif /* _IGRAPHICS_H_ */

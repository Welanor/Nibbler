#ifndef _GRAPHICS_H_
# define _GRAPHICS_H_

# include <curses.h>
# include "IGraphics.hpp"

class Graphics : public IGraphics
{
public:
  Graphics();
  virtual ~Graphics();

  virtual void create_window(const std::string &name, const int, const int);
  virtual void handleEvent(bool *key);
  virtual void clear();
  virtual void draw(int x, int y, int type);
  virtual void destroyWindow();
  virtual bool isDone();

private:
  WINDOW	*_window;
};

#endif /* _GRAPHICS_H_ */

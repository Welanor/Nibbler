#ifndef _GRAPHICS_H_
# define _GRAPHICS_H_

# include <curses.h>
# include "IGraphics.hpp"

class Graphics : public IGraphics
{
public:
  Graphics();
  virtual ~Graphics();

  virtual bool create_window(const std::string &name, const int *, const int *);
  virtual void handleEvent(bool *key);
  virtual void clear();
  virtual void draw(int x, int y, int type, int dir);
  virtual void display_score(int score);
  virtual void update();
  virtual void destroyWindow();

private:
  WINDOW	*_window;
  int		_x;
  int		_y;
};

#endif /* _GRAPHICS_H_ */

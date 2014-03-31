#ifndef _GRAPHICS_H_
# define _GRAPHICS_H_

# include "IGraphics.hpp"
# include <GL/glut.h>
# include <GL/freeglut_ext.h>

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
  virtual void setKey();
private:
  int	_size_win[2];
  int	_size_map[2];
};

#endif /* _GRAPHICS_H_ */

#ifndef _GRAPHICS_H_
# define _GRAPHICS_H_

# include "IGraphics.hpp"

class Graphics : public IGraphics
{
public:
  Graphics();
   virtual ~Graphics();

  virtual void create_window(const std::string &name, const int, const int);
  virtual void clear();
  virtual void draw(const std::list<t_snake> &snake);
  virtual void destroyWindow();

  virtual void handleEvent();
  virtual bool isDone();
};

#endif /* _GRAPHICS_H_ */

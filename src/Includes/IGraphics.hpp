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

  virtual bool create_window(const std::string &name, const int *,const int *) = 0;
  virtual void clear() = 0;
  virtual void draw(int x, int y, int type, int dir) = 0;
  virtual void display_score(int score) = 0;
  virtual void display_f_score(const std::string &name, int score, int y) = 0;
  virtual void update() = 0;
  virtual void destroyWindow() = 0;

  virtual void handleEvent(bool *key) = 0;

};

#endif /* _IGRAPHICS_H_ */

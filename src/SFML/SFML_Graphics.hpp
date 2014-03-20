#ifndef _SFML_HPP_
# define _SFML_HPP_

# include <SFML/Graphics.hpp>
# include "IGraphics.hpp"

class SFMLGraphics : public IGraphics
{
public:
  SFMLGraphics();
   virtual ~SFMLGraphics();

  virtual void create_window(const std::string &name, const int, const int);
  virtual void clear();
  virtual void draw(const std::list<t_snake> &snake);
  virtual void destroyWindow();

  virtual void handleEvent();
  virtual bool isDone();

private:
  sf::RenderWindow	_win;
  int			_size_x;
  int			_size_y;
};

#endif /* _SFML_HPP_ */

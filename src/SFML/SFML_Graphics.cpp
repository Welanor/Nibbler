#include "SFML_Graphics.hpp"

SFMLGraphics::SFMLGraphics(): IGraphics(), _win(), _size_x(0), _size_y(0)
{
  std::cout << "Constructor SFML" << std::endl;
}

SFMLGraphics::~SFMLGraphics()
{
  std::cout << "Destructor SFML" << std::endl;
}

void	SFMLGraphics::create_window(const std::string &name, int size_x, int size_y)
{
  _size_x = size_x;
  _size_y = size_y;
  _win.create(sf::VideoMode(size_x, size_y), name);
}

void	SFMLGraphics::clear()
{
  _win.clear();
}

void	SFMLGraphics::draw(const std::list<t_snake> &snake)
{
  (void)snake;
}

void	SFMLGraphics::destroyWindow()
{

}

void SFMLGraphics::handleEvent()
{

}

bool SFMLGraphics::isDone()
{
  return (false);
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics SFML" << std::endl;
    return (new SFMLGraphics);
  }
}

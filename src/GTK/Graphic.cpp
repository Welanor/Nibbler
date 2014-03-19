#include "Graphics.hpp"

Graphics::Graphics()
{
  std::cout << "Constructor GTK" << std::endl;
}

Graphics::~Graphics()
{
  std::cout << "Destructor GTK" << std::endl;
}

void	Graphics::create_window(const std::string &name, const int /* size_x */, const int /* size_y */)
{
  (void)name;
}

void	Graphics::clear()
{
}

void	Graphics::draw(const std::list<t_snake> &snake)
{
  (void)snake;
}

void	Graphics::destroyWindow()
{
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    return (new Graphics);
  }
}

#include "Graphics.hpp"

Graphics::Graphics()
{
  std::cout << "Constructor GTK" << std::endl;
}

Graphics::~Graphics()
{
  std::cout << "Destructor GTK" << std::endl;
}

void	Graphics::create_window(const std::string &name)
{
  (void)name;
}

void	Graphics::clear()
{
}

void	Graphics::draw(const std::string &map)
{
  (void)map;
}

void	Graphics::destroyWindow()
{
}

extern "C"
{
  Graphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    return (new Graphics);
  }
}

#include "Graphics.hpp"

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

void	Graphics::talk()
{
  std::cout << "GTK lib" << std::endl;
}

Graphics	*init_graphics()
{
  return (new Graphics);
}

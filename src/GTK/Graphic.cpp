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

void	Graphics::init_events()
{
  g_signal_connect(_window, "key-release-event", G_CALLBACK(key_event), NULL);
  g_signal_connect(_window, "key-press-event", G_CALLBACK(key_event), NULL);
}

void Graphics::handleEvent()
{

}

bool Graphics::isDone()
{
  return (false);
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    return (new Graphics);
  }
}

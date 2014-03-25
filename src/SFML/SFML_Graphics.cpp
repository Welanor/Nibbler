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

void SFMLGraphics::draw(int x, int y, int type)
{

}

void SFMLGraphics::destroyWindow()
{

}

void SFMLGraphics::handleKey(bool *key, bool val)
{

}

void SFMLGraphics::handleEvent(bool *key)
{
  sf::Event event;

  while (_win.pollEvent(event))
    {
      switch (event.type)
	{
        case sf::Event::Closed:
	  key[ESC] = true;
	  break;

        case sf::Event::KeyPressed:
	  handleKey(key, true);
	  break;

        case sf::Event::KeyReleased:
	  handleKey(key, false);
	  break;

        default:
	  break;
	}
    }
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    return (new SFMLGraphics);
  }
}

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

void SFMLGraphics::draw(int /*x*/, int /*y*/, int /* type */)
{

}

void SFMLGraphics::destroyWindow()
{
  _win.close();
}

void SFMLGraphics::handleKey(sf::Event event, bool *key, bool val)
{
  switch (event.key.code)
    {
    case sf::Keyboard::Escape:
      key[ESC] = val;
      break;
    case sf::Keyboard::Left:
      key[LEFT] = val;
      break;
    case sf::Keyboard::Right:
      key[RIGHT] = val;
      break;
    case sf::Keyboard::Up:
      key[UP] = val;
      break;
    case sf::Keyboard::Down:
      key[DOWN] = val;
      break;
    default:
      break;
    }
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
        case sf::Event::Resized:
	  _size_x = event.size.width;
	  _size_y = event.size.height;
	  break;
        case sf::Event::KeyPressed:
	  handleKey(event, key, true);
	  break;
        case sf::Event::KeyReleased:
	  handleKey(event, key, false);
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

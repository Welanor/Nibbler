#include "SFML_Graphics.hpp"

SFMLGraphics::SFMLGraphics(): IGraphics(), _win()
{
  _size_map[0] = 0;
  _size_map[1] = 0;
  _size_win[0] = 0;
  _size_win[1] = 0;
  std::cout << "Constructor SFML" << std::endl;
}

SFMLGraphics::~SFMLGraphics()
{
  std::cout << "Destructor SFML" << std::endl;
}

#include <unistd.h>

void	SFMLGraphics::create_window(const std::string &name, const int *size_win, const int *size_map)
{
  _size_win[0] = size_win[0];
  _size_win[1] = size_win[1];
  _size_map[0] = size_map[0];
  _size_map[1] = size_map[1];
  _win.create(sf::VideoMode(size_win[0], size_win[1]), name);
}

void	SFMLGraphics::clear()
{
  _win.clear();
}

void SFMLGraphics::draw(int x, int y, int type)
{
  float			rate_x, rate_y, _x, _y;
  sf::RectangleShape	rect;

  _x = x;
  _y = y;
  rate_x = _size_win[0] / _size_map[0];
  rate_y = _size_win[1] / _size_map[1];
  rect.setSize(sf::Vector2f(rate_x, rate_y));
  rect.setPosition(_x  * rate_x, _y * rate_y);
  rect.setFillColor(sf::Color(255, 255, 255));
  _win.draw(rect);
  _win.display();
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
	  _size_win[0] = event.size.width;
	  _size_win[1] = event.size.height;
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

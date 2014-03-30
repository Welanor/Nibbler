#include "SFML_Graphics.hpp"

SFMLGraphics::SFMLGraphics(): IGraphics(), _music(), _font(), _win()
{
  _size_map[0] = 0;
  _size_map[1] = 0;
  _size_win[0] = 0;
  _size_win[1] = 0;
  std::cout << "Constructor SFML" << std::endl;
}

SFMLGraphics::~SFMLGraphics()
{
  _music.stop();
  std::cout << "Destructor SFML" << std::endl;
}

bool	SFMLGraphics::create_window(const std::string &name, const int *size_win, const int *size_map)
{
  _size_win[0] = size_win[0];
  _size_win[1] = size_win[1];
  _size_map[0] = size_map[0];
  _size_map[1] = size_map[1];
  _win.create(sf::VideoMode(size_win[0], size_win[1]), name);
  if (!_music.openFromFile("Ressource SFML/music.ogg")
      || !_font.loadFromFile("Ressource SFML/font.ttf"))
    return (false);
  _music.setLoop(true);
  _music.setVolume(50);
  _music.play();
  return (true);
}

void	SFMLGraphics::clear()
{
  _win.clear();
}

void SFMLGraphics::draw(int x, int y, int type, int dir)
{
  float			rate_x, rate_y, _x, _y;
  sf::RectangleShape	rect;

  _x = x;
  _y = y;
  rate_x = _size_win[0] / _size_map[0];
  rate_y = _size_win[1] / _size_map[1];
  rect.setSize(sf::Vector2f(rate_x, rate_y));
  rect.setPosition(_x  * rate_x, _y * rate_y);
  if (type == HEAD || type == BUDDY || type == TAIL)
    rect.setFillColor(sf::Color(255, 255, 255));
  else if (type == APPLE)
    rect.setFillColor(sf::Color(124, 252, 0));
  else if (type == GOLD_APPLE)
    rect.setFillColor(sf::Color(255, 215, 0));
  else if (type == BREAD)
    rect.setFillColor(sf::Color(205, 133, 63));
  else if (type == CHICKEN)
    rect.setFillColor(sf::Color(255, 228, 181));
  else if (type == PORK)
    rect.setFillColor(sf::Color(245, 222, 179));
  _win.draw(rect);
}

void SFMLGraphics::destroyWindow()
{
  _win.close();
}

void SFMLGraphics::handleKey(sf::Event event, bool *key)
{
  int		keys[LAST] = { sf::Keyboard::Down, sf::Keyboard::Up, sf::Keyboard::Left,
			   sf::Keyboard::Right, sf::Keyboard::Escape};
  int		i;

  for (i = 0; i < LAST; i++)
    key[i] = false;
  for (i = 0; i < LAST && keys[i] != event.key.code; i++);
  if (i < LAST)
    key[i] = true;
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
	  handleKey(event, key);
	  break;
        default:
	  break;
	}
    }
}

void	SFMLGraphics::update()
{
  _win.display();
}

void	SFMLGraphics::display_score(int score)
{
  sf::Text text;
  std::stringstream ss("");

  ss << "Score: ";
  ss << score;

  std::cout << ss.str() << std::endl;
  text.setFont(_font);
  text.setString(ss.str());
  text.setCharacterSize(24);
  text.setPosition(0, 0);
  text.setColor(sf::Color::Red);
  _win.draw(text);
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    return (new SFMLGraphics);
  }
}

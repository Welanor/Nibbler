#include "SFML_Graphics.hpp"

SFMLGraphics::SFMLGraphics(): IGraphics(), _music(), _font(), _win()
{
  sf::Texture tmp;

  _size_map[0] = 0;
  _size_map[1] = 0;
  _size_win[0] = 0;
  _size_win[1] = 0;
  _color[HEAD] = sf::Color(255, 255, 255);
  _color[BUDDY] = sf::Color(255, 255, 255);
  _color[TAIL] = sf::Color(255, 255, 255);
  _color[APPLE] = sf::Color(124, 252, 0);
  _color[PEAR] = sf::Color(255, 215, 0);
  _color[STRAWBERRY] = sf::Color(205, 133, 63);
  _color[BANANA] = sf::Color(255, 228, 181);
  _color[KIWI] = sf::Color(245, 222, 179);
  _sprites[HEAD] = NULL;
  _sprites[BUDDY] = NULL;
  _sprites[TAIL] = NULL;
  _sprites[APPLE] = NULL;
  _sprites[PEAR] = NULL;
  _sprites[STRAWBERRY] = NULL;
  _sprites[BANANA] = NULL;
  _sprites[KIWI] = NULL;
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
  if (!_music.openFromFile(std::string(RESSOURCE_SFML) + "music.ogg")
    || !_font.loadFromFile(std::string(RESSOURCE_SFML) + "font.ttf"))
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
  if (_sprites[type] == NULL)
    rect.setFillColor(_color[type]);
  // else
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

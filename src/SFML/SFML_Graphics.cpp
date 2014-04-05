#include "SFML_Graphics.hpp"

SFMLGraphics::SFMLGraphics(): IGraphics(), _sprites(), _background(), _music(), _font(),
			      _win(), _vol(50)
{
  _size_map[0] = 0;
  _size_map[1] = 0;
  _size_win[0] = 0;
  _size_win[1] = 0;
}

SFMLGraphics::~SFMLGraphics()
{
  _music.stop();
}

bool	SFMLGraphics::create_window(const std::string &name, const int *size_win, const int *size_map)
{
  sf::Texture tmp;

  _size_win[0] = size_win[0];
  _size_win[1] = size_win[1];
  _size_map[0] = size_map[0];
  _size_map[1] = size_map[1];
  _win.create(sf::VideoMode(size_win[0], size_win[1]), name);
  if (!_sprites.loadFromFile(std::string(RESSOURCE_SFML) + "sprite.png") ||
      !_background.loadFromFile(std::string(RESSOURCE_SFML) + "grass.png") ||
      !_font.loadFromFile(std::string(RESSOURCE_SFML) + "font.ttf"))
    return (false);
  if (_music.openFromFile(std::string(RESSOURCE_SFML) + "music.ogg"))
    {
      _music.setLoop(true);
      _music.setVolume(_vol);
      _music.play();
    }
  return (true);
}

void	SFMLGraphics::clear()
{
  sf::Sprite tmp;

  tmp.setTexture(_background);
  tmp.setScale(sf::Vector2f(_size_win[0] / _background.getSize().x,
			    _size_win[1] / _background.getSize().y));
  _win.clear();
  _win.draw(tmp);
}

void SFMLGraphics::draw(int x, int y, int type, int dir)
{
  sf::Sprite		tmp(_sprites);
  double		rate_x, rate_y, _x, _y;
  sf::RectangleShape	rect;

  _x = x;
  _y = y;
  rate_x = _size_win[0] / _size_map[0];
  rate_y = _size_win[1] / _size_map[1];
  if (dir == RIGHT)
    {
      tmp.setTextureRect(sf::IntRect((type + 1) * SIZE_PNG, 0, -SIZE_PNG, SIZE_PNG));
      tmp.setOrigin(SIZE_PNG / 2, SIZE_PNG / 2);
    }
  else
    {
      tmp.setTextureRect(sf::IntRect(type * SIZE_PNG, 0, SIZE_PNG, SIZE_PNG));
      tmp.setOrigin(SIZE_PNG / 2, SIZE_PNG / 2);
      tmp.rotate(dir * 90);
    }
  tmp.scale(sf::Vector2f(rate_x / SIZE_PNG, rate_y / SIZE_PNG));
  tmp.setPosition(sf::Vector2f(_x * rate_x + (rate_x  / 2),
			       _y * rate_y + (rate_y  / 2)));
  _win.draw(tmp);
}

void SFMLGraphics::destroyWindow()
{
  _win.close();
}

void SFMLGraphics::handleKey(sf::Event event, bool *key)
{
  int		keys[LAST] = { sf::Keyboard::Q, sf::Keyboard::Z, sf::Keyboard::D,
			       sf::Keyboard::S, sf::Keyboard::Left, sf::Keyboard::Right,
			       sf::Keyboard::Escape, sf::Keyboard::P, sf::Keyboard::R};
  int		i;

  for (i = 0; i < LAST && keys[i] != event.key.code; i++);
  if (i < LAST)
    key[i] = !key[i];
  if (event.key.code == sf::Keyboard::Add)
    {
      _vol += 5;
      _music.setVolume(_vol);
    }
  else if (event.key.code == sf::Keyboard::Subtract)
    {
      _vol -= 5;
      _music.setVolume(_vol);
    }
  if (event.key.code == sf::Keyboard::Multiply)
    (_music.getStatus() == sf::SoundSource::Paused) ? _music.play() : _music.pause();
}

void SFMLGraphics::handleEvent(bool *key)
{
  sf::Event event;

  for (int i = 0; i < LAST; i++)
    {
      if (i != PAUSE)
	key[i] = false;
    }
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
	  _win.setView(sf::View(sf::FloatRect(0, 0, _size_win[0], _size_win[1])));
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

void	SFMLGraphics::display_f_score(const std::string &name, int score, int y)
{
  sf::Text text;
  std::stringstream ss("");

  ss << name;
  ss << " ";
  ss << score;

  text.setFont(_font);
  text.setString(ss.str());
  text.setCharacterSize(24);
  text.setPosition(_size_win[0] / 2 - 15, (_size_win[1] / 10) * y);
  text.setColor(sf::Color::Blue);
  _win.draw(text);
}

void	SFMLGraphics::display_pause_msg()
{
  sf::Text text;

  text.setFont(_font);
  text.setString("PAUSE");
  text.setCharacterSize(24);
  text.setPosition(_size_win[0] / 2 - 15, _size_win[1] / 2);
  text.setColor(sf::Color::Red);
  _win.draw(text);
  _win.display();
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    return (new SFMLGraphics);
  }
}

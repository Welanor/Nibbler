#ifndef _SFML_HPP_
# define _SFML_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <map>
# include <sstream>
# include "IGraphics.hpp"

# define RESSOURCE_SFML "../Ressource/SFML/"

class SFMLGraphics : public IGraphics
{
public:
  SFMLGraphics();
   virtual ~SFMLGraphics();

  virtual bool create_window(const std::string &name, const int *, const int *);
  virtual void clear();
  virtual void draw(int x, int y, int type, int dir);
  virtual void display_score(int score);
  virtual void display_pause_msg();
  virtual void display_f_score(const std::string &name, int score, int y);
  virtual void update();
  virtual void destroyWindow();

  virtual void handleEvent(bool *key);
  virtual void handleKey(sf::Event event, bool *key);

private:
  std::map<int, sf::Texture *>	_sprites;
  std::map<int, sf::Color>	_color;
  sf::Texture			_background;
  sf::Music			_music;
  sf::Font			_font;
  sf::RenderWindow		_win;
  int				_vol;
  float				_size_win[2];
  float				_size_map[2];
};

#endif /* _SFML_HPP_ */

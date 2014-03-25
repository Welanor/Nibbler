#ifndef _GAME_HPP_
# define _GAME_HPP_

# define WINX 800
# define WINY 600
# define FPS 5

# include <iostream>
# include <sstream>
# include <list>
# include <vector>
# include <ctime>
# include "Exception.hpp"
# include "LibLoader.hpp"
# include "Snake.hpp"
# include "IGraphics.hpp"

typedef std::list<t_snake>::iterator lit;
typedef std::list<t_snake>::const_iterator c_lit;
typedef std::vector<t_ent>::iterator vit;
typedef std::vector<t_ent>::const_iterator c_vit;

# define PROB	20

class Game
{
public:
  Game(const int ac, char **av);
  virtual ~Game();

  void	start();

private:
  void	parse_arg(const int ac, char **av);
  bool	check_collision();
  void	move_snake(bool *key);
  void	display();
  void	add_entities();

private:
  int			_x;
  int			_y;
  IGraphics		*_window;
  LibLoader		_lib;
  bool			_key[4];
  std::list<t_snake>	_snake;
  std::vector<t_ent>	_ent;
};

#endif /* _GAME_H_ */

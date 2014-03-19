#ifndef _GAME_HPP_
# define _GAME_HPP_

# define WINX 800
# define WINY 600
# define FPS 60

# include <iostream>
# include <sstream>
# include <list>
# include "Exception.hpp"
# include "LibLoader.hpp"
# include "Snake.hpp"
# include "IInput.hpp"
# include "IGraphics.hpp"

class Game
{
public:
  Game(const int ac, char **av);
  virtual ~Game();

  void	start();

private:
  void	parse_arg(const int ac, char **av);
  bool	check_collision() const;

private:
  int			_x;
  int			_y;
  IGraphics		*_window;
  IInput		*_input;
  LibLoader		_lib;
  std::list<t_snake>	_snake;
};

#endif /* _GAME_H_ */

#ifndef _GAME_HPP_
# define _GAME_HPP_

# define WINX 800
# define WINY 600

# include <iostream>
# include <sstream>
# include "Exception.hpp"

class Game
{
public:
  Game(int ac, char **av);
  virtual ~Game();

  void	start();

private:
  int		_x;
  int		_y;
  int		_size_winx;
  int		_size_winy;
  std::string	_libname;
};

#endif /* _GAME_H_ */

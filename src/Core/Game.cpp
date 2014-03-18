#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _size_winx(WINX), _size_winy(WINY), _lib()
{
  std::stringstream ss("");
  std::string libname("");

  if (ac != 4)
    throw(Exception("Usage: ./nibbler size_x size_y lib_nibbler_XXX.so"));
  ss.str(av[1]);
  if (!(ss >> _x) || _x <= 0)
    throw(Exception("Size X invalid"));
  ss.clear();
  ss.str(av[2]);
  if (!(ss >> _y) || _y <= 0)
    throw(Exception("Size Y invalid"));
  _lib.open(av[3], RTLD_LAZY);
}

Game::~Game()
{
  _lib.close();
}

void	Game::start()
{
   std::cout << "X = " << _x << std::endl;
  std::cout << "Y = " << _y << std::endl;
}

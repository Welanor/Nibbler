#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _size_winx(WINX), _size_winy(WINY), _libname("")
{
  std::stringstream ss("");

  if (ac != 4)
    throw(Exception("Usage: ./nibbler size_x size_y lib_nibbler_XXX.so"));
  ss.str(av[1]);
  if (!(ss >> _x) || _x <= 0)
    throw(Exception("Size X invalid"));
  ss.clear();
  ss.str(av[2]);
  if (!(ss >> _y) || _y <= 0)
    throw(Exception("Size Y invalid"));
  _libname = av[3];
}

Game::~Game()
{

}

void	Game::start()
{
  std::cout << "LIBNAME = " << _libname << std::endl;
  std::cout << "X = " << _x << std::endl;
  std::cout << "Y = " << _y << std::endl;
}

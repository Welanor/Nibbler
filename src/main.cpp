#include <iostream>
#include "Game.hpp"
#include "Exception.hpp"

int		main(int ac, char **av)
{
  try
    {
      Game	game(ac, av);

      game.start();
    }
  catch (Exception &e)
    {
      std::cout << e.what() << std::endl;
      return (1);
    }
  return (0);
}

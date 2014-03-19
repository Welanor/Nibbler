#include "Input.hpp"

unsigned int	Input::getTime()
{
  return (0);
}

void		Input::getEvent()
{
}

bool		Input::isDone()
{
  return (false);
}

void		Input::sleep(unsigned int time)
{
  (void)time;
}

extern "C"
{
  Input		*init_input()
  {
    std::cout << "init input" << std::endl;
    return (new Input);
  }
}

#include "SFML_Input.hpp"

SFMLInput::SFMLInput() : IInput(), _clock(), _done(false)
{

}

SFMLInput::~SFMLInput()
{

}

unsigned int	SFMLInput::getTime()
{
  return (0);
}

void		SFMLInput::getEvent()
{

}

bool		SFMLInput::isDone()
{
  return (_done);
}

void		SFMLInput::sleep(unsigned int time)
{
  (void)time;
}

extern "C"
{
  IInput	*init_input()
  {
    return (new SFMLInput);
  }
}

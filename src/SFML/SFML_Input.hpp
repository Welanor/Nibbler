#ifndef _SFMLINPUT_HPP_
#define _SFMLINPUT_HPP_

#include <SFML/System.hpp>
#include "IInput.hpp"

class SFMLInput : public IInput
{
public:
  SFMLInput();
  virtual ~SFMLInput();

  virtual unsigned int getTime();
  virtual void getEvent();
  virtual bool isDone();
  virtual void sleep(unsigned int time);

private:
  sf::Clock _clock;
  bool	    _done;
};

#endif /* _SFMLINPUT_HPP_ */

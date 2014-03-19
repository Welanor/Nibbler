#ifndef _IINPUT_H_
#define _IINPUT_H_

#include <string>
#include <iostream>

class IInput
{
public:
  virtual ~IInput() {};

  virtual unsigned int getTime() = 0;
  virtual void getEvent() = 0;
  virtual bool isDone() = 0;
  virtual void sleep(unsigned int time) = 0;
};

#endif /* _IINPUT_H_ */

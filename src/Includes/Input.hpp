#ifndef _INPUT_H_
#define _INPUT_H_

#include "IInput.hpp"

class Input : public IInput
{
public:
  virtual unsigned int getTime();
  virtual void getEvent();
  virtual bool isDone();
  virtual void sleep(unsigned int time);
};

#endif /* _INPUT_H_ */

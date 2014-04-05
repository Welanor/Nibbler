#ifndef _TIMER_HPP_
# define _TIMER_HPP_

# include <sys/time.h>
# include <iostream>

class Timer
{
public:
  Timer();
  virtual ~Timer();

  Timer &operator-=(const Timer &cpy);
  bool	operator<(double val) const;

  void	startTimer();
  double getTimer() const;

private:

  struct timeval _time;
};

#endif /* _TIMER_HPP_ */

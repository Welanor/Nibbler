#ifndef _TIME_HPP_
# define _TIME_HPP_

# include <sys/time.h>
# include <iostream>

class Time
{
public:
  Time();
  virtual ~Time();

  Time &operator-=(const Time &cpy);
  bool	operator<(double val) const;

  void	startTime();
  const double getTime() const;

private:

  struct timeval _time;
};

#endif /* _TIME_HPP_ */

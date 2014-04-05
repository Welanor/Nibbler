#include "Timer.hpp"

Timer::Timer()
{

}

Timer::~Timer()
{

}

Timer	&Timer::operator-=(const Timer &cpy)
{
  _time.tv_sec -= cpy._time.tv_sec;
  _time.tv_usec -= cpy._time.tv_usec;
  return (*this);
}

bool	Timer::operator<(double val) const
{
  return ((_time.tv_sec * 1000.0 + _time.tv_usec / 1000.0) < val);
}

double	Timer::getTimer() const
{
  return (_time.tv_sec * 1000.0 + _time.tv_usec / 1000.0);
}

void	Timer::startTimer()
{
  gettimeofday(&_time, NULL);
}

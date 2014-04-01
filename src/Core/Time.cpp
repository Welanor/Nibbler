#include "Time.hpp"

Time::Time()
{

}

Time::~Time()
{

}

Time	&Time::operator-=(const Time &cpy)
{
  _time.tv_sec -= cpy._time.tv_sec;
  _time.tv_usec -= cpy._time.tv_usec;
  return (*this);
}

bool	Time::operator<(double val) const
{
  return ((_time.tv_sec * 1000.0 + _time.tv_usec / 1000.0) < val);
}

double	Time::getTime() const
{
  return (_time.tv_sec * 1000.0 + _time.tv_usec / 1000.0);
}

void	Time::startTime()
{
  gettimeofday(&_time, NULL);
}

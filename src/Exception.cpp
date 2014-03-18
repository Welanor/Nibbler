#include "Exception.hpp"

Exception::Exception(const std::string &str) throw() : _what(str)
{

}

Exception::Exception(const Exception& cpy) throw() : _what(cpy._what)
{

}

Exception& Exception::operator= (const Exception& cpy) throw()
{
  _what = cpy._what;
  return (*this);
}

Exception::~Exception() throw()
{

}

const char* Exception::what() const throw()
{
  return (_what.c_str());
}

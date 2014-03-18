#ifndef _EXCEPTION_H_
# define _EXCEPTION_H_

# include <string>
# include <exception>

class Exception : public std::exception
{
public:
  Exception(const std::string &str) throw();
  Exception(const Exception&) throw();
  Exception& operator= (const Exception&) throw();
  virtual ~Exception() throw();
  virtual const char* what() const throw();

private:
  std::string	_what;
};

#endif /* _EXCEPTION_H_ */

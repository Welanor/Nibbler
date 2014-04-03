//
// Camera.hpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:39:57 2014 Etienne
// Last update Thu Apr  3 22:49:07 2014 Etienne
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <map>
#include <string>

class		Camera
{
public:
  Camera(float eyex, float eyey, float eyez,
	 float dirx, float diry, float dirz,
	 float sensivity);
  ~Camera();
  void		look();
  void		look(float,float,float);
  void		reinit_pos();
  void	        left();
  void	        right();
  void	        near();
  void	        far();
private:
  std::map<std::string, float>	_base_pos;
  std::map<std::string, float>	_custom_pos;
  float				_sensivity;
};

#endif /* _CAMERA_H_ */

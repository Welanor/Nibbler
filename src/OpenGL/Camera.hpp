//
// Camera.hpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:39:57 2014 Etienne
// Last update Fri Apr  4 16:27:49 2014 Etienne
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <map>
#include <string>
#include <vector>
#include "Snake.hpp"

typedef std::vector<float> color;

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
  void		followSnake(int dir, int *headPos);
  void		moveEye(int eyex, int eyey, int eyez);
  const std::map<std::string, float>    getEyePos() const;
  // void	        left();
  // void	        right();
  // void	        near();
  // void	        far();
private:
  std::map<std::string, float>	_base_pos;
  std::map<std::string, float>	_custom_pos;
  float				_sensivity;
};

#endif /* _CAMERA_H_ */

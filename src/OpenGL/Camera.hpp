//
// Camera.hpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:39:57 2014 Etienne
// Last update Fri Apr  4 20:14:57 2014 Etienne
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <map>
#include <string>
#include <vector>
#include "Snake.hpp"

# define MAX_UP 100
# define MAX_DOWN 1

enum camMovement
  {
    CAM_UP = 0,
    CAM_DOWN,
    CAM_NEAR,
    CAM_FAR,
  };

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
  void		moveEye(camMovement mov, int *headPos);
  const std::map<std::string, float>    getEyePos() const;
private:
  std::map<std::string, float>	_base_pos;
  std::map<std::string, float>	_custom_pos;
  float				_sensivity;
};

#endif /* _CAMERA_H_ */

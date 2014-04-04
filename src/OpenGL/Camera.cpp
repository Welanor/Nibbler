
//
// Camera.cpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:50:28 2014 Etienne
// Last update Fri Apr  4 20:35:06 2014 Etienne
//

#include <GL/glut.h>
#include "Camera.hpp"

Camera::Camera(float eyex, float eyey, float eyez,
	       float dirx, float diry, float dirz,
	       float sensivity)
{
  _base_pos["eyex"] = _custom_pos["eyex"] = eyex;
  _base_pos["eyey"] = _custom_pos["eyey"] = eyey;
  _base_pos["eyez"] = _custom_pos["eyez"] = eyez;
  _base_pos["dirx"] = _custom_pos["dirx"] = dirx;
  _base_pos["diry"] = _custom_pos["diry"] = diry;
  _base_pos["dirz"] = _custom_pos["dirz"] = dirz;
  _sensivity = sensivity;
}

void		Camera::look()
{
  gluLookAt(_custom_pos["eyex"], _custom_pos["eyey"], _custom_pos["eyez"],
	    _custom_pos["dirx"], _custom_pos["diry"], _custom_pos["dirz"],
	    0, 1, 0);
}

void		Camera::look(float dirx, float diry, float dirz)
{
  gluLookAt(_custom_pos["eyex"], _custom_pos["eyey"], _custom_pos["eyez"],
	    dirx, diry, dirz,
	    0, 1, 0);
}

void		Camera::reinit_pos()
{
  _custom_pos["eyex"] = _base_pos["eyex"];
  _custom_pos["eyey"] = _base_pos["eyey"];
  _custom_pos["eyez"] = _base_pos["eyez"];
  _custom_pos["dirx"] = _base_pos["dirx"];
  _custom_pos["diry"] = _base_pos["diry"];
  _custom_pos["dirz"] = _base_pos["dirz"];
}

void	        Camera::followSnake(int snakedir, int *headPos)
{
  switch (snakedir)
    {
    case DOWN :
      _custom_pos["eyez"] -= _sensivity;
      break;
    case UP :
      _custom_pos["eyez"] += _sensivity;
      break;
    case LEFT :
      _custom_pos["eyex"] -= _sensivity;
      break;
    case RIGHT :
      _custom_pos["eyex"] += _sensivity;
      break;
    }
}

void	        Camera::moveEye(int eyex, int eyey, int eyez)
{
  _custom_pos["eyex"] = eyex;
  _custom_pos["eyey"] = eyey;
  _custom_pos["eyez"] = eyez;
}

const std::map<std::string, float>	Camera::getEyePos() const
{
  return _custom_pos;
}

void	        Camera::moveEye(camMovement mov, int *headPos)
{
  switch (mov)
    {
    case CAM_UP :
      _custom_pos["eyey"] += _sensivity;
      if (_custom_pos["eyey"] > MAX_UP)
	_custom_pos["eyey"] = MAX_UP;
      break;
    case CAM_DOWN :
      _custom_pos["eyey"] -= _sensivity;
      if (_custom_pos["eyey"] < MAX_DOWN)
	_custom_pos["eyey"] = MAX_DOWN;
      break;
    case CAM_NEAR :
      _custom_pos["eyez"] -= _sensivity;
      if (_custom_pos["eyez"] < static_cast<float>(-headPos[1]))
	_custom_pos["eyez"] = static_cast<float>(-headPos[1]);
      break;
    case CAM_FAR :
      _custom_pos["eyez"] += _sensivity;
      break;
    }
}

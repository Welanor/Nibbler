
//
// Camera.cpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:50:28 2014 Etienne
// Last update Sun Apr  6 00:11:26 2014 Etienne
//

#include <GL/glut.h>
#include <iostream>
#include "Camera.hpp"

Camera::Camera(float eyex, float eyey, float eyez,
	       float dirx, float diry, float dirz,
	       float sensivity)
{
  for (int i = 0 ; i < 4 ; i++)
    {
      _eventCam[static_cast<camMovement>(i)] = false;
    }
  _base_pos["eyex"] = _custom_pos["eyex"] = eyex;
  _base_pos["eyey"] = _custom_pos["eyey"] = eyey;
  _base_pos["eyez"] = _custom_pos["eyez"] = eyez;
  _base_pos["dirx"] = _custom_pos["dirx"] = dirx;
  _base_pos["diry"] = _custom_pos["diry"] = diry;
  _base_pos["dirz"] = _custom_pos["dirz"] = dirz;
  _associatedKey['t'] = CAM_UP;
  _associatedKey['y'] = CAM_DOWN;
  _associatedKey['u'] = CAM_NEAR;
  _associatedKey['i'] = CAM_FAR;
  _sensivity = sensivity;
}

void		Camera::look()
{
  gluLookAt(_custom_pos["eyex"], _custom_pos["eyey"], _custom_pos["eyez"],
	    _custom_pos["dirx"], _custom_pos["diry"], _custom_pos["dirz"],
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

void	        Camera::followSnake(int snakedir)
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
void	        Camera::moveDir(int dirx, int diry, int dirz)
{
  _custom_pos["dirx"] = dirx;
  _custom_pos["diry"] = diry;
  _custom_pos["dirz"] = dirz;
}

const std::map<std::string, float>	Camera::getEyePos() const
{
  return _custom_pos;
}

void	        Camera::moveEye(camMovement mov)
{
  switch (mov)
    {
    case CAM_UP :
      _custom_pos["eyey"] += _sensivity;
      if (_custom_pos["eyey"] >= MAX_UP)
	_custom_pos["eyey"] = MAX_UP;
      break;
    case CAM_DOWN :
      _custom_pos["eyey"] -= _sensivity;
      if (_custom_pos["eyey"] <= MAX_DOWN)
	_custom_pos["eyey"] = MAX_DOWN;
      break;
    case CAM_NEAR :
      _custom_pos["eyez"] -= _sensivity;
      if (_custom_pos["eyez"] < _custom_pos["dirz"])
	_custom_pos["eyez"] += _sensivity;
      break;
    case CAM_FAR :
      _custom_pos["eyez"] += _sensivity;
      break;
    }
}

void		Camera::setEvent(camMovement event, bool status)
{
  _eventCam[event] = status;
}

std::map<unsigned char, camMovement>	Camera::getAssocitedKey() const
{
  return _associatedKey;
}

void		Camera::updateEvent()
{
  camMovement	mov;

  for (int i = 0 ; i < 4 ; i++)
    {
      mov = static_cast<camMovement>(i);
      if (_eventCam[mov] == true)
	this->moveEye(mov);
    }
}

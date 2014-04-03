//
// Camera.cpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:50:28 2014 Etienne
// Last update Thu Apr  3 22:50:01 2014 Etienne
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

void	        Camera::left()
{

}

void	        Camera::right()
{

}

void	        Camera::near()
{

}

void	        Camera::far()
{

}
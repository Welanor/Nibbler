
//
// Camera.hpp for cam in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Thu Apr  3 21:39:57 2014 Etienne
// Last update Sat Apr  5 22:04:34 2014 Etienne
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
  void		followSnake(int dir);
  void		moveEye(int eyex, int eyey, int eyez);
  void		moveDir(int dirx, int diry, int dirz);
  void		moveEye(camMovement mov);
  void		setEvent(camMovement, bool);
  void		updateEvent();
  std::map<unsigned char, camMovement>	getAssocitedKey() const;
  const std::map<std::string, float>    getEyePos() const;
private:
  std::map<camMovement, bool>		_eventCam;
  std::map<std::string, float>		_base_pos;
  std::map<std::string, float>		_custom_pos;
  std::map<unsigned char, camMovement>	_associatedKey;
  float					_sensivity;
};

#endif /* _CAMERA_H_ */

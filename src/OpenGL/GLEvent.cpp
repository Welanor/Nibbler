//
// GLEvent.cpp for GLevent.cpp in /home/debas_e/Project/C++/cpp_nibbler
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 21:14:38 2014 Etienne
// Last update Sat Apr  5 17:34:19 2014 Etienne
//

#include "Graphic.hpp"
#include <stdio.h>

extern Graphics	*graphic;

void	catchSpecialKey(int key, int x, int y)
{
  int	associativeKey[4] = {GLUT_KEY_LEFT, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_UP};

  for (int i = 0 ; i < 4 ; i++)
    graphic->setKey(i, false);

  for (int i = 0; i < 4; i++)
    if (associativeKey[i] == key)
      graphic->setKey(i, true);

  if (key == GLUT_KEY_F1)
    graphic->changeFirst();
  else if (key == GLUT_KEY_F2)
    graphic->changeFollowSnake();
  glutPostRedisplay();
}

void		catchBasicKey(unsigned char key, int x, int y)
{
  std::map<unsigned char, camMovement>	associativeKey = graphic->getCam()->getAssociativKey();
  std::map<unsigned char, camMovement>::iterator	it;
  // associativeKey['w'] = CAM_UP;
  // associativeKey['x'] = CAM_DOWN;
  // associativeKey['c'] = CAM_NEAR;
  // associativeKey['v'] = CAM_FAR;

  for (int i = 0; i < LAST ; i++)
    graphic->setKey(i, false);
  it = associativeKey.find(key);
  if (it != associativeKey.end())
    {
      graphic->getCam()->setEvent(it->second, true);
    }
  if (key == 27)
    graphic->setKey(ESC, true);
}

void		catchBasicKeyUp(unsigned char key, int x, int y)
{
  std::map<unsigned char, camMovement>	associativeKey = graphic->getCam()->getAssociativKey();
  std::map<unsigned char, camMovement>::iterator	it;
  // associativeKey['w'] = CAM_UP;
  // associativeKey['x'] = CAM_DOWN;
  // associativeKey['c'] = CAM_NEAR;
  // associativeKey['v'] = CAM_FAR;

  for (int i = 0; i < LAST ; i++)
    graphic->setKey(i, false);
  it = associativeKey.find(key);
  if (it != associativeKey.end())
    {
      graphic->getCam()->setEvent(it->second, false);
    }
}

void	resize(int width, int height)
{
  const float ar = (float) width / (float) height;

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 5000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void updateCamTimer(int value)
{
  graphic->getCam()->updateEvent();

  glutTimerFunc (20, updateCamTimer, value);
}

void	display(void)
{
  glLoadIdentity();

  graphic->updateCam();
  graphic->updateDisplayMap();

  glutPostRedisplay();
}

void	idle(void)
{
  glutPostRedisplay();
}

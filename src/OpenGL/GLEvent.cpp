//
// GLEvent.cpp for GLevent.cpp in /home/debas_e/Project/C++/cpp_nibbler
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 21:14:38 2014 Etienne
// Last update Fri Apr  4 20:19:53 2014 Etienne
//

#include "Graphic.hpp"
#include <stdio.h>

extern Graphics	*graphic;

void		catchSpecialKey(int key, int x, int y)
{
  for (int i = 0; i < LAST ; i++)
    {
      graphic->setKey(i, false);
    }

  switch (key)
    {
    case GLUT_KEY_UP :
      graphic->setKey(DOWN, true);
      break;
    case GLUT_KEY_DOWN :
      graphic->setKey(UP, true);
      break;
    case GLUT_KEY_LEFT :
      graphic->setKey(LEFT, true);
      break;
    case GLUT_KEY_RIGHT :
      graphic->setKey(RIGHT, true);
      break;
    case GLUT_KEY_F1 :
      graphic->changeFirst();
      break;
    case GLUT_KEY_F2 :
      graphic->changeFollowSnake();
      break;
    }
  glutPostRedisplay();
}

void		catchBasicKey(unsigned char key, int x, int y)
{
  for (int i = 0; i < LAST ; i++)
    {
      graphic->setKey(i, false);
    }

  switch (key)
    {
    case 27 :
      graphic->setKey(ESC, true);
      break;
    case 'z' :
      graphic->getCam()->moveEye(CAM_UP, graphic->getHeadPos());
      break;
    case 's' :
      graphic->getCam()->moveEye(CAM_DOWN, graphic->getHeadPos());
      break;
    case 'e' :
      graphic->getCam()->moveEye(CAM_NEAR, graphic->getHeadPos());
      break;
    case 'd' :
      graphic->getCam()->moveEye(CAM_FAR, graphic->getHeadPos());
      break;
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

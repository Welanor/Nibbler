//
// GLEvent.cpp for GLevent.cpp in /home/debas_e/Project/C++/cpp_nibbler
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 21:14:38 2014 Etienne
// Last update Sun Apr  6 10:26:29 2014 Etienne
//

#include "Graphic.hpp"
#include <stdio.h>

extern Graphics	*graphic;

void		catchSpecialKey(int key, int, int)
{
  int		glut[2] = {GLUT_KEY_LEFT, GLUT_KEY_RIGHT};
  Keypos	associative[2] = {ARIGHT, ALEFT};

  for (int i = 0 ; i < 2 ; i++)
    if (glut[i] == key)
      graphic->setKey(associative[i], true);
  if (key == GLUT_KEY_F1)
    graphic->changeFirst();
  else if (key == GLUT_KEY_F2)
    graphic->changeFollowSnake();
  glutPostRedisplay();
}

void		catchBasicKey(unsigned char key, int, int)
{
  std::map<unsigned char, camMovement>		associatedKeyCam = graphic->getCam()->getAssocitedKey();
  std::map<unsigned char, Keypos>		associatedKeySnake = graphic->getAssocitedKey();
  std::map<unsigned char, camMovement>::iterator itCam = associatedKeyCam.find(key);
  std::map<unsigned char, Keypos>::iterator	 itSnake = associatedKeySnake.find(key);

  if (itCam != associatedKeyCam.end())
    {
      graphic->getCam()->setEvent(itCam->second, true);
    }
  if (itSnake != associatedKeySnake.end())
    {
      graphic->setKey(itSnake->second, true);
    }
  if (key == 27)
    graphic->setKey(ESC, true);
}

void		catchBasicKeyUp(unsigned char key, int, int)
{
  std::map<unsigned char, camMovement>	associatedKey = graphic->getCam()->getAssocitedKey();
  std::map<unsigned char, camMovement>::iterator it = associatedKey.find(key);

  if (it != associatedKey.end())
    {
      graphic->getCam()->setEvent(it->second, false);
    }
  if (key == 27)
    graphic->setKey(ESC, true);
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
  graphic->setWinSize(width, height);
}

void updateCamTimer(int value)
{
  graphic->getCam()->updateEvent();

  glutTimerFunc (20, updateCamTimer, value);
}

// void DrawScreen()
// {
//   glColor3f(1,0,0);

//   std::string text;
//   text = "This is a simple text.";
//   glColor3f(0, 1, 0);
//   drawText(text.data(), text.size(), 50, 200);
// }

void	display(void)
{
  glLoadIdentity();

  graphic->updateCam();
  graphic->updateDisplayMap();

  // DrawScreen();

  glutPostRedisplay();
}

void	idle(void)
{
  glutPostRedisplay();
}

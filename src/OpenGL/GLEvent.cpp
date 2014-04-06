//
// GLEvent.cpp for GLevent.cpp in /home/debas_e/Project/C++/cpp_nibbler
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 21:14:38 2014 Etienne
// Last update Sun Apr  6 12:39:00 2014 Etienne
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

void drawText(const char *text, int length, int x, int y){
  glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
  double matrix[16]; // 16 doubles in stack memory
  glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
  glLoadIdentity(); // reset PROJECTION matrix to identity matrix
  glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
  glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
  glLoadIdentity(); // reset it to identity matrix
  glPushMatrix(); // push current state of MODELVIEW matrix to stack
  glLoadIdentity(); // reset it again. (may not be required, but it my convention)
  glRasterPos2i(x, y); // raster position in 2D
  for(int i=0; i<length; i++){
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
  }
  glPopMatrix(); // get MODELVIEW matrix value from stack
  glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
  glLoadMatrixd(matrix); // reset
  glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
}

void DrawScreen()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gluLookAt(0,0,-10, 0,0, 3, 0, 1, 0);

  glColor3f(1,0,0);

  glBegin(GL_LINES);
  glVertex3f(0,0,0);
  glVertex3f(1,0,0);
  glEnd();

  std::string text;
  text = "This is a simple text.";
  glColor3f(0, 1, 0);
  drawText(text.data(), text.size(), 0, 0);

  glutSwapBuffers();
}

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

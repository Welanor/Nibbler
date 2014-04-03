//
// Graphic.cpp for graphic in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 15:44:39 2014 Etienne
// Last update Thu Apr  3 20:47:56 2014 Etienne
//

#include <unistd.h>
#include <cmath>
#include "Graphic.hpp"

Graphics	*graphic = NULL;

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

bool		Graphics::create_window(const std::string &name,
					const int *size_win, const int *size_map)
{
  int		argc;
  GLfloat	WHITE[] = {1, 1, 1};

  argc = 1;
  glutInit(&argc, NULL);

  _size["winx"] = size_win[0];
  _size["winy"] = size_win[1];
  _size["mapx"] = size_map[0];
  _size["mapy"] = size_map[1];

  for (int i = 0 ; i < LAST ; i++)
    _key[i] = false;

  glutInitWindowSize(1920, 1080);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(name.c_str());
  // glutFullScreen();

  glutIdleFunc(idle);
  glutSpecialFunc(catchSpecialKey);
  glutKeyboardFunc(catchBasicKey);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);

  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  create_plane();

  return (true);
}

void		Graphics::handleEvent(bool *key)
{
  for (int i = 0 ; i < LAST ; i++)
    key[i] = false;
  for (int i = 0 ; i < LAST ; i++)
    key[i] = _key[i];
}

void		Graphics::clear()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void		Graphics::draw(int x, int y, int type, int dir)
{
  _pos[0] = x;
  _pos[1] = y;
  _type = type;
  _dir = dir;

  glutMainLoopEvent();
}

void		Graphics::display_score(int score)
{

}

void		Graphics::update()
{
  glFlush();
  glutSwapBuffers();
}

void		Graphics::destroyWindow()
{
}

void		Graphics::setKey(int index, bool value)
{
  _key[index] = value;
}

void		Graphics::updateCam()
{
  float         z;
  float         y;

  z = ((_size["mapx"] / 2.0) / tanf(M_PI * VIEW_FOV / 2.0 / 180.0));
  y = ((z + _size["mapy"] / 2.0) * tanf(FOV_ANGLE * M_PI / 180.0));
  gluLookAt(_size["mapx"] / 2.0, y, z,
            _size["mapx"] / 2.0, 0, -_size["mapy"] / 2.0,
            0,1,0);
}

void		Graphics::updateDisplayMap()
{
  GLfloat GREEN[] = {0, 1, 0};

  glCallList(_displayId);

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GREEN);
  glTranslated(_pos[0] + 0.5f, 0.5f, -(_pos[1] + 0.5f));
  glutSolidCube(1);
  glPopMatrix();
}

void		Graphics::create_plane()
{
  GLfloat RED[] = {1, 0, 0};

  _displayId = glGenLists(1);
  glNewList(_displayId, GL_COMPILE);

  GLfloat lightPosition[] = {_size["mapx"] / 2.0f, 30.0f, -(_size["mapy"] / 2.0f), 1.0f};
  GLfloat lightColor0[] = {1.0f, 1.0f, 0.0f, 1.0f}; //Color (0.5, 0.5, 0.5)
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  const GLfloat high_shininess[] = { 50.0f };
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);

  glBegin(GL_QUADS);
  glNormal3d(0, 1, 0);
  for (float z = 0; z < _size["mapy"] - 1; z++) {
    for (float x = 0; x < _size["mapx"] - 1; x++) {
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
      glVertex3d(x, 0, -z);
      glVertex3d(x, 0, -(z+1));
      glVertex3d(x+1, 0, -(z+1));
      glVertex3d(x+1, 0, -z);

      // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
      // glVertex3d(0, 0, 0);
      // glVertex3d(0, 0, -(_size["mapy"]));
      // glVertex3d(_size["mapx"], 0, -(_size["mapy"]));
      // glVertex3d(_size["mapx"], 0, 0);
    }
  }
  glEnd();
  glEndList();
}

void		Graphics::display_f_score(const std::string&, int, int)
{
}

void		Graphics::display_pause_msg()
{
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    graphic = new Graphics;
    return (graphic);
  }
}

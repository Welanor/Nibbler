//
// Graphic.cpp for graphic in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 15:44:39 2014 Etienne
// Last update Fri Apr  4 15:34:17 2014 Etienne
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

  argc = 1;
  glutInit(&argc, NULL);

  _size["winx"] = size_win[0];
  _size["winy"] = size_win[1];
  _size["mapx"] = size_map[0];
  _size["mapy"] = size_map[1];

  _isFirst = false;
  _followSnake = false;

  for (int i = 0 ; i < LAST ; i++)
    _key[i] = false;

  glutInitWindowSize(1920, 1080);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(name.c_str());

  glutIdleFunc(idle);
  glutSpecialFunc(catchSpecialKey);
  glutKeyboardFunc(catchBasicKey);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);

  init_light();
  init_cam();

  create_plane();

  return (true);
}

void		Graphics::handleEvent(bool *key)
{
  for (int i = 0 ; i < LAST ; i++)
    key[i] = false;
  for (int i = 0 ; i < LAST ; i++)
    key[i] = _key[i];
  glutMainLoopEvent();
}

void		Graphics::clear()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void		Graphics::draw(int x, int y, int type, int dir)
{
  _pos[0] = x;
  _pos[1] = y;
  if (type == HEAD)
    {
      _headpos[0] = x;
      _headpos[1] = y;
    }
  _type = type;
  _dir = dir;
  // if (type == HEAD)
  //   switch (dir)
  //     {
  //     case DOWN :
  // 	std::cout << "UP" << std::endl;
  // 	break;
  //     case UP :
  // 	std::cout << "DOWN" << std::endl;
  // 	break;
  //     case LEFT :
  // 	std::cout << "LEFT" << std::endl;
  // 	break;
  //     case RIGHT :
  // 	std::cout << "RIGHT" << std::endl;
  // 	break;
  //     }
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
  if (_isFirst)
    {
      cam->look(_headpos[0] + 0.5f, 0, -(_headpos[1] + 0.5f));
    }
  else if (_followSnake)
    {
      if (_type == HEAD)
	{
	  std::map<std::string, float> eyePos;

	  eyePos = cam->getEyePos();
	  cam->moveEye(_headpos[0] + 0.5f, eyePos["eyey"], -(_headpos[1] - 10 - 0.5f));
	}
      cam->look(_headpos[0], 0, -(_headpos[1]));
    }
  else
    {
      cam->look();
    }
}

void		Graphics::init_cam()
{
  float         z;
  float         y;
  float		eyex;
  float		eyey;
  float		eyez;
  float		dirx;
  float		diry;
  float		dirz;

  z = ((_size["mapx"] / 2.0) / tanf(M_PI * VIEW_FOV / 2.0 / 180.0));
  y = ((z + _size["mapy"] / 2.0) * tanf(FOV_ANGLE * M_PI / 180.0));

  eyex = _size["mapx"] / 2.0;
  eyey = y;
  eyez = z;
  dirx = _size["mapx"] / 2.0;
  diry = 0;
  dirz = -_size["mapy"] / 2.0;
  cam = new Camera(eyex, eyey, eyez,
		   dirx, diry, dirz,
		   1);
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

void		Graphics::init_light()
{
  GLfloat	WHITE[] = {1, 1, 1};

  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void		Graphics::create_plane()
{
  GLfloat RED[] = {0, 0, 0.5};
  // GLfloat lightPosition[] = {_size["mapx"] / 2.0f, 30.0f, -(_size["mapy"]), 1.0f};
  GLfloat lightColor0[] = {1.0f, 1.0f, 0.0f, 1.0f}; //Color (0.5, 0.5, 0.5)
  GLfloat high_shininess[] = { 50.0f };

  _displayId = glGenLists(1);
  glNewList(_displayId, GL_COMPILE);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);


  glBegin(GL_QUADS);
  glNormal3d(0, 1, 0);
  for (float z = 0; z < _size["mapy"] - 1; z++) {
    for (float x = 0; x < _size["mapx"]; x++) {
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
      glVertex3d(x, 0, -z);
      glVertex3d(x, 0, -(z+1));
      glVertex3d(x+1, 0, -(z+1));
      glVertex3d(x+1, 0, -z);
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

void		Graphics::changeFirst()
{
  _isFirst = !_isFirst;
}

void		Graphics::changeFollowSnake()
{
  if (_followSnake == true)
    cam->reinit_pos();
  _followSnake = !_followSnake;
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

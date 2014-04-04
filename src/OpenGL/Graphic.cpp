//
// Graphic.cpp for graphic in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 15:44:39 2014 Etienne
// Last update Fri Apr  4 23:38:42 2014 Etienne
//

#include <unistd.h>
#include <cmath>
#include "Graphic.hpp"

Graphics	*graphic = NULL;

Graphics::Graphics()
{
  _isFirst = false;
  _followSnake = false;

  for (int i = 0 ; i < LAST ; i++)
    _key[i] = false;
  for (int i = 0 ; i < 2 ; i++)
    {
      _pos[i] = 0;
      _headpos[i] = 0;
    }
  for (int i = 0 ; i < 3 ; i++)
    {
      _eye[i] = 0;
      _vecdir[i] = 0;
    }
}

Graphics::~Graphics()
{
  // delete cam;
}

void		Graphics::initColor()
{
  _color_entities[MONSTER] = new colorEntities(COLOR_FLOAT(15), COLOR_FLOAT(15), COLOR_FLOAT(13));
  _color_entities[BUDDY] = new colorEntities(COLOR_FLOAT(20), COLOR_FLOAT(130), COLOR_FLOAT(12));
  _color_entities[TAIL] = new colorEntities(COLOR_FLOAT(20), COLOR_FLOAT(130), COLOR_FLOAT(12));
  _color_entities[HEAD] = new colorEntities(COLOR_FLOAT(44), COLOR_FLOAT(94), COLOR_FLOAT(41));
  _color_entities[WALL] = new colorEntities(COLOR_FLOAT(66), COLOR_FLOAT(62), COLOR_FLOAT(62));
  _color_entities[BANANA] = new colorEntities(COLOR_FLOAT(198), COLOR_FLOAT(201), COLOR_FLOAT(22));
  _color_entities[STRAWBERRY] = new colorEntities(235, 7, 7);

  _color_entities[APPLE] = new colorEntities(COLOR_FLOAT(255), COLOR_FLOAT(255), COLOR_FLOAT(255));
  _color_entities[PEAR] = new colorEntities(COLOR_FLOAT(255), COLOR_FLOAT(255), COLOR_FLOAT(255));
  _color_entities[KIWI] = new colorEntities(COLOR_FLOAT(255), COLOR_FLOAT(255), COLOR_FLOAT(255));
  _color_entities[BOOSTER] = new colorEntities(COLOR_FLOAT(255), COLOR_FLOAT(255), COLOR_FLOAT(255));
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

  glutInitWindowSize(1920, 1080);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(name.c_str());

  glutIdleFunc(idle);
  glutSpecialFunc(catchSpecialKey);
  glutKeyboardFunc(catchBasicKey);
  glutKeyboardUpFunc(catchBasicKeyUp);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutTimerFunc(20, updateCamTimer, 0);

  initColor();
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
  std::map<std::string, float> eyePos;

  if (_isFirst)
    {
      cam->moveDir(_headpos[0] + 0.5f, 0, -(_headpos[1] + 0.5f));
      cam->look();
    }
  else if (_followSnake)
    {
      if (_type == HEAD)
	{
	  eyePos = cam->getEyePos();
	  cam->moveEye(_headpos[0] + 0.5f, eyePos["eyey"], -(_headpos[1] - 10 - 0.5f));
	}
      cam->moveDir(_headpos[0], 0, -(_headpos[1]));
      cam->look();
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
  GLfloat *color = _color_entities[static_cast<Entities>(_type)]->rgb;

  glCallList(_displayId);

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glTranslated(_pos[0] + 0.5f, 0.5f, -(_pos[1] + 0.5f));
  glutSolidCube(1);
  glPopMatrix();
}

void		Graphics::init_light()
{
  GLfloat	WHITE[] = {1, 1, 1};

  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
  glMaterialf(GL_FRONT, GL_SHININESS, 40);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
}

void		Graphics::create_plane()
{
  GLfloat FLOOR[] = {COLOR_FLOAT(13), COLOR_FLOAT(123), COLOR_FLOAT(135)};
  GLfloat lightPosition0[] = {_size["mapx"] / 2.0f, 30.0f, -(_size["mapy"] / 2.0f), 1.0f};
  GLfloat lightColor0[] = {COLOR_FLOAT(227), COLOR_FLOAT(223), COLOR_FLOAT(102), 0.0f};
  GLfloat high_shininess[] = { 50.0f };

  _displayId = glGenLists(1);
  glNewList(_displayId, GL_COMPILE);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

  glBegin(GL_QUADS);
  glNormal3d(0, 1, 0);
  for (float z = 0; z < _size["mapy"]; z++) {
    for (float x = 0; x < _size["mapx"]; x++) {
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, FLOOR);
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
  std::map<std::string, float> eyePos;

  if (_isFirst == true)
    cam->reinit_pos();
  else
    {
      eyePos = cam->getEyePos();
      cam->moveEye(_headpos[0] + 0.5f, eyePos["eyey"], -(_headpos[1] - 10 - 0.5f));
    }
  _isFirst = !_isFirst;
}

void		Graphics::changeFollowSnake()
{
  if (_followSnake == true)
    cam->reinit_pos();
  _followSnake = !_followSnake;
}

Camera		*Graphics::getCam()
{
  return cam;
}

int		*Graphics::getHeadPos()
{
  return _headpos;
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

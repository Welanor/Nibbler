//
// Graphic.cpp for graphic in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Mon Mar 31 15:44:39 2014 Etienne
// Last update Mon Mar 31 20:18:56 2014 Etienne
//

#include "Graphic.hpp"

Graphics	*instance = NULL;

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

  _size_win[0] = size_win[0];
  _size_win[1] = size_win[1];
  _size_map[0] = size_map[0];
  _size_map[1] = size_map[1];

  glutInitWindowSize(_size_win[0], _size_win[1]);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutCreateWindow(name.c_str());
  return (true);
}

void		Graphics::handleEvent(bool *key)
{
}

void		Graphics::clear()
{
}

void		Graphics::draw(int x, int y, int type, int dir)
{
  glutMainLoopEvent();
}

void		Graphics::display_score(int score)
{
}

void		Graphics::update()
{
}

void		Graphics::destroyWindow()
{
}

void		Graphics::setKey()
{
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    return (new Graphics);
  }
}

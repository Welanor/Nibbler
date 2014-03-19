#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _size_winx(WINX), _size_winy(WINY), _lib()
{
  std::stringstream ss("");
  std::string libname("");
  IInput *(*createInput)();
  IGraphics *(*createGraphics)();

  if (ac != 4)
    throw(Exception("Usage: ./nibbler size_x size_y lib_nibbler_XXX.so"));
  ss.str(av[1]);
  if (!(ss >> _x) || _x <= 0)
    throw(Exception("Size X invalid"));
  ss.clear();
  ss.str(av[2]);
  if (!(ss >> _y) || _y <= 0)
    throw(Exception("Size Y invalid"));
  _lib.open(av[3], RTLD_LAZY);

  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));
  createInput = reinterpret_cast<IInput *(*)()>(_lib.getSym("init_input"));

  if (createInput == NULL || createGraphics == NULL)
    throw(Exception(""));

  _window = (createGraphics)();
  _input = (createInput)();
}

Game::~Game()
{
  _lib.close();
  _window->destroyWindow();
  delete _window;
  delete _input;
}

void	Game::start()
{
  unsigned int frameRate = 1000 / FPS;
  unsigned int begin = 0, end = 0, time= 0;

  while (!_input->isDone())
    {
      begin = _input->getTime();

      /* Evenement */
      _window->clear();

      _input->getEvent();

      _window->draw(_map);

      end = _input->getTime();
      time = end - begin;
      if (time < frameRate)
	_input->sleep(frameRate - time);
    }
}

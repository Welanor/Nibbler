#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _size_winx(WINX),
				_size_winy(WINY), _lib(), _snake()
{
  IInput *(*createInput)();
  IGraphics *(*createGraphics)();

  parse_arg(ac, av);

  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));
  createInput = reinterpret_cast<IInput *(*)()>(_lib.getSym("init_input"));

  if (createInput == NULL || createGraphics == NULL)
    throw(Exception(""));

  t_snake tmp = {_x / 2, _y - 1, NORTH};

  _snake.push_back(tmp);
  _snake.push_back(tmp);
  _snake.push_back(tmp);
  _snake.push_back(tmp);

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

void Game::parse_arg(const int ac, char **av)
{
  std::stringstream ss("");
  std::string libname("");

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
}

bool	Game::check_collision() const
{
  if (_snake.front().x >= _x || _snake.front().y >= _y || _snake.front().y < 0 || _snake.front().x < 0)
    return (true);
  return (false);
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

      _window->draw(_snake);

      end = _input->getTime();
      time = end - begin;
      if (time < frameRate)
	_input->sleep(frameRate - time);
    }
}

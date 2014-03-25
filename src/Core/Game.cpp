#include <unistd.h>
#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _lib(), _snake()
{
  IGraphics *(*createGraphics)();

  parse_arg(ac, av);

  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));

  if (createGraphics == NULL)
    throw(Exception(""));

  t_snake tmp = {_x / 2, _y - 1, NORTH};
  t_snake tmp1 = {_x / 2 + 1, _y - 1, NORTH};
  t_snake tmp2 = {_x / 2 + 1, _y - 2, NORTH};

  _snake.push_back(tmp);
  _snake.push_back(tmp1);
  _snake.push_back(tmp2);
  _window = (createGraphics)();
}

Game::~Game()
{
  _lib.close();
  _window->destroyWindow();
  delete _window;
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
  if (_snake.front().x >= _x || _snake.front().y >= _y
      || _snake.front().y < 0 || _snake.front().x < 0)
    return (true);
  return (false);
}

void	Game::move_snake(bool *key)
{
  lit	beg = _snake.begin();
  lit	tmp;
  lit	end;

  for (end = (--_snake.end()); end != beg; --end)
    {
      tmp = end;
      --tmp;
      end->x = tmp->x;
      end->y = tmp->y;
    }
  beg->x += (key[RIGHT]) ? 1 : (key[LEFT]) ? -1 : 0;
  beg->y += (key[DOWN]) ? 1 : (key[UP]) ? -1 : 0;
}

void	Game::display()
{
  lit	beg = _snake.begin();
  lit	end = _snake.end();
  lit	tmp;

  for (;beg != end; ++beg)
    {
      tmp = beg;
      ++tmp;
      _window->draw(beg->x, beg->y, (beg == _snake.begin()) ? 0 :
		    (tmp == end) ? 2 : 1);
    }
}

void	Game::start()
{
  double frameRate = 1000 / FPS;
  time_t begin = 0;
  double time= 0;
  bool	 key[LAST];

  for (int i = 0; i < LAST; i++)
    key[i] = false;
  _window->create_window("Nibbler", WINX, WINY);
  while (!_window->isDone())
    {
      begin = clock();

      /* Evenement */
      _window->clear();

      _window->handleEvent(key);
      move_snake(key);
      display();
      time = (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000);
      if (time < frameRate)
	usleep(frameRate - time);
    }
}

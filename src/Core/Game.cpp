#include <unistd.h>
#include <stdlib.h>
#include <iterator>
#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _lib(), _snake()
{
  IGraphics *(*createGraphics)();

  parse_arg(ac, av);

  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));

  if (createGraphics == NULL)
    throw(Exception(""));

  t_snake tmp = {_x / 2, _y - 1, LEFT};
  t_snake tmp1 = {_x / 2 + 1, _y - 1, LEFT};
  t_snake tmp2 = {_x / 2 + 1, _y - 2, LEFT};

  _snake.push_back(tmp);
  _snake.push_back(tmp1);
  _snake.push_back(tmp2);
  _window = (createGraphics)();
}

Game::~Game()
{
  _window->destroyWindow();
  delete _window;
  _lib.close();
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

void	Game::add_entities()
{
  t_ent	ent;
  int	nb;

  if ((nb = rand()) % PROB != 0)
    return ;
  ent.x = nb % _x;
  ent.y = nb % _y;
  ent.type = APPLE;
  _ent.push_back(ent);
}

bool		Game::check_collision()
{
  s_snake	head;
  c_lit		lbeg;
  c_lit		lend;
  vit		vbeg;
  vit		vend;
  int		i;

  head = _snake.front();
  if (head.x >= _x || head.y >= _y || head.y < 0 || head.x < 0)
    return (true);
  for (i = 0, lbeg = _snake.begin(), lend = _snake.end(); lbeg != lend && i < 2; ++i, ++lbeg);
  for (; lbeg != lend; ++lbeg)
    if (head.x == lbeg->x && head.y == lbeg->y)
      return (true);
  for (vbeg = _ent.begin(), vend = _ent.end(); vbeg != vend; vbeg++)
    {
      if (head.x == vbeg->x && head.y == vbeg->y)
	{
	  if (vbeg->type == APPLE)
	    {
	      _snake.insert(_snake.begin(), *(++_snake.begin()));
	      _ent.erase(vbeg);
	      if ((vend = _ent.end()) == vbeg)
		break ;
	    }
	}
    }
  return (false);
}

void	Game::move_snake(bool *key)
{
  lit	beg = _snake.begin();
  lit	end = _snake.end();
  t_snake tmp;
  t_snake old;

  key[DOWN] = (key[DOWN] && beg->dir == UP) ? false : key[DOWN];
  key[UP] = (key[UP] && beg->dir == DOWN) ? false : key[UP];
  key[LEFT] = (key[LEFT] && beg->dir == RIGHT) ? false : key[LEFT];
  key[RIGHT] = (key[RIGHT] && beg->dir == LEFT) ? false : key[RIGHT];
  if (!key[DOWN] && !key[UP] && !key[LEFT] && !key[RIGHT])
    key[beg->dir] = true;
  beg = _snake.begin();
  old = *beg;
  for (int i = 0; i < LAST; i++)
    if (key[i])
      beg->dir = static_cast<Keypos>(i);
  beg->x += (key[RIGHT]) ? 1 : (key[LEFT]) ? -1 : 0;
  beg->y += (key[DOWN]) ? 1 : (key[UP]) ? -1 : 0;
  ++beg;
  while (beg != end)
    {
      tmp = *beg;
      *beg = old;
      old = tmp;
      ++beg;
      if (beg == end || (beg->x == old.x && beg->y == old.y && beg->dir == old.dir))
	break;
    }
}

void	Game::display()
{
  lit	beg = _snake.begin();
  lit	end = _snake.end();
  lit	tmp;
  vit	ebeg = _ent.begin();
  vit	eend = _ent.end();

  for (;beg != end; ++beg)
    {
      tmp = beg;
      ++tmp;
      _window->draw(beg->x, beg->y, (beg == _snake.begin()) ? HEAD :
		    (tmp == end) ? TAIL : BUDDY);
    }
  for (;ebeg != eend; ebeg++)
    _window->draw(ebeg->x, ebeg->y, ebeg->type);
}

void	Game::start()
{
  double frameRate = 1000 / FPS;
  time_t begin = 0;
  double time= 0;
  bool	 key[LAST];
  bool	end = false;

  for (int i = 0; i < LAST; i++)
    key[i] = false;
  _window->create_window("Nibbler", WINX, WINY);
  while (!end && !key[ESC])
    {
      begin = clock();
      /* Evenement */
      _window->clear();
      _window->handleEvent(key);
      move_snake(key);
      end = check_collision();
      add_entities();
      display();
      time = (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000);
      if (time < frameRate)
	usleep(frameRate - time);
    }
}

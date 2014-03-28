#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _lib(), _snake()
{
  int	seed;

  IGraphics *(*createGraphics)();
  parse_arg(ac, av);
  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));
  if (createGraphics == NULL)
    throw(Exception(""));

  __asm__ volatile ("rdtsc" : "=A" (seed));
  std::srand(seed);
  t_snake tmp = {_x / 2, _y / 2, LEFT};
  t_snake tmp1 = {_x / 2, _y / 2 - 1, LEFT};
  t_snake tmp2 = {_x / 2, _y / 2 - 2, LEFT};
  t_snake tmp3 = {_x / 2, _y / 2 - 3, LEFT};

  _snake.push_back(tmp);
  _snake.push_back(tmp1);
  _snake.push_back(tmp2);
  _snake.push_back(tmp3);
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

void		Game::add_entities()
{
  int		probs[] = {PROB_ONE, PROB_TWO, PROB_THREE, PROB_FOUR, PROB_FIVE};
  Entities	types[] = {APPLE, GOLD_APPLE, BREAD, CHICKEN, PORK};
  int		idx = 0;
  int		nb_ent = _ent.size();
  c_vit		beg;
  c_vit		end;
  t_ent		ent;
  unsigned int	nb;

  nb = std::rand();
  if (nb_ent == MAX_ENT || (nb_ent != 0 && nb % probs[nb_ent] != 0))
    return ;
  for (unsigned int i = 0; i < sizeof(probs) / sizeof(int); ++i)
    if (nb % probs[i] == 0)
      idx = i;
  ent.x = std::rand() % _x;
  ent.y = std::rand() % _y;
  ent.type = types[idx];
  for (beg = _ent.begin(), end = _ent.end(); beg != end; ++beg)
    if (beg->x == ent.x && beg->y == ent.y)
      return ;
  _ent.push_back(ent);
}

bool		Game::spe_collision(vit &vbeg, vit &vend)
{
  if (vbeg->type >= APPLE && vbeg->type <= PORK)
    {
      for (unsigned int tmp = vbeg->type; tmp >= APPLE; --tmp)
	_snake.push_back(*_snake.begin());
      _ent.erase(vbeg);
      if ((vend = _ent.end()) == vbeg)
	return (false);
    }
  return (true);
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
	if (!spe_collision(vbeg, vend))
	  break ;
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
  double frameRate = (1.0 / static_cast<double>(FPS)) * 1000.0;
  Time begin, end;
  bool	 key[LAST];
  bool	done = false;

  for (int i = 0; i < LAST; i++)
    key[i] = false;
  _window->create_window("Nibbler", WINX, WINY);
  while (!done && !key[ESC])
    {
      begin.startTime();
      /* Evenement */
      _window->clear();
      _window->handleEvent(key);
      move_snake(key);
      done = check_collision();
      add_entities();
      display();
      end.startTime();
      end -= begin;
      if (end < frameRate)
      	usleep((frameRate - end.getTime()) * 1000);
    }
}

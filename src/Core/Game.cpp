#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <cmath>
#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _lib(), _snake(), _score(0)
{
  int		seed;
  IGraphics	*(*createGraphics)();

  _fps = FPS;
  parse_arg(ac, av);
  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));
  if (createGraphics == NULL)
    throw(Exception(""));

  __asm__ volatile ("rdtsc" : "=A" (seed));
  std::srand(seed);

  for (int i = 0; i < 4; ++i)
    {
      t_snake tmp = {_x / 2, _y / 2 - i, LEFT};
      _snake.push_back(tmp);
    }
  for (int i = APPLE; i <= KIWI; ++i)
    {
      t_ent tmp = {0, 0, static_cast<Entities>(i), (i - APPLE) * 100 + 1, NOTIME};
      _entlist.push_back(tmp);
    }
  t_ent tmp = {0, 0, BOOSTER, 10, 0};
  _entlist.push_back(tmp);
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

void		Game::remove_entities()
{
  vit		beg = _ent.begin();
  vit		end = _ent.end();

  for (; beg != end; ++beg)
    {
      if (beg->time > NOTIME && (beg->time + 1) >= MAXTIME)
	_ent.erase(beg);
      else if (beg->time != NOTIME)
	++(beg->time);
    }
}

void		Game::add_entities()
{
  int		nb_ent = _ent.size();
  c_vit		beg = _entlist.begin();
  c_vit		end = _entlist.end();
  t_ent		ent = {0, 0, ELAST, 0, NOTIME};
  unsigned int	nb;

  if (nb_ent >= MAXENT)
    return ;
  nb = std::rand();
  for (; beg != end; ++beg)
    {
      if (nb % beg->prob == 0)
	ent = *beg;
    }
  if (ent.type == ELAST)
    return ;
  ent.x = std::rand() % _x;
  ent.y = std::rand() % _y;
  for (beg = _ent.begin(), end = _ent.end(); beg != end; ++beg)
    if (beg->type == ent.type || (beg->x == ent.x && beg->y == ent.y))
      return ;
  _ent.push_back(ent);
}

bool		Game::spe_collision(vit &vbeg, vit &vend)
{
  bool		ret = true;

  if (vbeg->type >= APPLE && vbeg->type <= KIWI)
    {
      for (unsigned int tmp = vbeg->type; tmp >= APPLE; --tmp)
	_snake.push_back(*_snake.begin());
      if ((vend = _ent.end()) == vbeg)
	ret = false;
      _score += pow(2, vbeg->type);
    }
  else if (vbeg->type == BOOSTER)
    _fps = (rand() % 2) == 0 ? (FPS / 4) : (FPS * 2);
  _ent.erase(vbeg);
  return (ret);
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
		    (tmp == end) ? TAIL : BUDDY, beg->dir);
    }
  for (;ebeg != eend; ebeg++)
    _window->draw(ebeg->x, ebeg->y, ebeg->type, 0);
  _window->display_score(_score);
  _window->update();
}

void	Game::handle_fps(int &idx)
{
  if (_fps != FPS && idx == -1)
    idx = 0;
  if (idx >= BOOSTTIME)
    {
      _fps = FPS;
      idx = -1;
    }
  else
    ++idx;
}

void	Game::start()
{
  double frameRate;
  Time	begin, end;
  bool	key[LAST] = { false };
  bool	done = false;
  int	size_win[] = { WINX, WINY };
  int	size_map[] = { _x, _y };
  int	idx = -1;

  _window->create_window("Nibbler", size_win, size_map);
  while (!done && !key[ESC])
    {
      handle_fps(idx);
      frameRate = (1.0 / static_cast<double>(_fps)) * 1000.0;
      begin.startTime();
      /* Evenement */
      _window->clear();
      _window->handleEvent(key);
      move_snake(key);
      done = check_collision();
      remove_entities();
      add_entities();
      display();
      end.startTime();
      end -= begin;
      if (end < frameRate)
      	usleep((frameRate - end.getTime()) * 1000);
    }
}

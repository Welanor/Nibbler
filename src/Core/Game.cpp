#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _lib(), _snake()
{
  int		seed;
  IGraphics	*(*createGraphics)();

  _player.score = 0;
  _player.name = "You";
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
  for (int i = 0; i < 10; ++i)
    {
      t_ent tmp = {(std::rand() % _x), (std::rand() % _y), WALL, 0, NOTIME};
      _ent.push_back(tmp);
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
  int		notime = NOTIME, maxtime = MAXTIME;

  for (; beg != end; ++beg)
    {
      if (beg->time > notime && (beg->time + 1) >= maxtime)
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

int		Game::spe_collision(vit &vbeg, vit &vend)
{
  bool		ret = 1;

  if (vbeg->type >= APPLE && vbeg->type <= KIWI)
    {
      for (unsigned int tmp = vbeg->type; tmp >= APPLE; --tmp)
	_snake.push_back(*_snake.begin());
      if ((vend = _ent.end()) == vbeg)
	ret = 0;
      _player.score += pow(2, vbeg->type);
    }
  else if (vbeg->type == BOOSTER)
    _fps = (rand() % 2) == 0 ? (FPS / 4) : (FPS * 2);
  else if (vbeg->type == WALL)
    return (2);
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
	{
	  int ret = spe_collision(vbeg, vend);
	  if (!ret)
	    break;
	  else if (ret == 2)
	    return (true);
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
    }
}

bool	score_compare(t_player pl1, t_player pl2)
{
  return (pl1.score >= pl2.score);
}

void	Game::print_scores()
{
  std::fstream	file;
  std::string	line;
  std::string	name;
  std::string	filename(SCOREPATH);
  std::list<t_player> pl;
  std::list<t_player>::iterator beg;
  std::list<t_player>::iterator end;
  unsigned int	i;

  file.open (filename.c_str(), std::ios::in);
  if (file.is_open())
    {
      for (i = 0; std::getline(file, line) && i < 6; ++i)
	{
	  t_player player;
	  std::stringstream iss(line);

	  iss >> player.name >> player.score;
	  pl.push_back(player);
	  _window->display_f_score(player.name, player.score, i);
	}
      _window->display_f_score(_player.name, _player.score, i + 1);
      pl.push_back(_player);
      file.close();
    }
  file.open (filename.c_str(), std::fstream::out | std::fstream::trunc);
  if (file.is_open())
    {
      pl.sort(&score_compare);
      for (i = 0, beg = pl.begin(), end = pl.end(); beg != end && i < 5; ++beg, ++i)
	file << beg->name << " " << beg->score << std::endl;
      file.close();
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
  _window->display_score(_player.score);
  _window->update();
}

void	Game::handle_fps(int &idx)
{
  if (_fps != FPS && idx == -1)
    idx = 0;
  if (idx >= static_cast<int>(BOOSTTIME))
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
      for (int i = 0; i == 0 || key[PAUSE]; i = 1)
	{
	  _window->handleEvent(key);
	  if (key[PAUSE] && i == 0)
	    _window->display_pause_msg();
	}
      _window->clear();
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
  _window->clear();
  print_scores();
  _window->update();
  getchar();
}

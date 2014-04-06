#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "Game.hpp"

Game::Game(int ac, char **av) : _x(0), _y(0), _lib(), _current_lib(0), _snake()
{
  IGraphics	*(*createGraphics)();
  Display	*dis;

  _player.name = "Unknown";
  _fps = FPS;
  parse_arg(ac, av);
  createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"));
  if ((dis = XOpenDisplay(NULL)) == NULL || createGraphics == NULL)
    throw(Exception("Connection to server X could not be established"));
  XCloseDisplay(dis);
  std::srand(time(NULL));
  init_entities();
  _window = (createGraphics)();
}

Game::~Game()
{
  if (_window != NULL)
    {
      _window->destroyWindow();
      delete _window;
      _lib.close();
    }
}

void	Game::parse_arg(const int ac, char **av)
{
  std::stringstream ss("");
  std::string libname("");

  if (ac < 4)
    throw(Exception("Usage: ./nibbler size_x size_y lib_nibbler_XXX.so [--name NAME] [other lib]"));
  ss.str(av[1]);
  if (!(ss >> _x) || _x <= 0)
    throw(Exception("Size X invalid"));
  ss.clear();
  ss.str(av[2]);
  if (!(ss >> _y) || _y <= 0)
    throw(Exception("Size Y invalid"));
  for (int i = 3;i < ac;i++)
    {
      if (std::string(av[i]) == "--name")
	{
	  if (i + 1 < ac)
	    _player.name = av[i + 1];
	  else
	    throw(Exception("Usage: ./nibbler size_x size_y lib_nibbler_XXX.so [--name NAME] [other lib]"));
	  ++i;
	}
      else
	_all_lib.push_back(av[i]);
    }
  _lib.open(_all_lib.front(), RTLD_LAZY);
}

void	Game::init_entities()
{
  _snake.clear();
  _ent.clear();
  _entlist.clear();
  _player.score = 0;
  _fps = FPS;
  for (int i = 0; i < 4; ++i)
    {
      t_snake tmp = {_x / 2, _y / 2 - i, LEFT};
      _snake.push_back(tmp);
    }
  for (int i = APPLE; i <= KIWI; ++i)
    {
      t_ent tmp = {0, 0, static_cast<Entities>(i), (i - APPLE) * 100 + 1,
		   NOTIME, pow(2, i)};
      _entlist.push_back(tmp);
    }
  for (int i = 0; i < 10; ++i)
    {
      t_ent tmp = {(std::rand() % _x), (std::rand() % _y), WALL, 0, NOTIME, 0};
      _ent.push_back(tmp);
    }
  {
    t_ent tmp = {0, 0, BOOSTER, 10, 0, 0};
    _entlist.push_back(tmp);
  }
  {
    t_ent tmp = {0, 0, MONSTER, 100, NOTIME, 0};
    _entlist.push_back(tmp);
  }
  {
    t_ent tmp = {0, 0, WARP, 300, 0, 0};
    _entlist.push_back(tmp);
  }
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

bool	Game::monster_colision(vit &beg)
{
  for (vit tmp = _ent.begin(); tmp != _ent.end(); ++tmp)
    {
      if (tmp->x == beg->x && tmp->y == beg->y &&
	  (tmp->type == WALL || (tmp->type >= HEAD && tmp->type <= TAIL) ||
	   (tmp->type >= APPLE && tmp->type <= KIWI)))
	{
	  if (tmp->type >= APPLE && tmp->type <= KIWI)
	    {
	      (*beg).score += tmp->score;
	      _ent.erase(tmp);
	    }
	  else if (tmp->type == WALL)
	    {
	      beg = _ent.erase(beg);
	      return (true);
	    }
	  return (false);
	}
    }
  return (false);
}

void	Game::move_entities()
{
  vit  	beg = _ent.begin();
  vit	tmp;
  c_lit	lbeg;
  c_lit	lend;
  t_ent	*ent = NULL;
  int	dist[2];

  for (;beg != _ent.end(); ++beg)
    {
      if (beg->type != MONSTER)
	continue ;
      for (tmp = _ent.begin(); tmp != _ent.end(); ++tmp)
	{
	  if (tmp->type >= APPLE && tmp->type <= KIWI)
	    {
	      if (ent == NULL)
		ent = &(*tmp);
	      else
		{
		  dist[0] = ABS(beg->x - tmp->x) + ABS(beg->y - tmp->y);
		  dist[1] = ABS(beg->x - ent->x) + ABS(beg->y - ent->y);
		  if (dist[0] < dist[1])
		    ent = &(*tmp);
		}
	    }
	}
      if (ent)
	{
	  dist[0] = ABS(beg->x - ent->x);
	  dist[1] = ABS(beg->y - ent->y);
	  if (dist[0] > dist[1])
	    beg->x += (beg->x > ent->x) ? -1 : 1;
	  else
	    beg->y += (beg->y > ent->y) ? -1 : 1;
	}
      if (monster_colision(beg) || beg == _ent.end())
	{
	  beg = _ent.begin();
	  break ;
	}
      for (lbeg = _snake.begin(), lend = _snake.end(); lbeg != lend; ++lbeg)
	{
	  if (lbeg->x == beg->x && lbeg->y == beg->y)
	    {
	      beg = _ent.erase(beg);
	      break;
	    }
	}
      if (beg == _ent.end())
	break ;
    }
}

void		Game::add_entities()
{
  int		nb_ent = _ent.size();
  c_vit		beg = _entlist.begin();
  c_vit		end = _entlist.end();
  t_ent		ent = {0, 0, ELAST, 0, NOTIME, 0};
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
  if (ent.type == WARP)
    {
      ent.x = std::rand() % _x;
      ent.y = std::rand() % _y;
      _ent.push_back(ent);
    }
}

int		Game::spe_collision(vit &vbeg, vit &vend)
{
  bool		ret = 1;
  vit		tbeg;

  if (vbeg->type >= APPLE && vbeg->type <= KIWI)
    {
      for (unsigned int tmp = vbeg->type; tmp >= APPLE; --tmp)
	_snake.push_back(*_snake.begin());
      if ((vend = _ent.end()) == vbeg)
	ret = 0;
      _player.score += vbeg->score;
    }
  switch (static_cast<int>(vbeg->type))
    {
    case (BOOSTER):
      _fps = (rand() % 2) == 0 ? (FPS / 4) : (FPS * 2);
      break;
    case (WALL):
      return (2);
      break ;
    case (MONSTER):
      _player.score += vbeg->score;
      for (int i = 0; i < std::sqrt(vbeg->score); i++)
	_snake.push_back(*_snake.begin());
      break;
    case (WARP):
      for (tbeg = _ent.begin(); tbeg != vend; tbeg++)
	{
	  if (tbeg == vbeg)
	    continue ;
	  if (tbeg->type == WARP)
	    {
	      _snake.begin()->x = tbeg->x;
	      _snake.begin()->y = tbeg->y;
	      break ;
	    }
	}
      break;
    }
  if (vbeg->type != WARP)
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
  for (i = 0, lbeg = _snake.begin(), lend = _snake.end();
       lbeg != lend && i < 2; ++i, ++lbeg);
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
  if (!key[DOWN] && !key[UP] && !key[LEFT] &&
      !key[RIGHT] && !key[ARIGHT] && !key[ALEFT])
    key[beg->dir] = true;
  old = *beg;
  for (int i = 0; i < ESC; i++)
    if (key[i])
      {
	if (i == ALEFT)
	  beg->dir = static_cast<Keypos>((4 + beg->dir - 1) % 4);
	else if (i == ARIGHT)
	  beg->dir = static_cast<Keypos>((beg->dir + 1) % 4);
	else
	  beg->dir = static_cast<Keypos>(i);
	key[beg->dir] = true;
      }
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

void	Game::encrypt_line(std::string &line) const
{
  for (std::string::iterator it = line.begin();it != line.end();it++)
    {
      (*it) ^= 0x20;
      (*it) ^= 0x50;
      (*it) ^= 0x02;
    }
}

void	Game::decrypt_line(std::string &line) const
{
  for (std::string::iterator it = line.begin();it != line.end();it++)
    {
      (*it) ^= 0x02;
      (*it) ^= 0x50;
      (*it) ^= 0x20;
    }
}

void	Game::print_scores() const
{
  std::fstream	file;
  std::string	line;
  std::string	name;
  std::string	filename(SCOREPATH);
  std::list<t_player> pl;
  std::list<t_player>::iterator beg;
  std::list<t_player>::iterator end;
  unsigned int	i = 0;

  file.open (filename.c_str(), std::ios::in);
  if (file.is_open())
    {
      for (; std::getline(file, line) && i < 6; ++i)
	{
	  decrypt_line(line);
	  t_player player;
	  std::stringstream iss(line);

	  iss >> player.name >> player.score;
	  pl.push_back(player);
	  _window->display_f_score(player.name, player.score, i);
	}
      file.close();
    }
  _window->display_f_score(_player.name, _player.score, i + 1);
  pl.push_back(_player);
  file.open (filename.c_str(), std::fstream::out | std::fstream::trunc);
  if (file.is_open())
    {
      std::stringstream iss("");
      pl.sort(&score_compare);
      for (i = 0, beg = pl.begin(), end = pl.end(); beg != end && i < 5; ++beg, ++i)
	iss << beg->name << " " << beg->score << std::endl;
      line = iss.str();
      encrypt_line(line);
      file << line;
      file.close();
    }
}

void	Game::display() const
{
  c_lit	beg = _snake.begin();
  c_lit	end = _snake.end();
  c_lit	tmp;
  c_vit	ebeg = _ent.begin();
  c_vit	eend = _ent.end();

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
  if (idx == -1)
    return ;
  if (idx >= static_cast<int>(BOOSTTIME))
    {
      _fps = FPS;
      idx = -1;
    }
  else
    ++idx;
}

void	Game::end_score(bool *key, bool &done) const
{
  for (int i = 0; i < LAST; ++i)
    key[i] = false;
  _window->clear();
  print_scores();
  _window->update();
  while (!key[ESC] && !key[NEWGAME])
    {
      _window->handleEvent(key);
      usleep(1000);
    }
  done = !key[NEWGAME];
}

void	Game::switch_lib()
{
  int		size_win[] = { WINX, WINY };
  int		size_map[] = { _x, _y };
  IGraphics	*(*createGraphics)();

  _window->destroyWindow();
  delete _window;
  _window = NULL;
  _lib.close();
  _current_lib = (_current_lib + 1) % _all_lib.size();
  _lib.open(_all_lib[_current_lib], RTLD_LAZY);
  if ((createGraphics = reinterpret_cast<IGraphics *(*)()>(_lib.getSym("init_graphics"))) == NULL)
    throw(Exception("Error unknow symbol"));
  _window = (createGraphics)();
  if (_window == NULL || _window->create_window("Nibbler", size_win, size_map) == false)
    throw (Exception("Init Windows Failed"));
}


void	Game::start()
{
  double frameRate;
  Timer	begin, end;
  bool	key[LAST] = { false };
  bool	done = false;
  int	size_win[] = { WINX, WINY };
  int	size_map[] = { _x, _y };
  int	idx = -1;

  if (_window->create_window("Nibbler", size_win, size_map) == false)
    throw (Exception("Init Windows Failed"));
  while (!done && !key[ESC])
    {
      handle_fps(idx);
      frameRate = (1.0 / static_cast<double>(_fps)) * 1000.0;
      begin.startTimer();
      /* Evenement */
      for (int i = 0; i == 0 || key[PAUSE]; i = 1)
	{
	  _window->handleEvent(key);
	  if (key[PAUSE] && i == 0)
	    _window->display_pause_msg();
	  usleep(1000);
	}
      if (key[SWITCHLIB])
	switch_lib();
      _window->clear();
      move_snake(key);
      done = check_collision();
      remove_entities();
      move_entities();
      add_entities();
      display();
      end.startTimer();
      end -= begin;
      if (end < frameRate)
      	usleep((frameRate - end.getTimer()) * 1000);
      if (done || key[ESC])
	{
	  end_score(key, done);
	  if (!done && !key[ESC])
	    init_entities();
	}
    }
}

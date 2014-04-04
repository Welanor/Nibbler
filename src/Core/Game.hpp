#ifndef _GAME_HPP_
# define _GAME_HPP_

# define WINX 800
# define WINY 600
# define FPS 20
# define MAXENT 40
# define NOTIME -1
# define MAXTIME (7 * _fps)
# define BOOSTTIME (5 * _fps)
# define SCOREPATH "../Ressource/scores.txt"

# define ABS(x) (((x) < 0) ? -(x) : (x))

# include <iostream>
# include <sstream>
# include <list>
# include <vector>
# include <ctime>
# include "Exception.hpp"
# include "LibLoader.hpp"
# include "Snake.hpp"
# include "IGraphics.hpp"
# include "Time.hpp"

typedef std::list<t_snake>::iterator lit;
typedef std::list<t_snake>::const_iterator c_lit;
typedef std::vector<t_ent>::iterator vit;
typedef std::vector<t_ent>::const_iterator c_vit;
typedef struct s_player	t_player;

struct		s_player
{
  std::string	name;
  unsigned int	score;
};

class Game
{
public:
  Game(const int ac, char **av);
  virtual ~Game();

  void	start();

private:
  void	parse_arg(const int ac, char **av);
  bool	check_collision();
  int	spe_collision(vit &vbeg, vit &vend);
  void	move_snake(bool *key);
  void	display() const;
  void	init_entities();
  void	add_entities();
  void	remove_entities();
  void	move_entities();
  void	handle_fps(int &idx);
  void	print_scores() const;
  bool	monster_colision(vit &beg);
  void	encrypt_line(std::string &line) const;
  void	decrypt_line(std::string &line) const;
  void	end_score(bool *key, bool &done) const;

private:
  int			_x;
  int			_y;
  unsigned int		_fps;
  IGraphics		*_window;
  LibLoader		_lib;
  bool			_key[4];
  std::list<t_snake>	_snake;
  std::vector<t_ent>	_ent;
  std::vector<t_ent>	_entlist;
  t_player		_player;
};

#endif /* _GAME_H_ */

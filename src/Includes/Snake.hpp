#ifndef _SNAKE_H_
# define _SNAKE_H_

enum Keypos
  {
    LEFT = 0,
    UP,
    RIGHT,
    DOWN,
    ALEFT,
    ARIGHT,
    ESC,
    PAUSE,
    NEWGAME,
    SWITCHLIB,
    LAST
  };

enum Entities
  {
    HEAD = 0,
    BUDDY,
    TAIL,
    APPLE,
    PEAR,
    STRAWBERRY,
    BANANA,
    KIWI,
    BOOSTER,
    WALL,
    MONSTER,
    WARP,
    ELAST
  };

typedef struct	s_ent
{
  int		x;
  int		y;
  Entities	type;
  int		prob;
  int		time;
  double	score;
}		t_ent;

typedef struct	s_snake
{
  int		x;
  int		y;
  Keypos	dir;
}		t_snake;

#endif /* _SNAKE_H_ */

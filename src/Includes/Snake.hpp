#ifndef _SNAKE_H_
# define _SNAKE_H_

enum Keypos
  {
    LEFT = 0,
    UP,
    RIGHT,
    DOWN,
    ESC,
    PAUSE,
    NEWGAME,
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
    ELAST
  };

typedef struct	s_ent
{
  int		x;
  int		y;
  Entities	type;
  int		prob;
  int		time;
}		t_ent;

typedef struct	s_snake
{
  int		x;
  int		y;
  Keypos	dir;
}		t_snake;

#endif /* _SNAKE_H_ */

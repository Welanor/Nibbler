#ifndef _SNAKE_H_
# define _SNAKE_H_

enum Keypos
  {
    DOWN = 0,
    UP,
    LEFT,
    RIGHT,
    ESC,
    LAST
  };

enum Entities
  {
    HEAD = 0,
    BUDDY,
    TAIL,
    APPLE,
    GOLD_APPLE,
    BREAD,
    CHICKEN,
    PORK,
    ELAST
  };

typedef struct	s_ent
{
  int		x;
  int		y;
  Entities	type;
}		t_ent;

typedef struct	s_snake
{
  int		x;
  int		y;
  Keypos	dir;
}		t_snake;

#endif /* _SNAKE_H_ */

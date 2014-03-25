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

typedef struct	s_snake
{
  int		x;
  int		y;
  Keypos	dir;
}		t_snake;

#endif /* _SNAKE_H_ */

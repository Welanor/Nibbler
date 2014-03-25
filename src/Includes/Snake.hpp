#ifndef _SNAKE_H_
# define _SNAKE_H_

enum Direction
  {
    SOUTH = 0,
    NORTH,
    WEST,
    EAST,
  };

enum Keypos
  {
    DOWN = 0,
    UP,
    LEFT,
    RIGHT,
    LAST
  };

typedef struct	s_snake
{
  int		x;
  int		y;
  Direction	dir;
}		t_snake;

#endif /* _SNAKE_H_ */

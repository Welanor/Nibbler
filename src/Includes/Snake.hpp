#ifndef _SNAKE_H_
# define _SNAKE_H_

enum Direction
  {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
  };

typedef struct	s_snake
{
  int		x;
  int		y;
  Direction	dir;
}		t_snake;

#endif /* _SNAKE_H_ */

#include "Graphics.hpp"

Graphics::Graphics()
{
  std::cout << "Constructor NCURSE" << std::endl;
  initscr();
  start_color();
  /*  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  */
  curs_set(0);
  noecho();
}

Graphics::~Graphics()
{
  std::cout << "Destructor NCURSE" << std::endl;
  endwin();
}

bool	Graphics::create_window(const std::string &/*name*/,
				const int */*size_win*/, const int *size_map)
{
  _x = size_map[0];
  _y = size_map[1];
  if (_x > 190 || _y > 50 ||
      (_window = newwin(_y, _x, 0, 0)) == NULL)
    return (false);
  keypad(_window, TRUE);
  wtimeout(_window, 0);
  return (true);
}

void	Graphics::clear()
{
  werase(_window);
  box(_window, ACS_VLINE, ACS_HLINE);
}

void	Graphics::draw(int x, int y, int type, int dir)
{
  std::string caracs = "o~#APSBK!";
  char	c;

  c = caracs[type];
  mvwaddch(_window, y, x, c);
}

void	Graphics::destroyWindow()
{
  delwin(_window);
}

void	Graphics::handleEvent(bool *key)
{
  static int	keys[5] = {258, 259, 260, 261, 27};
  int		i;
  int		tmp;

  for (i = 0; i < LAST; i++)
    key[i] = false;
  if ((tmp = wgetch(_window)) == ERR)
    return ;
  for (i = 0; i < LAST && keys[i] != tmp; i++);
  if (i < LAST)
    key[i] = true;
}

void display_score(int score)
{

}

void Graphics::update()
{
  wrefresh(_window);
}


extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    return (new Graphics);
  }
}

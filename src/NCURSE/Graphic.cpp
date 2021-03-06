#include "Graphics.hpp"

Graphics::Graphics()
{
  initscr();
  start_color();
  curs_set(0);
  noecho();
}

Graphics::~Graphics()
{
  endwin();
}

bool	Graphics::create_window(const std::string &/*name*/,
				const int */*size_win*/, const int *size_map)
{
  _x = size_map[0];
  _y = size_map[1];
  if (_x + 2 > 190 || _y + 2 > 50 ||
      (_window = newwin(_y + 2, _x + 2, 0, 0)) == NULL)
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

void	Graphics::draw(int x, int y, int type, int /*dir*/)
{
  std::string caracs = "o~#APSBK!WMO";
  char	c;

  c = caracs[type];
  mvwaddch(_window, y + 1, x + 1, c);
}

void	Graphics::destroyWindow()
{
  delwin(_window);
}

void	Graphics::handleEvent(bool *key)
{
  static int	keys[LAST] = {'q', 'z', 'd', 's', KEY_LEFT, KEY_RIGHT, 27, 'p', 'r', 'c'};
  int		i;
  int		tmp;

  for (i = 0; i < LAST; i++)
    {
      if (i != PAUSE)
	key[i] = false;
    }
  if ((tmp = wgetch(_window)) == ERR)
    return ;
  for (i = 0; i < LAST && keys[i] != tmp; i++);
  if (i < LAST)
      key[i] = !key[i];
}

void	Graphics::display_score(int score)
{
  mvwprintw(_window, 0, 1, " Score: %d ", score);
}

void	Graphics::update()
{
  wrefresh(_window);
}

void	Graphics::display_f_score(const std::string &name, int score, int y)
{
  mvwprintw(_window, _y / 3 + y + 1, _x / 2 - 5, "%s  %d", name.c_str(), score);
}

void	Graphics::display_pause_msg()
{
  mvwaddstr(_window, _y, _x - 6, "Pause");
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    return (new Graphics);
  }
}

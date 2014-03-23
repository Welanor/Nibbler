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
  keypad(stdscr, TRUE);
  refresh();
}

Graphics::~Graphics()
{
  std::cout << "Destructor NCURSE" << std::endl;
  endwin();
}

void	Graphics::create_window(const std::string &name,
				int  size_x, int size_y)
{
  (void)name;(void)size_x;(void)size_y;
  _window = newwin(LINES, COLS, 0, 0);
  box(_window, ACS_VLINE, ACS_HLINE);
  wrefresh(_window);
}

void	Graphics::clear()
{
  wclear(_window);
}

void	Graphics::draw(const std::list<t_snake> &snake)
{
  (void)snake;
}

void	Graphics::destroyWindow()
{
  delwin(_window);
}

void	Graphics::init_events(bool *key)
{
  (void)key;
}

void Graphics::handleEvent()
{

}

bool Graphics::isDone()
{
  return (false);
}

extern "C"
{
  IGraphics	*init_graphics()
  {
    std::cout << "init_graphics" << std::endl;
    return (new Graphics);
  }
}

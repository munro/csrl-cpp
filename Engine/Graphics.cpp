#include <ncurses.h>
#include <cstdlib>
#include <cmath>
#include "Engine/Graphics.h"

/*
void Graphics::init()
{
  inst = new NCurses();
}

void Graphics::deinit()
{
  delete inst;
}

void Graphics::clear()
{
  inst->impl_clear();
}

void Graphics::add_char(int x, int y, char ch)
{
  inst->impl_add_char(x, y, ch);
}

void Graphics::add_string(int x, int y, string s)
{
  inst->impl_add_string(x, y, s);
}

void Graphics::refresh()
{
  inst->impl_refresh();
}
*/

// Draw a line
void Graphics::draw_line(int x1, int y1, int x2, int y2, int ch)
{

  int subx = x2 - x1, suby = y2 - y1;
  float slope, adder;

  // Draw start and end points
  mvaddch(y1, x1, ch);
  mvaddch(y2, x2, ch);

  // Line starts and end at same place
  if(subx == 0 && suby == 0)
  {
    return;
  }

  // Y/X Slope
  else if(abs(suby) <= abs(subx))
  {
    slope = double(suby) / double(subx);
    if(x1 < x2) { adder = y1; }
    else        { adder = y2; y1 = x1; x1 = x2; x2 = y1; }
    for(x1++; x1 < x2; x1++)
    {
      adder += slope;
      mvaddch(round(adder), x1, ch);

    }
  }

  // X/Y Slope
  else
  {
    slope = double(subx) / double(suby);
    if(y1 < y2) { adder = x1; }
    else        { adder = x2; x1 = y1; y1 = y2; y2 = x1; }
    for(y1++; y1 < y2; y1++)
    {
      adder += slope;
      mvaddch(y1, round(adder), ch);
    }
  }
}

// Print entire NCurses charset, useful for making GFXs for X11
void Graphics::print_charset(int x, int y)
{
  // List of DEC graphics starting at ACS_RARROW
  int values[32] = {0, 1, 2, 3, 5, 53, 54, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83};

  // Printable ASCII characters
  for(int i = 32; i < 127; i++)
  {
    mvaddch(y + i / 32, x + i % 32, i);
  }

  // Print DEC graphics
  for(int i = 0; i < 32; i++)
  {
    mvaddch(y + 4, x + i, ACS_RARROW + values[i]);
  }
}

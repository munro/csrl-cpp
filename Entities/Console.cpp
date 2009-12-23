#include <ncurses.h>
#include "Engine/CSRL.h"
#include "Entities/Console.h"

// Initialize console
Console::Console()
{
  // Setup blanking strings
  resize();

  // Setup variables
  display = false;
  height = 0;
  max_height = 10;
  load = 0.0;
}

// Deinitialize console
Console::~Console()
{
  clear_lines();
}

// Update console
bool Console::update(float delta)
{
  // Open console
  if(display && height < max_height)
  {
    load += delta * 15;
    height = int(load);
  }

  // Hide console
  else if(!display && height > 0)
  {
    mvprintw(0, 0, blank.c_str());
    mvprintw(int(load), 0, blank.c_str());
    load -= delta * 15;
    height = int(load);
  }
  return true;
}

// Draw console
void Console::draw()
{
  // Check if it's open
  if(height > 0)
  {
    int i;

    // Draw blank space
    for(i = 0; i < height; i++)
    {
      mvprintw(i, 0, blank.c_str());
    }

    // Draw tilde border
    mvprintw(height, 0, tilde.c_str());

    // Draw console data
    i = lines.size();
    for(list <Line *>::iterator it = lines.begin(); it != lines.end(); it++, i--)
    {
      if(i < height)
      {
        mvprintw(height - i - 1, 0, (*it)->text.c_str());
      }
    }

    // Draw typed text
    mvprintw(height - 1, 0, ("] " + text).c_str());
  }
}

// Screen resized, update blanking strings
void Console::resize()
{
  blank = string(CSRL::inst->width, ' ');
  tilde = string(CSRL::inst->width, '~');
}

// Input character into console
void Console::input(int ch)
{
  if(ch == 127)
  {
    if(text.size() == 1)
      text = "";
    else if(!text.empty())
      text = text.substr(0, text.size() - 1);
  }
  else if(ch == 10)
  {
    command(text);
    text = "";
  }
  else if(ch >= 32 && ch <= 255)
  {
    text += char(ch);
  }
}

// Run command on console
void Console::command(string text)
{
  add_line("Error: command \"" + text + "\" not found.");
}

// Add line to console
void Console::add_line(string text)
{
  Line *line = new Line;
  line->text = text;
  line->rows = 1;
  lines.push_back(line);
}

// Clear all lines
void Console::clear_lines()
{
  list <Line *>::iterator it;
  for(it = lines.begin(); it != lines.end(); it++)
  {
    delete (*it);
  }
  lines.clear();
}

// Toggle console's display
void Console::toggle()
{
  display = !display;
}

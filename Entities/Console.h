#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <string>
#include <list>
#include "Entities/Entity.h"
using namespace std;

struct Line
{
  string text;
  int rows;
};

class Console : public Entity
{
public:
  Console();
  ~Console();
  bool update(float delta);
  void draw();
  void resize();
  void input(int ch);
  void command(string text);
  void add_line(string text);
  void clear_lines();
  void toggle();
public:
  list <Line *> lines;
  string text, blank, tilde;
  int height, max_height;
  double load;
  bool display;
};

#endif

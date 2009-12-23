#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <string>
using namespace std;

class Graphics
{
public:
  static void init();
  static void deinit();
  static void clear();
  static void add_char(int x, int y, char ch);
  static void add_string(int x, int y, string s);
  static void refresh();
  static void draw_line(int x1, int y1, int x2, int y2, int ch);
  static void print_charset(int x, int y);
public:
  Graphics();
  virtual ~Graphics();
  virtual void impl_clear();
  virtual void impl_add_char(int x, int y, char ch);
  virtual void impl_add_string(int x, int y, string s);
  virtual void impl_refresh();
public:
  static Graphics *inst;
};

#endif

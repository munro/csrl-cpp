#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
public:
  virtual bool update(double delta);
  virtual void draw();
  virtual void resize();
  static int rotate_x(int x, int steps, int rotation);
  static int rotate_y(int y, int steps, int rotation);
};

#endif

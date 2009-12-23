#ifndef __BULLETEFFECT_H__
#define __BULLETEFFECT_H__

#include "Entities/Entity.h"

class BulletEffect : public Entity
{
public:
  BulletEffect(int x, int y, float angle);
  bool update(double delta);
  void draw();
public:
  double x, y, nx, ny, dx, dy, life;
  double cool;
};

#endif

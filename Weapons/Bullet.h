#ifndef __BULLET_H__
#define __BULLET_H__

#include "Entities/Entity.h" // This is an entity incase it's a slow bullet

class Character;

class Bullet : public Entity
{
public:
  Bullet(Character *owner, int x, int y, double angle, double damage);
  bool update(double delta);
};

#endif

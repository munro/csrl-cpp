#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <string>
#include "Entities/Object.h"
using namespace std;

class Character;

class Weapon : public Object
{
public:
  Weapon(string name, string display, int x, int y, int rotation);
  virtual void fire(Character *owner, float angle);
  virtual void reload();
  virtual void draw_info();
  virtual void draw_equipped();
  void draw();
public:
  string display;
  int rotation;
  char icon;
};

#endif

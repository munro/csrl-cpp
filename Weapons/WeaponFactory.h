#ifndef __WEAPONFACTORY_H__
#define __WEAPONFACTORY_H__

#include "Weapons/Weapon.h"

class WeaponFactory
{
public:
  static Weapon *create(string name, int x, int y, int rotation);
};

#endif

#include "Weapons/WeaponFactory.h"
#include "Weapons/Gun.h"

Weapon *WeaponFactory::create(string name, int x, int y, int rotation)
{
  // Create AK-47
  if(name == "AK47")
  {
    return new Gun("AK47", "|/-\\|/-\\", x, y, rotation, 0.06, 1.0, 4.0, 0.85, 0.2, 60, 180, 30, 30);
  }

  // :P
  else
  {
    return NULL;
  }
}

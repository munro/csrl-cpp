#include "Weapons/Bullet.h"
#include "Entities/Character.h"
#include "Engine/CSRL.h"
#include "Engine/Math.h"
#include <cmath>

// Initialize bullet
Bullet::Bullet(Character *owner, int x, int y, double angle, double damage)
{
  double amount;

  // Rotate angle to match cos/sin functions
  angle -= 90;

  // Check every character to see if they intersect the bullet
  for(list <Character *>::iterator it = CSRL::inst->characters.begin(); it != CSRL::inst->characters.end(); it++)
  {
    // Do not hit ourselves!
    if(owner != (*it))
    {
      // Calculate intersection
      amount = Math::intersect(x, y, x + cos(angle * 0.0174532925) * 200.0, y + sin(angle * 0.0174532925) * 200.0,
                                (*it)->x, (*it)->y);

      // Do damage to character
      if(amount)
      {
        (*it)->hit(amount * damage);
      }
    }
  }
}

// We want to immediately kill the bullet
bool Bullet::update(double delta)
{
  return false;
}


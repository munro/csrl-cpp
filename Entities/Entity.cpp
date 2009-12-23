#include "Entities/Entity.h"

// Update entity
bool Entity::update(double delta)
{
  return true;
}

// Draw entity
void Entity::draw()
{
}

// Screen resized
void Entity::resize()
{
}

// Rotate point, get x
int Entity::rotate_x(int x, int steps, int rotation)
{
  rotation %= 8;
  if(rotation >= 1 && rotation <= 3)
  {
    return x + steps;
  }
  else if(rotation >= 5 && rotation <= 7)
  {
    return x - steps;
  }
  else
  {
    return x;
  }
}

// Rotate point, get y
int Entity::rotate_y(int y, int steps, int rotation)
{
  rotation %= 8;
  if(rotation == 0 || rotation == 1 || rotation == 7)
  {
    return y - steps;
  }
  else if(rotation >= 3 && rotation <= 5)
  {
    return y + steps;
  }
  else
  {
    return y;
  }
}

#include <cmath>
#include <ncurses.h>
#include "Weapons/BulletEffect.h"
#include "Engine/Graphics.h"

// Initialize bullet effect
BulletEffect::BulletEffect(int x, int y, float angle)
{
  angle -= 90.0;
  this->x = nx = float(x);
  this->y = ny = float(y);
  dx = cos(angle * 0.0174532925f);
  dy = sin(angle * 0.0174532925f);
  life = 0.0f;
  cool = 0.0;
}

// Update bullet effect
bool BulletEffect::update(double delta)
{
  // Undraw the current line
  Graphics::draw_line(int(x), int(y), int(nx), int(ny), ' ');

  // Age this entity
  life += delta;

  // Entity is still alive
  if(life < 0.5)
  {
    cool -= delta;
    nx += dx * delta * 600.0;
    ny += dy * delta * 600.0;

    // This makes the line longer by updating it less frequently
    if(cool <= 0.0)
    {
      x = nx;
      y = ny;
      cool = 0.05;
    }
    return true;
  }

  // Entity is too old!  Time to kill it
  else
  {
    return false;
  }
}

// Draw the bullet effect
void BulletEffect::draw()
{
  Graphics::draw_line(int(x), int(y), int(nx), int(ny), ACS_DIAMOND);
  //Graphics::draw_line(int(x), int(y), 0, 0, ACS_DIAMOND);
  //mvaddch(int(y), int(x), ACS_DIAMON);
}

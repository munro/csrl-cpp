#include <ncurses.h>
#include "Engine/CSRL.h"
#include "Weapons/Weapon.h"
#include "Entities/Character.h"

// Initialize weapon
Weapon::Weapon(string name, string display, int x, int y, int rotation)
  : Object(name)
{
  this->display = display;
  this->x = x;
  this->y = y;
  this->rotation = rotation;
}

// Fire weapon
void Weapon::fire(Character *owner, float angle)
{
}

// Reload weapon
void Weapon::reload()
{
}

// Draw HUD
void Weapon::draw_info()
{
  mvprintw(CSRL::inst->height - 2, CSRL::inst->width - 1 - name.size(), name.c_str());
}

// Draw equipped on character
void Weapon::draw_equipped()
{
  // Point in the correct direction
  int dx = rotate_x(x, 1, rotation);
  int dy = rotate_y(y, 1, rotation);

  // Draw weapon
  mvaddch(dy, dx, display[rotation]);
}

// Draw weapon icon on the ground
void Weapon::draw()
{
  // Draw weapon icon
  mvaddch(y, x, 'w');
}

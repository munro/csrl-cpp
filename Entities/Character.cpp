#include <ncurses.h>
#include "Entities/Character.h"
#include "Weapons/Weapon.h"
#include "Weapons/WeaponFactory.h"

// Initialize character
Character::Character(string name, Team team, int x, int y)
{
  this->name = name;
  this->team = team;
  this->x = x;
  this->y = y;
  rotation = 2;
  weapon = WeaponFactory::create("AK47", x, y, rotation);
  health = 100;
  armor = 100;
}

// Input key from keyboard
bool Character::input(int ch)
{
  switch(ch | 32)
  {
    // Move player
    case 'j': rotate(-1); break;
    case 'l': rotate(1); break;
    case 'i': move(1, Up); break;
    case 'k': move(1, Down); break;
    case 'u':
    case 'h': move(1, Left); break;
    case 'o': move(1, Right); break;

    // Player shoots
    case 'a': fire(-19.285); break;
    case 'w': fire(-6.428); break;
    case 'e': fire(6.428); break;
    case 'f': fire(19.285); break;
    case 's':
    case 'd': fire(0.0); break;

    // Player reloads
    case 'r': reload(); break;
    default:
      if(ch == ':' || ch == ';')
      {
        move(1, Right);
        return true;
      }
      return false;
  }
  return true;
}

// Update character
bool Character::update(double delta)
{
  if(weapon)
  {
    weapon->update(delta);
  }
  return true;
}

// Draw character
void Character::draw()
{
  // Draw character
  mvaddch(y, x, '@');
  mvprintw(y + 2, x, "%s %i", name.c_str(), health);

  // Draw weapon
  if(weapon)
  {
    weapon->draw_equipped();
  }
}

// Hit character for damage
void Character::hit(int damage)
{
  health -= damage;
}

// Character fires weapon
void Character::fire(float angle)
{
  if(weapon)
  {
    weapon->fire(this, angle);
  }
}

// Character reloads current weapon
void Character::reload()
{
  if(weapon)
  {
    weapon->reload();
  }
}

// Character rotates
void Character::rotate(int turns)
{
  rotation = (rotation + turns + 40) % 8;

  // Update weapon's rotation too!
  if(weapon)
  {
    weapon->rotation = rotation;
  }
}

// Character moves
void Character::move(int steps, Direction direction)
{
  x = rotate_x(x, steps, rotation + 2 * direction);
  y = rotate_y(y, steps, rotation + 2 * direction);

  // Update weapon's coordinates too!
  if(weapon)
  {
    weapon->x = x;
    weapon->y = y;
  }
}

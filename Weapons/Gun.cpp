#include <ncurses.h>
#include <cstdlib>
#include "Engine/CSRL.h"
#include "Weapons/Gun.h"
#include "Weapons/Bullet.h"
#include "Weapons/BulletEffect.h"
#include "Entities/Character.h"

// Initialize gun
Gun::Gun(string name, string display, int x, int y, int rotation,
           double bullet_adder, double reloading_adder,
           double accuracy_angle, double accuracy_modifier, double accuracy_adder,
           int ammo, int max_ammo, int clip, int max_clip)
    : Weapon(name, display, x, y, rotation)
{

  // Initialize variables
  cool_down = 0.0;
  reloading = 0.0;
  accuracy = 0.0;

  // Setup weapon
  this->bullet_adder = bullet_adder;
  this->reloading_adder = reloading_adder;
  this->accuracy_angle = accuracy_angle;
  this->accuracy_modifier = accuracy_modifier;
  this->accuracy_adder = accuracy_adder;
  this->ammo = ammo;
  this->max_ammo = max_ammo;
  this->clip = clip;
  this->max_clip = max_clip;
}

// Update gun
bool Gun::update(double delta)
{
  // Decrement cool down
  if(cool_down > 0.0)
  {
    cool_down = (delta > cool_down ? 0.0 : cool_down - delta);
  }

  // Decrement reloading
  if(reloading > 0.0)
  {
    reloading -= delta;
    if(reloading <= 0.0)
    {
      reloading = 0.0;
      reload_complete();
    }
  }

  // Decrement accuracy
  if(accuracy > 0.0)
  {
    accuracy = (delta > accuracy ? 0.0 : accuracy - delta * accuracy_modifier);
  }

  // Auto reload
  if(reloading <= 0.0 && clip <= 0 && ammo > 0)
  {
    reload();
  }
  return true;
}

// Fire gun
void Gun::fire(Character *owner, float angle)
{
  // Check cool down
  if(cool_down <= 0.0 && reloading <= 0.0 && clip > 0)
  {
    // Rotate to the direction of the gun
    angle += rotation * 45;

    // Condsider weapon accuracy
    angle += accuracy_angle * accuracy * ((double(rand()) / double(RAND_MAX) - 0.5));

    // Create bullet entity
    CSRL::inst->add_entity((Entity *)new BulletEffect(x, y, angle));
    CSRL::inst->add_entity((Entity *)new Bullet(owner, x, y, angle, 10));

    // Subtract bullet
    clip--;

    // Set weapon cool down
    cool_down = bullet_adder;

    // Increment accuracy
    if(accuracy < 1.0)
    {
      accuracy += accuracy_adder;
      if(accuracy > 1.0)
      {
        accuracy = 1.0;
      }
    }
  }
}

// Reload gun
void Gun::reload()
{
  if(clip < max_clip && ammo > 0)
  {
    reloading = reloading_adder;
  }
}

// Reloading completed
void Gun::reload_complete()
{
  ammo += clip;
  if(ammo < max_clip)
  {
    clip = ammo;
    ammo = 0;
  }
  else
  {
    //ammo -= max_clip;
    clip = max_clip;
  }
  accuracy = 0.0;
}

// Draw gun HUD
void Gun::draw_info()
{
  int meter_max;

  // Draw name
  mvprintw(CSRL::inst->height - 2, CSRL::inst->width - 25 - name.size(), name.c_str());

  // Draw ammo
  mvprintw(CSRL::inst->height - 2, CSRL::inst->width - 25, " %3i/%3i", clip, ammo);

  // Draw meter
  mvprintw(CSRL::inst->height - 2, CSRL::inst->width - 16, (reloading > 0.0 ? "[    reloading ]" : "[     accuracy ]"));

  // Get meter value
  if(reloading > 0.0)
  {
    meter_max = (reloading_adder - reloading) / reloading_adder * 15;
  }
  else
  {
    meter_max = accuracy * 15;
  }

  // Draw meter value
  for(int i = 0; i < meter_max; i++)
  {
    mvaddch(CSRL::inst->height - 2, CSRL::inst->width - 15 + i, '=');
  }
}

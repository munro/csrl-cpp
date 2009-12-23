#ifndef __GUN_H__
#define __GUN_H__

#include "Weapons/Weapon.h"

class Character;

class Gun : public Weapon
{
public:
  Gun(string name, string display, int x, int y, int rotation,
        double bullet_adder, double reloading_adder,
        double accuracy_angle, double accuracy_modifier, double accuracy_adder,
        int ammo, int max_ammo, int clip, int max_clip);
  void fire(Character *owner, float angle);
  void reload();
  void reload_complete();
  bool update(double delta);
  void draw_info();
public:
  double cool_down, bullet_adder;
  double accuracy, accuracy_angle, accuracy_modifier, accuracy_adder;
  double reloading, reloading_adder;
  int ammo, max_ammo, clip, max_clip;
};

#endif

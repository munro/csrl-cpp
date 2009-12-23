#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <string>
#include "Entities/Object.h"
using namespace std;

enum Team {CounterTerrorist, Terrorist, Hostage};
enum Direction {Up = 0, Right = 1 , Down = 2, Left = 3};

class Weapon;

class Character : public Object
{
public:
  Character(string name, Team team, int x, int y);
  bool input(int ch);
  bool update(double delta);
  void draw();
  void hit(int damage);
  void fire(float angle);
  void reload();
  void rotate(int turns);
  void move(int steps, Direction direction);
public:
  Team team;
  int rotation, health, armor;
  Weapon *weapon;
};

#endif

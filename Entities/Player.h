#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entities/Entity.h"

enum Team;
class Character;

class Player : public Entity
{
public:
  Player(string name, Team team);
  void update(double delta);
  void draw();
  void spawn(int x, int y);
public:
  string name;
  Team team;
  Character *character;
  bool is_dead;
};

#endif

#ifndef __CSRL_H__
#define __CSRL_H__

#include <list>

using namespace std;

class Entity;
class Object;
class Character;
class Console;

class CSRL
{
public:
  CSRL();
  ~CSRL();
  void run();
  void get_input();
  void update(double delta);
  void draw();
  void draw_hud();
  void resize();
  Character *add_character(Character *character);
  Object *add_object(Object *object);
  Entity *add_entity(Entity *entity);

public:
  int width, height;
  bool running;
  Console *console;
  Character *player;
  list <Character *> characters;
  list <Object *> objects;
  list <Entity *> entities;
  static CSRL *inst;
};

#endif

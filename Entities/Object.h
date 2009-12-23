#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include "Entities/Entity.h"
using namespace std;

class Object : public Entity
{
public:
  Object(string name);
  Object();
public:
  string name;
  int x, y;
};

#endif

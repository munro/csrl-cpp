#include "Entities/Object.h"

// Initialize object with name
Object::Object(string name)
{
  this->name = name;
}

// Initialize object with no name
Object::Object()
{
  name = "";
}

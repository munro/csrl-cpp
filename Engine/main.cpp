#include "Engine/CSRL.h"

int main(int argc, char **argv)
{
  CSRL::inst = new CSRL();
  delete CSRL::inst;
  return 0;
}

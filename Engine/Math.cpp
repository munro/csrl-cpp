#include <cstdlib>
#include <cmath>
#include "Engine/Math.h"

// Check if point intersects with line, return how close to the center it is to the point
bool Math::intersect(int x1, int y1, int x2, int y2, int cx, int cy)
{
  int subx = x2 - x1, suby = y2 - y1, swapx, swapy;
  float slope;

  // Line starts and end at same place
  if(subx == 0 && suby == 0)
  {
    return (x1 == cx && y1 == cy);
  }

  // Y/X Slope
  else if(abs(suby) <= abs(subx))
  {
    if(x1 > x2) { swapx = x1; swapy = y1; x1 = x2; y1 = y2; x2 = swapx; y2 = swapy; }
    slope = double(suby) / double(subx);
    return (cy == y1 + round(slope * (cx - x1)));
  }

  // X/Y Slope
  else
  {
    if(y1 > y2) { swapx = x1; swapy = y1; x1 = x2; y1 = y2; x2 = swapx; y2 = swapy; }
    slope = double(subx) / double(suby);
    return (cx == x1 + round(slope * (cy - y1)));
  }
}

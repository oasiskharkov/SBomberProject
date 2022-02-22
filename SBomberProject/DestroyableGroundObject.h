#pragma once

#include "GameObject.h"

class DestroyableGroundObject : public GameObject
{
public:
   virtual bool isInside(double x1, double x2) const = 0;
   virtual uint16_t GetScore() const = 0;
   bool HandleInsideCheck(double x1, double x2)
   {
      return isInside(x1, x2);
   }
};
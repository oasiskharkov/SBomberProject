#pragma once

#include <stdint.h>

#include "GameObject.h"

class DestroyableGroundObject : public GameObject
{
public:
   virtual bool __fastcall isInside(double x1, double x2) const = 0;
   virtual uint16_t GetScore() const = 0;
protected:
};
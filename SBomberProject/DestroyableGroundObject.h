#pragma once

#include <memory>

#include "GameObject.h"

class BombDecorator;

class DestroyableGroundObject : public GameObject
{
public:
   virtual bool isInside(double x1, double x2) const = 0;
   virtual uint16_t GetScore() const = 0;
   virtual std::shared_ptr<DestroyableGroundObject> Clone() const = 0;
   bool HandleInsideCheck(BombDecorator* bombDecorator) const;
};
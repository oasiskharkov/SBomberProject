#pragma once

#include <iostream>

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:
   static const uint16_t BombCost = 10; // ????????? ????? ? ?????
   void Draw() const override;
   void Accept(const Visitor& v) override;
};


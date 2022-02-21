#pragma once

#include "Bomb.h"

class BombDecorator : public DynamicObject
{
public:
   void Draw() const override;
   void Move(uint64_t time) override;
   void SetPos(double nx, double ny) override; 
   double GetY() const override;
   double GetX() const override;
   void SetWidth(uint16_t width) override;
   uint16_t GetWidth() const override;
   void SetSpeed(double sp) override;
   void SetDirection(double dx, double dy) override;
private:
   Bomb bomb;
};
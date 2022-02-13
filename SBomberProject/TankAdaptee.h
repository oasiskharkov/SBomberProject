#pragma once

#include <iostream>

class TankAdaptee {
public:
   TankAdaptee();

   void Paint() const;
   bool isInRange(double x1, double x2) const;

   uint16_t GetScore() const { return score; }

   void SetPos(double nx, double ny) { x = nx; y = ny; }
   double GetY() const { return y; }
   double GetX() const { return x; }

   void SetWidth(uint16_t widthN) { width = widthN; }
   uint16_t GetWidth() const { return width; }
protected:
   double x;
   double y;
   uint16_t width;
   const uint16_t score = 50;
};
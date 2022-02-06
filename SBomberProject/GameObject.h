#pragma once

class GameObject {
public:
   GameObject() : 
      x{ 0.0 },
      y{ 0.0 },
      width{ 0 }
   { }

   virtual void Draw() const = 0;
   void SetPos(double nx, double ny) { x = nx; y = ny; }

   double GetY() const { return y; }
   double GetX() const { return x; }

   void SetWidth(uint16_t widthN) { width = widthN; }
   uint16_t GetWidth() const { return width; }
protected:
   double x;
   double y;
   uint16_t width;
};
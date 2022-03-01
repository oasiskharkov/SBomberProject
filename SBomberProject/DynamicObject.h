#pragma once

#include "GameObject.h"
#include "Visitor.h"

class DynamicObject : public GameObject 
{
public:
    DynamicObject() : 
       speed{ 0.0 },
       xDirection{ 0.0 },
       yDirection{ 0.0 }
    {}

   virtual void SetSpeed(double sp) { speed = sp; }
   virtual void SetDirection(double dx, double dy) { xDirection = dx; yDirection = dy; }
   virtual void Accept(const Visitor& v) = 0;
   
   double GetSpeed() const { return speed; }
   std::pair<double, double> GetDirection() const { return std::make_pair(xDirection, yDirection); }
  
   virtual void Move(uint64_t time) { x += xDirection * speed * time * 0.001; y += yDirection * speed * time * 0.001; };
protected:
   double speed;
   double xDirection;
   double yDirection;
};
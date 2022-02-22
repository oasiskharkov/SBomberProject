#pragma once

#include "GameObject.h"
#include "Visitor.h"

class DynamicObject : public GameObject 
{
public:
    DynamicObject() : 
       speed{ 0.0 },

       xDirction{ 0.0 },
       yDirection{ 0.0 }
    { }

   virtual void SetSpeed(double sp) { speed = sp; }
   virtual void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
   virtual void Accept(const Visitor& v) = 0;
   
   double GetSpeed() const { return speed; }
   std::pair<double, double> GetDirection() const { return std::make_pair(xDirction, yDirection); }
  
   virtual void Move(uint64_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };
protected:
   double speed;
   double xDirction;
   double yDirection;
};
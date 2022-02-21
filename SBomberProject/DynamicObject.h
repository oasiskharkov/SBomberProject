#pragma once

#include "GameObject.h"

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
  
   virtual void Move(uint64_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };
protected:
   double speed;
   double xDirction;
   double yDirection;
};
#pragma once

#include <memory>

#include "SBomberImpl.h"

class SBomber
{
public:
   SBomber();
   ~SBomber() = default;

   bool GetExitFlag() const; 

   void ProcessKBHit();
   void TimeStart();
   void TimeFinish();

   void DrawFrame();
   void MoveObjects();
   void CheckObjects();
private:
   std::unique_ptr<SBomberImpl> impl;
};
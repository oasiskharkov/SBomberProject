#pragma once

#include "GameObject.h"

class LevelGUI : public GameObject 
{
public:
   LevelGUI();

   void SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
   void SetHeight(uint16_t heightN) { height = heightN; };

   uint16_t GetFinishX() const { return finishX; }
   void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

   void Draw() const override;
private:
   uint16_t height;
   uint16_t finishX = 109;
   uint64_t passedTime;
   uint64_t fps;
   uint16_t bombsNumber;
   int16_t score;
};




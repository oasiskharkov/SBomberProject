#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "BombDecorator.h"
#include "Ground.h"
#include "Tank.h"
#include "MyTools.h"

class SBomber
{
public:
   SBomber();
   ~SBomber();

   bool GetExitFlag() const { return exitFlag; }

   void ProcessKBHit();
   void TimeStart();
   void TimeFinish();

   void DrawFrame();
   void MoveObjects();
   void CheckObjects();

private:
   void CheckPlaneAndLevelGUI();
   void CheckBombsAndGround();
   void  CheckDestroyableObjects(BombDecorator* pBomb);

   void  DeleteDynamicObj(DynamicObject* pBomb);
   void  DeleteStaticObj(GameObject* pObj);

   Ground* FindGround() const;
   Plane* FindPlane() const;
   LevelGUI* FindLevelGUI() const;

   std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const;
   std::vector<BombDecorator*> FindAllBombs() const;

   void DropBomb();

   std::vector<DynamicObject*> vecDynamicObj;
   std::vector<GameObject*> vecStaticObj;

   bool exitFlag;

   uint64_t startTime;
   uint64_t finishTime;
   uint64_t passedTime;
   uint64_t deltaTime;
   uint16_t bombsNumber;
   uint16_t fps;
   int16_t score;

   MyTools::LoggerSingleton& logger;
};
#pragma once

#include <vector>
#include <memory>

#include "LevelGUI.h"
#include "Plane.h"
#include "Ground.h"
#include "BombDecorator.h"
#include "BombIterator.h"
#include "MyTools.h"
#include "Tank.h"
#include "Command.h"

class SBomber
{
public:
   SBomber();
   ~SBomber() = default;

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
   void CheckDestroyableObjects(BombDecorator* pBomb);

   void DeleteDynamicObj(DynamicObject* pBomb);
   void DeleteStaticObj(GameObject* pObj);

   Ground* FindGround() const;
   Plane* FindPlane() const;
   LevelGUI* FindLevelGUI() const;

   std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const;
   std::vector<BombDecorator*> FindAllBombs() const;

   void DropBomb();

   void CommandExecuter(std::unique_ptr<Command> command);

   std::vector<std::shared_ptr<DynamicObject>> vecDynamicObj;
   std::vector<std::shared_ptr<GameObject>> vecStaticObj;

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
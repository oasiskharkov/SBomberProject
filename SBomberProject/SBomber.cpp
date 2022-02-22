#include <conio.h>
#include <windows.h>
#include <memory>

#include "SBomber.h"
#include "MyTools.h"
#include "BombIterator.h"
#include "TankAdapter.h"
#include "HouseBuilder.h"

using namespace MyTools;
using namespace std::placeholders;

SBomber::SBomber() :
   exitFlag{ false },
   startTime{ 0 },
   finishTime{ 0 },
   passedTime{ 0 },
   deltaTime{ 0 },
   bombsNumber{ 10 },
   fps{ 0 },
   score{ 0 },
   logger{ LoggerSingleton::getInstance(FileLoggerSingleton::getInstance()) },
   collisionDetector{ std::make_unique<CollisionImplWin>() }
{
   srand(static_cast<unsigned>(time(nullptr)));

   logger.OpenFile("log.txt");
   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   std::shared_ptr<Plane> pPlane = std::make_shared<Plane>();
   pPlane->SetDirection(1, 0.1);
   pPlane->SetSpeed(4);
   pPlane->SetPos(5, 10);
   vecDynamicObj.emplace_back(pPlane);

   std::shared_ptr<LevelGUI> pGUI = std::make_shared<LevelGUI>();
   pGUI->SetParam(passedTime, fps, bombsNumber, score);
   const uint16_t maxX = GetMaxX();
   const uint16_t maxY = GetMaxY();
   const uint16_t offset = 3;
   const uint16_t width = maxX - 7;
   pGUI->SetPos(offset, offset);
   pGUI->SetWidth(width);
   pGUI->SetHeight(maxY - 4);
   pGUI->SetFinishX(offset + width - 4);
   vecStaticObj.emplace_back(pGUI);

   std::shared_ptr<Ground> pGround = std::make_shared<Ground>();
   const uint16_t groundY = maxY - 5;
   pGround->SetPos(offset + 1, groundY);
   pGround->SetWidth(width - 2);
   vecStaticObj.emplace_back(pGround);

   std::shared_ptr<TankAdapter> pTankAdapter = std::make_shared<TankAdapter>();
   pTankAdapter->SetWidth(13);
   pTankAdapter->SetPos(30, groundY - 1);
   vecStaticObj.emplace_back(pTankAdapter);

   std::shared_ptr<Tank> pTank = std::make_shared<Tank>();
   pTank->SetWidth(13);
   pTank->SetPos(50, groundY - 1);
   vecStaticObj.emplace_back(pTank);

   std::shared_ptr<Tank> pTank2 = std::make_shared<Tank>();
   pTank2->SetWidth(13);
   pTank2->SetPos(70, groundY - 1);
   vecStaticObj.emplace_back(pTank2);

   std::shared_ptr<House> pHouse = std::make_shared<House>();
   pHouse->SetWidth(12);
   pHouse->SetPos(90, groundY - 1);
   vecStaticObj.emplace_back(pHouse);

   HouseBuilderA hbA;
   HouseBuilderB hbB;
   if (rand() % 2 == 0)
   {
      Director::createHouse(hbA, *pHouse);
   }
   else
   {
      Director::createHouse(hbB, *pHouse);
   }
}

void SBomber::MoveObjects()
{
   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   for (size_t i = 0; i < vecDynamicObj.size(); ++i)
   {
      if (vecDynamicObj[i] != nullptr)
      {
         vecDynamicObj[i]->Move(deltaTime);
         vecDynamicObj[i]->Accept(logVisitor);
      }
   }
};

void SBomber::CheckObjects()
{
   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   CheckPlaneAndLevelGUI();
   CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
   std::function<Plane*()> fP = std::bind(&SBomber::FindPlane, this);
   std::function<LevelGUI*()> fLG = std::bind(&SBomber::FindLevelGUI, this);
   
   collisionDetector.CheckPlaneAndLevelGUI(std::move(fP), std::move(fLG), exitFlag);
}

void SBomber::CheckBombsAndGround()
{
   /*std::function<std::vector<BombDecorator*>()> fB = std::bind(&SBomber::FindAllBombs, this);
   std::function<Ground*()> fG = std::bind(&SBomber::FindGround, this);
   std::function<void(BombDecorator*)> fCDO = std::bind(&SBomber::CheckDestroyableObjects, this, _1);
   std::function<void(BombDecorator*)> fDDO = std::bind(&SBomber::DeleteDynamicObj, this, _1);

   collisionDetector.CheckBombsAndGround(std::move(fB), std::move(fG), std::move(fCDO), std::move(fDDO));*/

   std::vector<BombDecorator*> vecBombs = FindAllBombs();
   Ground* pGround = FindGround();
   const double y = pGround->GetY();
   for (size_t i = 0; i < vecBombs.size(); ++i)
   {
      if (vecBombs[i]->GetY() >= y)
      {
         pGround->AddCrater(vecBombs[i]->GetX());
         const auto& dgos = vecBombs[i]->CheckDestroyableObjects();
         for (const auto& dgo : dgos)
         {
            score += dgo->GetScore();
            DeleteStaticObj(dgo);
         }
         DeleteDynamicObj(vecBombs[i]);
      }
   }
}

void SBomber::CheckDestroyableObjects(BombDecorator* pBomb)
{
   std::function<std::vector<DestroyableGroundObject*>()> fDGO = std::bind(&SBomber::FindDestroyableGroundObjects, this);
   std::function<void(GameObject*)> fDSO = std::bind(&SBomber::DeleteStaticObj, this, _1);

   collisionDetector.CheckDestroyableObjects(std::move(fDGO), std::move(fDSO), score, pBomb);
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
   std::unique_ptr<Command> command = std::make_unique<DeleteDynamicObjectCommand>(vecDynamicObj, pObj);
   CommandExecuter(std::move(command));
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
   std::unique_ptr<Command> command = std::make_unique<DeleteStaticObjectCommand>(vecStaticObj, pObj);
   CommandExecuter(std::move(command));
}

std::vector<DestroyableGroundObject*> SBomber::FindDestroyableGroundObjects() const
{
   std::vector<DestroyableGroundObject*> vec;
   Tank* pTank;
   TankAdapter* pTankAdapter;
   House* pHouse;
   for (size_t i = 0; i < vecStaticObj.size(); ++i)
   {
      pTank = dynamic_cast<Tank*>(vecStaticObj[i].get());
      if (pTank != nullptr)
      {
         vec.emplace_back(pTank);
         continue;
      }

      pTankAdapter = dynamic_cast<TankAdapter*>(vecStaticObj[i].get());
      if (pTankAdapter != nullptr)
      {
         vec.emplace_back(pTankAdapter);
         continue;
      }

      pHouse = dynamic_cast<House*>(vecStaticObj[i].get());
      if (pHouse != nullptr)
      {
         vec.emplace_back(pHouse);
         continue;
      }
   }

   return vec;
}

Ground* SBomber::FindGround() const
{
   Ground* pGround;

   for (size_t i = 0; i < vecStaticObj.size(); ++i)
   {
      pGround = dynamic_cast<Ground*>(vecStaticObj[i].get());
      if (pGround != nullptr)
      {
         return pGround;
      }
   }
   return nullptr;
}

std::vector<BombDecorator*> SBomber::FindAllBombs() const
{
   std::vector<BombDecorator*> vecBombs;

   BombIterator bi(vecDynamicObj);
   for (auto it = bi.begin(); it != bi.end(); ++it)
   {
      vecBombs.emplace_back(*it);
   }
   return vecBombs;
}


Plane* SBomber::FindPlane() const
{
   for (size_t i = 0; i < vecDynamicObj.size(); ++i)
   {
      Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i].get());
      if (p != nullptr)
      {
         return p;
      }
   }
   return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const
{
   for (size_t i = 0; i < vecStaticObj.size(); ++i)
   {
      LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i].get());
      if (p != nullptr)
      {
         return p;
      }
   }
   return nullptr;
}

void SBomber::ProcessKBHit()
{
   int c = _getch();

   if (c == 224)
   {
      c = _getch();
   }

   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked. key = ", c);

   switch (c) {

   case 27: // esc
      exitFlag = true;
      break;

   case 72: // up
      FindPlane()->ChangePlaneY(-0.25);
      break;

   case 80: // down
      FindPlane()->ChangePlaneY(0.25);
      break;

   case 'b':
      DropBomb();
      break;

   case 'B':
      DropBomb();
      break;

   default:
      break;
   }
}

void SBomber::DrawFrame()
{
   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   for (size_t i = 0; i < vecDynamicObj.size(); ++i)
   {
      if (vecDynamicObj[i] != nullptr)
      {
         vecDynamicObj[i]->Draw();
      }
   }

   for (size_t i = 0; i < vecStaticObj.size(); ++i)
   {
      if (vecStaticObj[i] != nullptr)
      {
         vecStaticObj[i]->Draw();
      }
   }

   GotoXY(0, 0);
   fps++;

   FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");
   startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
   finishTime = GetTickCount64();
   deltaTime = uint16_t(finishTime - startTime);
   passedTime += deltaTime;

   logger.WriteToLog(std::string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::DropBomb()
{
   if (bombsNumber > 0)
   {
      logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");
      auto dgos = FindDestroyableGroundObjects();
      std::unique_ptr<Command> command = std::make_unique<DropBombCommand>(vecDynamicObj, dgos, FindPlane(), bombsNumber, score);
      CommandExecuter(std::move(command));
   }
}

void SBomber::CommandExecuter(std::unique_ptr<Command> command)
{
   if (command)
   {
      command->Execute();
   }
}

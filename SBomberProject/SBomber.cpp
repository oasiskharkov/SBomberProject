#include <conio.h>
#include <windows.h>
#include <memory>

#include "MyTools.h"
#include "SBomber.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "Command.h"

using namespace MyTools;

SBomber::SBomber() :
   exitFlag{ false },
   startTime{ 0 },
   finishTime{ 0 },
   passedTime{ 0 },
   deltaTime{ 0 },
   bombsNumber{ 10 },
   fps{ 0 },
   score{ 0 },
   logger{ LoggerSingleton::getInstance(FileLoggerSingleton::getInstance()) }
{
   logger.OpenFile("log.txt");
   logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   Plane* p = new Plane;
   p->SetDirection(1, 0.1);
   p->SetSpeed(4);
   p->SetPos(5, 10);
   vecDynamicObj.push_back(p);

   LevelGUI* pGUI = new LevelGUI;
   pGUI->SetParam(passedTime, fps, bombsNumber, score);
   const uint16_t maxX = GetMaxX();
   const uint16_t maxY = GetMaxY();
   const uint16_t offset = 3;
   const uint16_t width = maxX - 7;
   pGUI->SetPos(offset, offset);
   pGUI->SetWidth(width);
   pGUI->SetHeight(maxY - 4);
   pGUI->SetFinishX(offset + width - 4);
   vecStaticObj.push_back(pGUI);

   Ground* pGr = new Ground;
   const uint16_t groundY = maxY - 5;
   pGr->SetPos(offset + 1, groundY);
   pGr->SetWidth(width - 2);
   vecStaticObj.push_back(pGr);

   Tank* pTank = new Tank;
   pTank->SetWidth(13);
   pTank->SetPos(30, groundY - 1);
   vecStaticObj.push_back(pTank);

   pTank = new Tank;
   pTank->SetWidth(13);
   pTank->SetPos(50, groundY - 1);
   vecStaticObj.push_back(pTank);

   House* pHouse = new House;
   pHouse->SetWidth(13);
   pHouse->SetPos(80, groundY - 1);
   vecStaticObj.push_back(pHouse);
}

SBomber::~SBomber()
{
   for (size_t i = 0; i < vecDynamicObj.size(); ++i)
   {
      if (vecDynamicObj[i] != nullptr)
      {
         delete vecDynamicObj[i];
      }
   }

   for (size_t i = 0; i < vecStaticObj.size(); ++i)
   {
      if (vecStaticObj[i] != nullptr)
      {
         delete vecStaticObj[i];
      }
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
   if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
   {
      exitFlag = true;
   }
}

void SBomber::CheckBombsAndGround()
{
   std::vector<BombDecorator*> vecBombs = FindAllBombs();
   Ground* pGround = FindGround();
   const double y = pGround->GetY();
   for (size_t i = 0; i < vecBombs.size(); ++i)
   {
      if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
      {
         pGround->AddCrater(vecBombs[i]->GetX());
         CheckDestroyableObjects(vecBombs[i]);
         DeleteDynamicObj(vecBombs[i]);
      }
   }

}

void SBomber::CheckDestroyableObjects(BombDecorator* pBomb)
{
   std::vector<DestroyableGroundObject*> vecDestroyableObjects = FindDestroyableGroundObjects();
   const double size = pBomb->GetWidth();
   const double size_2 = size / 2;
   for (size_t i = 0; i < vecDestroyableObjects.size(); ++i)
   {
      const double x1 = pBomb->GetX() - size_2;
      const double x2 = x1 + size;
      if (vecDestroyableObjects[i]->isInside(x1, x2))
      {
         score += vecDestroyableObjects[i]->GetScore();
         DeleteStaticObj(vecDestroyableObjects[i]);
      }
   }
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
   std::unique_ptr<Command> command = std::make_unique<DeleteDynamicObjectCommand>(vecDynamicObj, pObj);
   command->Execute();
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
   std::unique_ptr<Command> command = std::make_unique<DeleteStaticObjectCommand>(vecStaticObj, pObj);
   command->Execute();
}

std::vector<DestroyableGroundObject*> SBomber::FindDestroyableGroundObjects() const
{
   std::vector<DestroyableGroundObject*> vec;
   Tank* pTank;
   House* pHouse;
   for (size_t i = 0; i < vecStaticObj.size(); ++i)
   {
      pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
      if (pTank != nullptr)
      {
         vec.push_back(pTank);
         continue;
      }

      pHouse = dynamic_cast<House*>(vecStaticObj[i]);
      if (pHouse != nullptr)
      {
         vec.push_back(pHouse);
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
      pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
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

   for (size_t i = 0; i < vecDynamicObj.size(); ++i)
   {
      BombDecorator* pBomb = dynamic_cast<BombDecorator*>(vecDynamicObj[i]);
      if (pBomb != nullptr)
      {
         vecBombs.push_back(pBomb);
      }
   }

   return vecBombs;
}

Plane* SBomber::FindPlane() const
{
   for (size_t i = 0; i < vecDynamicObj.size(); ++i)
   {
      Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
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
      LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
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

      std::unique_ptr<Command> command = std::make_unique<DropBombCommand>(vecDynamicObj, FindPlane(), bombsNumber, score);
      command->Execute();
   }
}

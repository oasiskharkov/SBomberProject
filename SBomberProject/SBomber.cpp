#include <conio.h>
#include <windows.h>

#include "SBomber.h"
#include "BombIterator.h"
#include "TankAdapter.h"
#include "HouseBuilder.h"
#include "MyTools.h"
#include "Tank.h"
#include "Command.h"
#include "Collision.h"
#include "Visitor.h"
#include "Mediator.h"
#include "Plane.h"
#include "LevelGUI.h"
#include "Ground.h"

using namespace std::placeholders;
using namespace MyTools;

class SBomberImpl
{

public:
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
   CollisionDetector collisionDetector;
   LogVisitor logVisitor;
   Mediator mediator;

   SBomberImpl() :
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

      std::shared_ptr<Plane> pPlane;
      if (rand() % 2 == 0)
      {
         pPlane = std::make_shared<ColorPlane>();
      }
      else
      {
         pPlane = std::make_shared<BigPlane>();
      }

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
      pGround->SetPos(offset + 1, (double)groundY);
      pGround->SetWidth(width - 2);
      vecStaticObj.emplace_back(pGround);

      std::shared_ptr<TankAdapter> pTankAdapter = std::make_shared<TankAdapter>();
      pTankAdapter->SetWidth(13);
      pTankAdapter->SetPos(30, groundY - 1);
      vecStaticObj.emplace_back(pTankAdapter);

      std::shared_ptr<Tank> pTank = std::make_shared<Tank>(&mediator);
      pTank->SetWidth(13);
      pTank->SetPos(50, groundY - 1);
      vecStaticObj.emplace_back(pTank);

      std::shared_ptr<Tank> pTank2 = std::make_shared<Tank>(&mediator);
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

      mediator.SetReceiver(pGUI.get());
   }

   void CheckPlaneAndLevelGUI()
   {
      std::function<Plane* ()> fP = std::bind(&SBomberImpl::FindPlane, this);
      std::function<LevelGUI* ()> fLG = std::bind(&SBomberImpl::FindLevelGUI, this);

      collisionDetector.CheckPlaneAndLevelGUI(std::move(fP), std::move(fLG), exitFlag);
   }

   void CheckBombsAndGround()
   {
      /*std::function<std::vector<BombDecorator*>()> fB = std::bind(&SBomberImpl::FindAllBombs, this);
      std::function<Ground*()> fG = std::bind(&SBomberImpl::FindGround, this);
      std::function<void(BombDecorator*)> fCDO = std::bind(&SBomberImpl::CheckDestroyableObjects, this, _1);
      std::function<void(BombDecorator*)> fDDO = std::bind(&SBomberImpl::DeleteDynamicObj, this, _1);

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
               if (dgo)
               {
                  score += dgo->GetScore();
                  DeleteStaticObj(dgo);
               }
            }
            DeleteDynamicObj(vecBombs[i]);
         }
      }
   }

   void CheckDestroyableObjects(BombDecorator* pBomb)
   {
      std::function<std::vector<DestroyableGroundObject*>()> fDGO = std::bind(&SBomberImpl::FindDestroyableGroundObjects, this);
      std::function<void(GameObject*)> fDSO = std::bind(&SBomberImpl::DeleteStaticObj, this, _1);

      collisionDetector.CheckDestroyableObjects(std::move(fDGO), std::move(fDSO), score, pBomb);
   }

   void DeleteDynamicObj(DynamicObject* pObj)
   {
      std::unique_ptr<Command> command = std::make_unique<DeleteDynamicObjectCommand>(vecDynamicObj, pObj);
      CommandExecuter(std::move(command));
   }

   void DeleteStaticObj(GameObject* pObj)
   {
      std::unique_ptr<Command> command = std::make_unique<DeleteStaticObjectCommand>(vecStaticObj, pObj);
      CommandExecuter(std::move(command));
   }

   std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const
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

   Ground* FindGround() const
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

   std::vector<BombDecorator*> FindAllBombs() const
   {
      std::vector<BombDecorator*> vecBombs;

      BombIterator bi(vecDynamicObj);
      for (auto it = bi.begin(); it != bi.end(); ++it)
      {
         vecBombs.emplace_back(*it);
      }
      return vecBombs;
   }

   Plane* FindPlane() const
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

   LevelGUI* FindLevelGUI() const
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

   void DropBomb()
   {
      if (bombsNumber > 0)
      {
         logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");
         auto dgos = FindDestroyableGroundObjects();
         std::unique_ptr<Command> command = std::make_unique<DropBombCommand>(vecDynamicObj, dgos, FindPlane(), bombsNumber, score);
         CommandExecuter(std::move(command));
      }
   }

   void CommandExecuter(std::unique_ptr<Command> command)
   {
      if (command)
      {
         command->Execute();
      }
   }
};

SBomber::SBomber() :
   impl{ std::make_unique<SBomberImpl>() }
{
   
}

void SBomber::MoveObjects()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   for (size_t i = 0; i < impl->vecDynamicObj.size(); ++i)
   {
      if (impl->vecDynamicObj[i] != nullptr)
      {
         impl->vecDynamicObj[i]->Move(impl->deltaTime);
         impl->vecDynamicObj[i]->Accept(impl->logVisitor);
      }
   }
};

void SBomber::CheckObjects()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   impl->CheckPlaneAndLevelGUI();
   impl->CheckBombsAndGround();
};

bool SBomber::GetExitFlag() const
{
   return impl->exitFlag;
}

void SBomber::ProcessKBHit()
{
   int c = _getch();

   if (c == 224)
   {
      c = _getch();
   }

   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked. key = ", c);

   switch (c) {

   case 27: // esc
      impl->exitFlag = true;
      break;

   case 72: // up
      impl->FindPlane()->ChangePlaneY(-0.25);
      break;

   case 80: // down
      impl->FindPlane()->ChangePlaneY(0.25);
      break;

   case 'b':
      impl->DropBomb();
      break;

   case 'B':
      impl->DropBomb();
      break;

   default:
      break;
   }
}

void SBomber::DrawFrame()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   for (size_t i = 0; i < impl->vecDynamicObj.size(); ++i)
   {
      if (impl->vecDynamicObj[i] != nullptr)
      {
         impl->vecDynamicObj[i]->Draw();
      }
   }

   for (size_t i = 0; i < impl->vecStaticObj.size(); ++i)
   {
      if (impl->vecStaticObj[i] != nullptr)
      {
         impl->vecStaticObj[i]->Draw();
      }
   }

   GotoXY(0, 0);
   impl->fps++;

   impl->FindLevelGUI()->SetParam(impl->passedTime, impl->fps, impl->bombsNumber, impl->score);
}

void SBomber::TimeStart()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");
   impl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
   impl->finishTime = GetTickCount64();
   impl->deltaTime = uint16_t(impl->finishTime - impl->startTime);
   impl->passedTime += impl->deltaTime;

   for (size_t i = 0; i < impl->vecStaticObj.size(); ++i)
   {
      if (typeid(Tank) == typeid(*impl->vecStaticObj[i].get()))
      {
         if (Tank* pTank = dynamic_cast<Tank*>(impl->vecStaticObj[i].get()))
         {
            pTank->Update(impl->deltaTime / 1000.f);
         }
      }
   }

   impl->mediator.Update(impl->deltaTime / 1000.f);

   impl->logger.WriteToLog(std::string(__FUNCTION__) + " deltaTime = ", (int)impl->deltaTime);
}
